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

#include <csp/interfaces/csp_if_i2c.h>

#include <string.h>

#include <csp/csp_endian.h>
#include <csp/csp_crc32.h>


int csp_i2c_tx(const csp_route_t * ifroute, csp_packet_t * packet) {

	csp_kiss_interface_data_t * ifdata = ifroute->iface->interface_data;
	void * driver = ifroute->iface->driver_data;
	int addr = ifroute->via;
	if(CSP_NO_VIA_ADDRESS == ifroute->via) {
		addr = packet->id.dst;
	}

	/* Add CRC32 checksum - the MTU setting ensures there are space */
	if(packet->id.flags & 0x01) {
	csp_crc32_append(packet, false);}

	/* Lock */
	if (csp_mutex_lock(&ifdata->lock, 1000) != CSP_MUTEX_OK) {
            return CSP_ERR_TIMEDOUT;
        }

	/* Save the outgoing id in the buffer */
	packet->id.ext = csp_hton32(packet->id.ext);
	packet->length += sizeof(packet->id.ext);


	uint8_t buffer[260] = {0};
		uint8_t index = 0;

		const unsigned char * data = (unsigned char *) &packet->id.ext;

		for (unsigned int i = 0; i < packet->length; i++, ++data) {
		        buffer[index++] = *data;
			}
		ifdata->tx_func(driver, buffer, index,addr);



	/* Free data */
	csp_buffer_free(packet);

	/* Unlock */
	csp_mutex_unlock(&ifdata->lock);

	return CSP_ERR_NONE;
}

/**
 * Decode received data and eventually route the packet.
 */
void csp_i2c_rx(csp_iface_t * iface, const uint8_t * buf, size_t len, void * pxTaskWoken) {

	csp_kiss_interface_data_t * ifdata = iface->interface_data;

	if (ifdata->rx_packet == NULL) {
		ifdata->rx_packet = pxTaskWoken ? csp_buffer_get_isr(0) : csp_buffer_get(0); // CSP only supports one size
	}

	/* If no more memory, skip frame */
	if (ifdata->rx_packet == NULL) {
		return;
	}

	/* Start transfer */
	ifdata->rx_length = 0;
	ifdata->rx_first = true;


	while (len--) {

		/* Input */
		uint8_t inputbyte = *buf++;

		/* If packet was too long */
		if (ifdata->rx_length > ifdata->max_rx_length) {
			//csp_log_warn("KISS RX overflow");
			iface->rx_error++;
			ifdata->rx_length = 0;
		}
		((char *) &ifdata->rx_packet->id.ext)[ifdata->rx_length++] = inputbyte;
	}



	/* Accept message */
	if (ifdata->rx_length > 0) {

		/* The CSP packet length is without the header */
		ifdata->rx_packet->length = ifdata->rx_length - CSP_HEADER_LENGTH;

		/* Convert the packet from network to host order */
		ifdata->rx_packet->id.ext = csp_ntoh32(ifdata->rx_packet->id.ext);

		//ifdata->rx_packet->id.flags;
		if (ifdata->rx_packet->id.flags & 0x01) {
			if (csp_crc32_verify(ifdata->rx_packet, false) != CSP_ERR_NONE) {
				//csp_log_warn("KISS invalid crc frame skipped, len: %u", ifdata->rx_packet->length);
				iface->rx_error++;
				return;
			}
		}




		/* Send back into CSP, notice calling from task so last argument must be NULL! */
		csp_qfifo_write(ifdata->rx_packet, iface, pxTaskWoken);
		ifdata->rx_packet = NULL;
		return;

	}

}

int csp_i2c_add_interface(csp_iface_t * iface) {

	if ((iface == NULL) || (iface->name == NULL) || (iface->interface_data == NULL)) {
		return CSP_ERR_INVAL;
	}

        csp_kiss_interface_data_t * ifdata = iface->interface_data;
	if (ifdata->tx_func == NULL) {
		return CSP_ERR_INVAL;
	}

	if (csp_mutex_create(&ifdata->lock) != CSP_MUTEX_OK) {
		return CSP_ERR_NOMEM;
        }

	ifdata->max_rx_length = CSP_HEADER_LENGTH + csp_buffer_data_size(); // CSP header + CSP data
	ifdata->rx_length = 0;
	ifdata->rx_mode = KISS_MODE_NOT_STARTED;
	ifdata->rx_first = false;
	ifdata->rx_packet = NULL;

        const unsigned int max_data_size = csp_buffer_data_size() - sizeof(uint32_t); // compensate for the added CRC32
        if ((iface->mtu == 0) || (iface->mtu > max_data_size)) {
            iface->mtu = max_data_size;
        }

	iface->nexthop = csp_i2c_tx;

	return csp_iflist_add(iface);
}
