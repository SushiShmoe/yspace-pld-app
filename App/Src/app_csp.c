#include "app_csp.h"

#include "main.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"

#include "cmsis_os2.h"

#include "csp/csp.h"
#include "csp/drivers/driver_i2c.h"
#include "csp/interfaces/csp_if_i2c.h"
#include "csp/arch/csp_system.h"

#include "LTC2983_config.h"

#include "server_ltc.h"
#include "pld_ltc.h"

uint8_t receive_complete = 0;
uint8_t rx_count = 0;
uint8_t rx_buffer[256];

uint8_t uartBuffer[256] = {0};
uint8_t uartLength;

csp_iface_t *iface_UART;
csp_iface_t *iface_I2C;

osThreadId_t cspTaskHandle;
const osThreadAttr_t cspTask_attributes = {
    .name = "cspTask",
    .stack_size = 2048 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t cspListenerTaskHandle;
const osThreadAttr_t cspListenerTask_attributes = {
    .name = "cspListenerTask",
    .stack_size = 2048 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t cspRouterTaskHandle;
const osThreadAttr_t cspRouterTask_attributes = {
    .name = "cspRouterTask",
    .stack_size = 2048 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t cspI2CHandle;
const osThreadAttr_t cspI2C_attributes = {
    .name = "cspI2C",
    .stack_size = 2048 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};


void csp_reboot_callback(void);
void StartcspTask(void *argument);
void StartcspListenerTask(void *argument);
void StartcspRouterTask(void *argument);
void StartcspI2C(void *argument);


void app_init_csp(void)
{
    HAL_I2C_EnableListen_IT(&hi2c1);

    cspTaskHandle = osThreadNew(StartcspTask, NULL, &cspTask_attributes);
}

void StartcspTask(void *argument)
{
    /* Infinite loop */
    csp_conf_t csp_conf;
    csp_conf_get_defaults(&csp_conf);
    csp_conf.address = 13;
    csp_conf.conn_max = 30;
    csp_conf.buffers = 30;
    csp_conf.port_max_bind = 50;
    csp_conf.hostname = "Yspace - U5";
    csp_conf.revision = "B";
    csp_init(&csp_conf);

    csp_sys_set_reboot(csp_reboot_callback);

    csp_add_interface_i2c("I2C", &iface_I2C, hi2c1);

    // csp_rtable_set(7, 5, iface_UART, CSP_NO_VIA_ADDRESS);
    // csp_rtable_set(15, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    // csp_rtable_set(7, 5, iface_I2C, 15);

    csp_rtable_set(9, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    csp_rtable_set(14, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    csp_rtable_set(10, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    csp_rtable_set(8, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    csp_rtable_set(2, 5, iface_I2C, CSP_NO_VIA_ADDRESS);
    csp_rtable_set(24, 5, iface_I2C, 9);
	csp_rtable_set(11, 5, iface_I2C, 9);

	csp_rtable_set(25, 5, iface_I2C, 9);

    // csp_rtable_set(CSP_DEFAULT_ROUTE, 0, iface_UART, CSP_NO_VIA_ADDRESS);

    cspListenerTaskHandle = osThreadNew(StartcspListenerTask, NULL, &cspListenerTask_attributes);
    configASSERT(cspListenerTaskHandle != NULL);

    /* creation of cspRouterTask */
    cspRouterTaskHandle = osThreadNew(StartcspRouterTask, NULL, &cspRouterTask_attributes);

    cspI2CHandle = osThreadNew(StartcspI2C, NULL, &cspI2C_attributes);

    vTaskDelete(NULL);
}

void StartcspListenerTask(void *argument)
{
    for (;;)
    {
        csp_conn_t *conn = NULL;
        csp_packet_t *packet = NULL;
        csp_socket_t *sock = csp_socket(CSP_SO_NONE);

        csp_bind(sock, CSP_ANY);

        csp_listen(sock, 10);

        while (1)
        {

            conn = csp_accept(sock, 1000);
            if (conn == NULL)
            {
                //int i = csp_ping(11, 5000, 10, CSP_O_NONE);
                continue;
            }

            while ((packet = csp_read(conn, 0)) != NULL)
            {
                switch (csp_conn_dport(conn))
                {
                case 10:
                	server_process_packet(conn, packet);
                	break;
                default:
                    csp_service_handler(conn, packet);
                    break;
                }
                // csp_buffer_free(packet);
            }

            if (conn) {
            	csp_close(conn);
            }
        }

        return;
    }
}

void StartcspRouterTask(void *argument)
{
    for (;;)
    {
        csp_route_work(10);
    }
}

void StartcspI2C(void *argument)
{
    for (;;)
    {
        csp_i2c_rx(iface_I2C, rx_buffer, rx_count, NULL);
        memset(rx_buffer, 0, rx_count);
        rx_count = 0;
        receive_complete = 0;
        vTaskSuspend(cspI2CHandle);
    }
}

void HAL_I2C_AddrCallback(I2C_HandleTypeDef *hi2c, uint8_t TransferDirection, uint16_t AddrMatchCode)
{
    if (hi2c->Instance == I2C1 && TransferDirection == I2C_DIRECTION_TRANSMIT)
    {
        rx_count = 0; // Reset byte counter
        // Start receiving data. I2C_NO_OPTION means the slave will keep ACKing until STOP or NACK from master
        HAL_I2C_Slave_Seq_Receive_IT(hi2c, rx_buffer, sizeof(rx_buffer), I2C_NEXT_FRAME);
    }
}

// Callback when a complete listen cycle ends (including STOP detection)
void HAL_I2C_ListenCpltCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        receive_complete = 1;
        xTaskResumeFromISR(cspI2CHandle);

        HAL_I2C_EnableListen_IT(hi2c);
    }
}

// Callback for I2C errors
void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c)
{
    if (hi2c->Instance == I2C1)
    {
        if (hi2c->ErrorCode & HAL_I2C_ERROR_AF)
        {
            rx_count = sizeof(rx_buffer) - hi2c->XferSize;

            receive_complete = 1;
            xTaskResumeFromISR(cspI2CHandle);
        }
        // Handle other I2C errors as needed
    }
    // Re-enable listening after handling the error
    HAL_I2C_EnableListen_IT(hi2c);
}

void csp_reboot_callback(void)
{
    HAL_NVIC_SystemReset();
}
