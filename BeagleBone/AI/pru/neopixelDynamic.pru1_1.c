////////////////////////////////////////
//	neopixelDynamic.c
//	One color appears to move around the ws2812 (NeoPixel) display
//	Wiring:	The NeoPixel Data In goes to P9_16, the plus lead to P9_3 or P9_4 (3.3V)
//			and the ground to P9_1 or P9_2.  If you have more then 40 some 
//			NeoPixels you will need and external supply.
//	Setup:	None
//	See:	 
//	PRU:	pru1_1
////////////////////////////////////////
#include <stdint.h>
#include <pru_cfg.h>
#include "resource_table_empty.h"
#include "init_pins_empty.h"
#include "prugpio.h"

#define STR_LEN 24
#define	oneCyclesOn		700/5	// Stay on 700ns
#define oneCyclesOff	800/5
#define zeroCyclesOn	350/5
#define zeroCyclesOff	600/5
#define resetCycles		60000/5	// Must be at least 50u, use 60u

#define SPEED 20000000/5	// Time to wait between updates

volatile register uint32_t __R30;
volatile register uint32_t __R31;

void main(void)
{
	uint32_t background = 0x00000f;
	uint32_t foreground = 0x000f00;

	// Select which pins to output to.  These are all on pru1_1
	uint32_t gpio = P9_16;
	
	uint32_t color[STR_LEN];	// green, red, blue
	int i, j;
	int k, oldk = 0;;
	// Set everything to background
	for(i=0; i<STR_LEN; i++) {
		color[i] = background;
	}
	
	while(1) {
		// Move forward one position
		for(k=0; k<STR_LEN; k++) {
			color[oldk] = background;
			color[k]    = foreground;
			oldk=k;

			// Output the string
			for(j=0; j<STR_LEN; j++) {
				for(i=23; i>=0; i--) {
					if(color[j] & (0x1<<i)) {
						__R30 |= gpio;		// Set the GPIO pin to 1
						__delay_cycles(oneCyclesOn-1);
						__R30 &= ~gpio;		// Clear the GPIO pin
						__delay_cycles(oneCyclesOff-2);
					} else {
						__R30 |= gpio;		// Set the GPIO pin to 1
						__delay_cycles(zeroCyclesOn-1);
						__R30 &= ~gpio;		// Clear the GPIO pin
						__delay_cycles(zeroCyclesOff-2);
					}
				}
			}
			// Send Reset
			__R30 &= ~gpio;	// Clear the GPIO pin
			__delay_cycles(resetCycles);

			// Wait
			__delay_cycles(SPEED);
		}
	}
}
