#ifndef _SERVICE_CSP_PLD_TXN_H
#define _SERVICE_CSP_PLD_TXN_H

#include <csp/csp.h>
#include <payloads_internal.h>

// helper macro to get largest member size
#define SIZEOF_MAX(...) sizeof( union{__VA_ARGS__} )

// helper macro the get single member size
// looks like a null ptr, but actually isn't because the operand of sizeof() is not evaluated
#define SIZEOF_MEMBER(TYPE, MEMBER) sizeof(((TYPE *)0)->MEMBER)

typedef int8_t (*pld_exec_func)(void* vreq, void* vrsp);
typedef int8_t (*pld_exec_func_growable)(void* vreq, void* vrsp, size_t* resp_size);

struct csp_pld_txn_t {
  csp_packet_t* pack_req;
  size_t bin_size_rsp;
  fn_parse_static_t req_parse_s;
  fn_build_static_t rsp_build_s;
  void* pld_req;
  void* pld_rsp;
  pld_exec_func fce;
  pld_exec_func_growable fce_grow;
};

void csp_rpl_id(csp_id_t id, uint8_t cmd_id, int8_t reply, size_t len);
int csp_rpl_buffer(csp_packet_t *packet, void *reply, size_t reply_size);
int csp_rpl(csp_packet_t* packet);

void csp_pld_txn(struct csp_pld_txn_t* txn);
int8_t csp_txn_retry(csp_conn_t* conn, uint32_t timeout, uint8_t* req_buff, size_t req_size, uint8_t* rsp_buff, uint8_t rsp_size, uint8_t retries);


#endif
