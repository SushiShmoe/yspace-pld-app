// app headers
#include <app_LTC2983.h>
#include <server_ltc.h>

// standard libraries
#include <string.h>

#include <cmsis_os2.h>

// SALLY libraries
#include <csp_pld_txn.h>
#include <service_err_codes.h>

// lpldgen-generated packet descriptions
#include <pld_ltc.h>

#include <LTC2983.h>

#include <ltc/ltc_defines.h>

#define MAX_ITERATIONS 100

static int8_t server_set_mode(void* vreq, void* vrpl);
static int8_t server_get_status(void* vreq, void* vrpl);
static int8_t server_read_temp(void* vreq, void* vrpl);
static int8_t server_set_rsense(void* vreq, void* vrpl);

void ltc_service_handler(csp_conn_t* conn, csp_packet_t *packet) {
  (void)conn;
  if(!packet) {
    return;
  }
  
  if(packet->length < 1) {
    csp_buffer_free(packet);
    return;
  }

  uint8_t pld_req_buff[SIZEOF_MAX(struct LTC_SET_MODE_REQ a; \
  	  	  	  	  	  	  	  	  struct LTC_GET_STATUS_REQ b; \
								  struct LTC_READ_TEMP_REQ c;
							  )];

  uint8_t pld_rsp_buff[SIZEOF_MAX(struct LTC_SET_MODE_RSP a; \
  	  	  	  	  	  	  	  	  struct LTC_GET_STATUS_RSP b; \
  	  	  	  	  	  	  	  	  struct LTC_READ_TEMP_RSP c;
							  )];
  
  // this structure will hold information about the transaction
  struct csp_pld_txn_t txn = {
    .pack_req = packet,
    .pld_req = pld_req_buff,
    .pld_rsp = pld_rsp_buff,
  };

  // set transaction properties based on the command ID
  uint8_t cmd_id = packet->data[0];
  switch(cmd_id) {
    case LTC_SET_MODE_RSP_CMD_ID: {
      // each transaction needs at least the size of the reply, ...
      txn.bin_size_rsp = LTC_SET_MODE_RSP_BIN_SIZE;
      // ... function to be used to parse the request, ...
      txn.req_parse_s = (fn_parse_static_t)LTC_SET_MODE_REQ_parse_s;
      // ... function to be used to build a reply, ...
      txn.rsp_build_s = (fn_build_static_t)LTC_SET_MODE_RSP_build_s;
      // ... and a callback to a function that will actually do something
      txn.fce = server_set_mode;
    } break;

    case LTC_GET_STATUS_RSP_CMD_ID: {
      // each transaction needs at least the size of the reply, ...
      txn.bin_size_rsp = LTC_GET_STATUS_RSP_BIN_SIZE;
      // ... function to be used to parse the request, ...
      txn.req_parse_s = (fn_parse_static_t)LTC_GET_STATUS_REQ_parse_s;
      // ... function to be used to build a reply, ...
      txn.rsp_build_s = (fn_build_static_t)LTC_GET_STATUS_RSP_build_s;
      // ... and a callback to a function that will actually do something
      txn.fce = server_get_status;
    } break;

    case LTC_READ_TEMP_RSP_CMD_ID: {
      // each transaction needs at least the size of the reply, ...
      txn.bin_size_rsp = LTC_READ_TEMP_RSP_BIN_SIZE;
      // ... function to be used to parse the request, ...
      txn.req_parse_s = (fn_parse_static_t)LTC_READ_TEMP_REQ_parse_s;
      // ... function to be used to build a reply, ...
      txn.rsp_build_s = (fn_build_static_t)LTC_READ_TEMP_RSP_build_s;
      // ... and a callback to a function that will actually do something
      txn.fce = server_read_temp;
    } break;

    case LTC_SET_RSENSE_RSP_CMD_ID: {
      // each transaction needs at least the size of the reply, ...
      txn.bin_size_rsp = LTC_SET_RSENSE_RSP_BIN_SIZE;
      // ... function to be used to parse the request, ...
      txn.req_parse_s = (fn_parse_static_t)LTC_SET_RSENSE_REQ_parse_s;
      // ... function to be used to build a reply, ...
      txn.rsp_build_s = (fn_build_static_t)LTC_SET_RSENSE_RSP_build_s;
      // ... and a callback to a function that will actually do something
      txn.fce = server_set_rsense;
    } break;

    default: {
      fprintf(stderr, "Unknown command 0x%02x!", packet->data[0]);
      csp_buffer_free(packet);
      return;
    }
  }

  csp_pld_txn(&txn);
}

static int8_t server_set_mode(void* vreq, void* vrpl) {
  struct LTC_SET_MODE_REQ* req = (struct LTC_SET_MODE_REQ*)vreq;
  struct LTC_SET_MODE_RSP* rpl = (struct LTC_SET_MODE_RSP*)vrpl;
  rpl->pld_id = LTC_SET_MODE_RSP_ID;

  LTC2983_AppMeasurementMode targetMode = (LTC2983_AppMeasurementMode)req->mode;

  LTC2983_AppSetMode(targetMode);

  uint32_t frequency = req->frequency;
  if (frequency > 0){
	  LTC2983_AppSetFrequency(frequency);
  }

  rpl->status = STATUS_GOOD;
  strncpy((char*)rpl->error, "Badabum", sizeof(rpl->error));
  rpl->error[sizeof(rpl->error) - 1] = '\0';

  // these functions have to return a status code
  return(SERVICE_ERR_NONE);
}

static int8_t server_get_status(void* vreq, void* vrpl) {
  (void*)vreq;
  struct LTC_GET_STATUS_RSP* rpl = (struct LTC_GET_STATUS_RSP*)vrpl;
  rpl->pld_id = LTC_GET_STATUS_RSP_ID;

  rpl->mode = (uint8_t)LTC2983_AppGetMode();

  rpl->frequency = (uint32_t)LTC2983_AppGetFrequency();

  rpl->result_status = (uint8_t)(LTC2983_AppIsResultReady() ? 0 : 1);

  rpl->error =(uint8_t)LTC2983_AppGetError();

  // these functions have to return a status code
  return(SERVICE_ERR_NONE);
}

static int8_t server_read_temp(void* vreq, void* vrpl) {
  struct LTC_READ_TEMP_REQ* req = (struct LTC_READ_TEMP_REQ*)vreq;
  struct LTC_READ_TEMP_RSP* rpl = (struct LTC_READ_TEMP_RSP*)vrpl;
  rpl->pld_id = LTC_READ_TEMP_RSP_ID;

  uint8_t force = req->force_measurement;

  LTC2983ConvResult_t tempResults[4];

  uint8_t status = LTC2983_AppGetResults(tempResults);

  if (!status && force){
	  LTC2983_AppSetMode(0);

	 for (int i = 0; i < MAX_ITERATIONS; i++){
		 if (LTC2983_AppIsResultReady()){
			 status = LTC2983_AppGetResults(tempResults);

			 break;
		 }

		 osDelay(50);
	 }
  }

  if (!status){
	  rpl->result_ready = RESULT_NOT_READY;

	  for (int i = 0; i < TEMP_RSLT_COUNT; i++){
		rpl->TempRslt[i].channel = 0;
	    rpl->TempRslt[i].temperature = 0;
	    rpl->TempRslt[i].status = LTC2983_ENUM_CONV_STATUS_INVALID;
	  }


	  return(SERVICE_ERR_NONE);
  }

  for (int i = 0; i < 4; i++){
	rpl->TempRslt[i].channel = tempResults[i].Channel;
	rpl->TempRslt[i].temperature = tempResults[i].Temperature;
	rpl->TempRslt[i].status = tempResults[i].Status;
  }

  // these functions have to return a status code
  return(SERVICE_ERR_NONE);
}

static int8_t server_set_rsense(void* vreq, void* vrpl) {
  struct LTC_SET_RSENSE_REQ* req = (struct LTC_SET_RSENSE_REQ*)vreq;
  struct LTC_SET_RSENSE_RSP* rpl = (struct LTC_SET_RSENSE_RSP*)vrpl;
  rpl->pld_id = LTC_SET_RSENSE_RSP_ID;

  LTC2983_ChangeRsenseValue(req->val);

  // these functions have to return a status code
  return(SERVICE_ERR_NONE);
}

