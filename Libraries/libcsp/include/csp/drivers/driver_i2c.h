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


/**
   @file

   USART driver.

   @note This interface implementation only support ONE open UART connection.
*/

#include <csp/interfaces/csp_if_i2c.h>


#ifdef __cplusplus
extern "C" {
#endif



typedef int csp_usart_fd_t;

int i2c_driver_tx(void *driver_data, const unsigned char * data, size_t data_length, uint8_t address);

void i2c_driver_rx(void * user_data, uint8_t * data, size_t data_size, void * pxTaskWoken);

int csp_add_interface_i2c(const char * ifname, csp_iface_t ** return_iface, I2C_HandleTypeDef i);

#ifdef __cplusplus
}
#endif

