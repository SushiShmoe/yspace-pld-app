/*
Cubesat Space Protocol - A small network-layer protocol designed for Cubesats
Copyright (C) 2012 GomSpace ApS (http://www.gomspace.com)
Copyright (C) 2012 AAUSAT3 Project (http://aausat3.space.aau.dk)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include "main.h"

#include <csp/interfaces/csp_if_usart.h>

#include <stdio.h>
#include <inttypes.h>


#include <csp/csp.h>
#include <csp/drivers/driver_usart.h>
#include <csp/arch/csp_malloc.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

typedef struct {
	char name[CSP_IFLIST_NAME_MAX + 1];
	csp_iface_t iface;
	csp_kiss_interface_data_t ifdata;
	csp_usart_fd_t fd;
	 UART_HandleTypeDef huart;
} kiss_context_t;

static int usart_driver_tx(void *driver_data, const unsigned char * data, size_t data_length) {

	kiss_context_t * ctx = driver_data;
	char *c = ctx->iface.name;
	if (HAL_UART_Transmit(&ctx->huart, data, data_length, 1000) == HAL_OK) {
		return CSP_ERR_NONE;
	}

	return CSP_ERR_TX;
}

static void usart_driver_rx(void * user_data, uint8_t * data, size_t data_size, void * pxTaskWoken) {

	kiss_context_t * ctx = user_data;
	csp_usart_rx(&ctx->iface, data, data_size, NULL);
}

int csp_add_interface_usart(const char * ifname, csp_iface_t ** return_iface, UART_HandleTypeDef h) {


	kiss_context_t * ctx = csp_calloc(1, sizeof(*ctx));
	if (ctx == NULL) {
		return CSP_ERR_NOMEM;
	}
	ctx->huart = h;

	strncpy(ctx->name, ifname, sizeof(ctx->name) - 1);
	ctx->iface.name = ctx->name;
	ctx->iface.driver_data = ctx;
	ctx->iface.interface_data = &ctx->ifdata;
	ctx->ifdata.tx_func = usart_driver_tx;

	ctx->fd = -1;


	int res = csp_usart_add_interface(&ctx->iface);

	if (return_iface) {
		*return_iface = &ctx->iface;
	}

	return res;
}
