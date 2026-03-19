#include <csp_pld_txn.h>
#include <service_err_codes.h>

static csp_packet_t* csp_buffer_get_safe(size_t len) {
  return(csp_buffer_get(len));
}

static void csp_buffer_free_safe(csp_packet_t* packet) {

  csp_buffer_free(packet);
}

void csp_rpl_id(csp_id_t id, uint8_t cmd_id, int8_t reply, size_t len) {
  // get the buffer
  csp_packet_t* packet = csp_buffer_get_safe(len);
  if(packet == NULL) {
    //DEBUG_APP_PRINTF("Failed to get CSP reply buffer!");
    return;
  }

  // init data to zeroes
  memset(packet->data, 0x00, len);

  // set data and length
  packet->data[0] = cmd_id;
  packet->data[1] = reply;
  packet->length = len;

  // set ID
  packet->id.ext = id.ext;

  // send it - if this goes wrong, csp_rpl will free the packet
  csp_rpl(packet);
}

int csp_rpl(csp_packet_t* packet) {
  if(packet == NULL) {
    //DEBUG_APP_PRINTF("Invalid CSP reply buffer!");
    return(CSP_ERR_NOMEM);
  }

  // send it with swapped destinations and sources
  int ret = csp_sendto(packet->id.pri, packet->id.src, packet->id.sport, packet->id.dport, 0, packet, 0);
  if(ret != CSP_ERR_NONE) {
    //DEBUG_APP_PRINTF("Failed to send CSP reply!");
    csp_buffer_free_safe(packet);
  }

  return(ret);
}

int csp_rpl_buffer(csp_packet_t *packet, void *reply, size_t reply_size) {
  if(!packet || !reply) {
    return(CSP_ERR_INVAL);
  }

  csp_packet_t *reply_packet = csp_buffer_get_safe(reply_size);
  if(reply_packet == NULL) {
    //DEBUG_APP_PRINTF("csp_buffer_get NULL!\r\n");
    return(CSP_ERR_NOMEM);
  }

  reply_packet->length = reply_size;
  reply_packet->id.ext = packet->id.ext;
  memcpy(reply_packet->data, reply, reply_size);

  // free the original packet, we don't need it anymore
  csp_buffer_free_safe(packet);

  // if this goes wrong, csp_rpl will free the reply packet
  return(csp_rpl(reply_packet));
}

void csp_pld_txn(struct csp_pld_txn_t* txn) {
  if(!txn || !txn->req_parse_s) {
    // maybe the user wants to do nothing?
    return;
  }

  // parse the request
  pld_error_t ret = txn->req_parse_s(txn->pack_req->data, txn->pack_req->length, txn->pld_req);
  if(ret != PLD_OK) {
    csp_rpl_id(txn->pack_req->id, txn->pack_req->data[0], SERVICE_ERR_PAYLOADS(ret), txn->bin_size_rsp);
    csp_buffer_free_safe(txn->pack_req);
    return;
  }

  // do the deed
  int8_t res = SERVICE_ERR_NONE;
  if(txn->fce) {
    res = txn->fce(txn->pld_req, txn->pld_rsp);
  } else {
    res = txn->fce_grow(txn->pld_req, txn->pld_rsp, &txn->bin_size_rsp);
  }

  if(res != SERVICE_ERR_NONE) {
    csp_rpl_id(txn->pack_req->id, txn->pack_req->data[0], res, txn->bin_size_rsp);
    csp_buffer_free_safe(txn->pack_req);
    return;
  }

  // check if user want to send a response
  if(!txn->rsp_build_s) {
    // response build callback not present, probably multiple response packets
    csp_buffer_free_safe(txn->pack_req);
    return;
  }

  // get buffer for the response
  csp_packet_t* pack_rsp = csp_buffer_get_safe(txn->bin_size_rsp);
  if(pack_rsp == NULL) {
    csp_rpl_id(txn->pack_req->id, txn->pack_req->data[0], SERVICE_ERR_UNKNOWN, txn->bin_size_rsp);
    csp_buffer_free_safe(txn->pack_req);
    return;
  }

  // build the response
  ret = txn->rsp_build_s(txn->pld_rsp, pack_rsp->data, txn->bin_size_rsp);
  if(ret != PLD_OK) {
    csp_buffer_free_safe(pack_rsp);
    csp_rpl_id(txn->pack_req->id, txn->pack_req->data[0], SERVICE_ERR_PAYLOADS(ret), txn->bin_size_rsp);
    csp_buffer_free_safe(txn->pack_req);
    return;
  }

  // send it
  pack_rsp->id.ext = txn->pack_req->id.ext;
  pack_rsp->length = txn->bin_size_rsp;
  csp_rpl(pack_rsp);

  // free everything
  csp_buffer_free_safe(txn->pack_req);
}

int8_t csp_txn_retry(csp_conn_t* conn, uint32_t timeout, uint8_t* req_buff, size_t req_size, uint8_t* rsp_buff, uint8_t rsp_size, uint8_t retries) {
  if(!conn) {
    return(SERVICE_ERR_INVALID_ARG);
  }

  int8_t ret = SERVICE_ERR_TIMEOUT;
  for(uint8_t i = 0; i < retries; i++) {
    int sz = csp_transaction_persistent(conn, timeout, req_buff, req_size, rsp_buff, rsp_size);
    if(sz == 0) {
      continue;
    }

    // reply status is offset by 1 byte (CMD_ID)
    if((int8_t)rsp_buff[1] == SERVICE_ERR_TIMEOUT) {
      continue;
    }

    ret = rsp_buff[1];
    break;
  }
  
  return(ret);
}
