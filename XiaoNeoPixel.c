#include "XiaoNeoPixel.h"

#include "pico/stdlib.h"
#include <stdio.h>
#include "hardware/uart.h"
#include "hardware/gpio.h"

void xnp_init(void)
{
	uart_init(uart0, 6660000ul);
	uart_set_format(uart0, 6, 1, UART_PARITY_NONE);
	gpio_set_function (12, GPIO_FUNC_UART);
	iobank0_hw->io[12].ctrl = (iobank0_hw->io[12].ctrl & ~(3u<<8)) | (1u<<8); // invert UART output signal
	gpio_init(11);
	gpio_set_dir(11, GPIO_OUT);    
	gpio_put(11, 1);
	gpio_set_drive_strength(11, GPIO_DRIVE_STRENGTH_12MA); // set drive strength of IO to maximum to get a bright LED
	gpio_set_function(11, GPIO_FUNC_SIO);
}

void __not_in_flash_func(xnp_send)(uint8_t r, uint8_t g, uint8_t b)
{
	uint32_t dataword = (((uint32_t)g)<<16) | (((uint32_t)r)<<8) | (((uint32_t)b)<<0);

	for (uint8_t bitcounter=0; bitcounter<24; bitcounter++)
	{
		dataword <<= 1;
		if (dataword & (1<<24))
		    uart_putc(uart0, 0x30); // send a 1
		else
		    uart_putc(uart0, 0x3C); // send a 0
	}
}
