#ifndef DRIVER_TEMPLATE_SERVER_CSP_H
#define DRIVER_TEMPLATE_SERVER_CSP_H

/*!
  \file server_csp.h 
  \brief This template header contains commands for simulating server
  processing and responses. This is to be used in testing to simulate the device.
  This version processes packets sent via CSP.
*/

#include <csp/csp.h>
#include <payloads_internal.h>

/*!  
  \brief This function processes packets sent via CSP.
  It is called by SALLY after packet has been received,
  or a connection has been opened (depending on the configuration of the service)
  \param packet When called, this will point to the received CSP packet.
  NOTE: It is up to the caller to dispose of the packet with csp_buffer_free(packet)!
  \param conn When called, this will point to the opened connection.
*/
void ltc_service_handler(csp_conn_t* conn, csp_packet_t *packet);

#endif
