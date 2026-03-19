#include "app.h"

#include "main.h"
#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "gpdma.h"

#include "cmsis_os2.h"

#include "app_csp.h"

#include "app_LTC2983.h"
#include "LTC2983.h"

void StartIdleTask(void *argument);
void StartLTCInit(void* argument);

osThreadId_t idleTaskHandle;
const osThreadAttr_t idleTask_attributes = {
    .name = "idleTask",
    .priority = (osPriority_t)osPriorityNormal,
    .stack_size = 128 * 4
};

void app_main(void)
{
	MX_GPIO_Init();
	MX_GPDMA1_Init();
	MX_I2C1_Init();
	MX_RTC_Init();
	MX_SPI2_Init();
	MX_ADC1_Init();

    osKernelInitialize();

    idleTaskHandle = osThreadNew(StartIdleTask, NULL, &idleTask_attributes);

    app_init_LTC2983();

	app_init_csp();

	MX_FREERTOS_Init();

    osKernelStart();

    while (1)
    {
        osDelay(250);
    }
}

void StartIdleTask(void *argument)
{
    for (;;)
    {
        osDelay(250);
    }
}


