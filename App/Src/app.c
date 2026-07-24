#include "app.h"

#include "adc.h"
#include "gpio.h"
#include "i2c.h"
#include "rtc.h"
#include "spi.h"
#include "gpdma.h"

#include "cmsis_os2.h"

#include "app_csp.h"

#include "app_LTC2983.h"


void app_main(void)
{
	MX_GPIO_Init();
	MX_GPDMA1_Init();
	MX_I2C1_Init();
	MX_RTC_Init();
	MX_SPI2_Init();
	MX_ADC1_Init();

    osKernelInitialize();

    app_init_LTC2983();
	app_init_csp();

    osKernelStart();

    while (1)
    {
        osDelay(250);
    }
}
