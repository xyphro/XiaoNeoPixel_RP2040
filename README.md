# XiaoNeoPixel_RP2040

So it happened... I had a project where I used the Seeedstudio XIAO RP2040 module and it has a nice and bright WS2812 LED on it.

Naively I thought: Well, let's use one of the plenty available software libraries to control it.
HOWEVER, all those RP2040 drivers use the PIO module to set the WS2812 Neopixel LED.

After some thinking I came to the conclusion that the UART-TX signal can be used to send the right datapattern.

The UART when set to 6 bit mode with parity disabled and an inverted TX signal is here used as a nice means to update this single Neopixel with low software overhead. Check the code for full understanding.

## Short usage example:

Copy the files XiaoNeoPixel.c and XiaoNeoPixel.h to your RP2040 C project.

An Example on how to call the API is here:

```C
//[...]
#include "XiaoNeoPixel.h"

int main(void)
{
    //[...]
    xnp_init();

	uint8_t r = 0, g = 0, b = 0;
	
	while (true)
	{
		r += 1;
		g += 2;
		b += 4;
		xnp_send(r, g, b);
		sleep_ms(50);
	}
	
	//[...]
}
```

## Notes

- I am not responsible for any damages, use it at own risk :-)
- Ensure that uart0 is not used for other purposes, e.g. for stdio.
- I will likely not apply a lot of maintanance to this repository nor give a lot of support. Just want to enable others that have the same problem to solve.
- License: MIT
