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


#include <stdio.h>
#include <inttypes.h>


#include <csp/csp.h>
#include <csp/drivers/driver_i2c.h>
#include <csp/arch/csp_malloc.h>

extern I2C_HandleTypeDef hi2c1;
extern uint8_t uartBuffer[256];
extern uint8_t uartLength;

typedef struct {
	char name[CSP_IFLIST_NAME_MAX + 1];
	csp_iface_t iface;
	csp_kiss_interface_data_t ifdata;
	csp_usart_fd_t fd;
	I2C_HandleTypeDef i2c;
} kiss_context_t;

int i2c_driver_tx(void *driver_data, const unsigned char * data, size_t data_length, uint8_t address) {

	kiss_context_t * ctx = driver_data;
	HAL_I2C_DisableListen_IT(&ctx->i2c);

	HAL_StatusTypeDef x = HAL_I2C_Master_Transmit(&ctx->i2c,(address << 1), data, data_length, 1000);
	HAL_I2C_EnableListen_IT(&ctx->i2c);
	if(x == HAL_OK) {return CSP_ERR_NONE;}
	return CSP_ERR_TX;


}

void i2c_driver_rx(void * user_data, uint8_t * data, size_t data_size, void * pxTaskWoken) {

	kiss_context_t * ctx = user_data;
	csp_kiss_rx(&ctx->iface, data, data_size, NULL);
}

int csp_add_interface_i2c(const char * ifname, csp_iface_t ** return_iface, I2C_HandleTypeDef i) {


	kiss_context_t * ctx = csp_calloc(1, sizeof(*ctx));
	if (ctx == NULL) {
		return CSP_ERR_NOMEM;
	}
	ctx->i2c = i;

	strncpy(ctx->name, ifname, sizeof(ctx->name) - 1);
	ctx->iface.name = ctx->name;
	ctx->iface.driver_data = ctx;
	ctx->iface.interface_data = &ctx->ifdata;
	ctx->ifdata.tx_func = i2c_driver_tx;
#if (CSP_WINDOWS)
	ctx->fd = NULL;
#else
	ctx->fd = -1;
#endif

	int res = csp_i2c_add_interface(&ctx->iface);
	if (res == CSP_ERR_NONE) {
		//res = csp_usart_open(conf, kiss_driver_rx, ctx, &ctx->fd);
	}

	if (return_iface) {
		*return_iface = &ctx->iface;
	}

	return res;
}
