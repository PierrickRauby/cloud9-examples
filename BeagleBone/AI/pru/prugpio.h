// This file defines the GPIO port addresses and PRU address

#if AI == 1
#warning "Found AI"
// These are addresses for the am5729
// First define the 9 GPIO port addresses
#define GPIO1 0x4AE10000
#define GPIO2 0x48055000
#define GPIO3 0x48057000
#define GPIO4 0x48059000
#define GPIO5 0x4805B000
#define GPIO6 0x4805D000
#define GPIO7 0x48051000
#define GPIO8 0x48053000

// These define which bits in a given port go to the USR LEDs
// GPIO3
#define USR0 (1<<17)
#define USR2 (1<<15)
#define USR3 (1<<14)
#define USR4 (1<< 7)
// GPIO5
#define USR1 (1<< 5)
// The define a couple of GPIO pin addresses
// GPIO6
#define P9_25   (1<<17)
// GPIO8
#define P8_17   (1<18)

// These define which bin in register R30 go to which header pins
// R30 bits - Output on pru1_1
#define P9_14	(1<<14)
#define P9_16	(1<<15)
#define P8_15	(1<<16)
#define P8_26	(1<<17)
#define P8_16	(1<<18)
// R31 bits - Input on pru1_1
#define P8_18	(1<<5)
#define P8_19	(1<<6)
#define P8_13	(1<<7)

#else

#warning "Found else"
// These are addresses for the am35xx
#define GPIO0 0x44E09000
#define GPIO1 0x4804C000
#define GPIO2 0x481AC000
#define GPIO3 0x481AE000

// USR LED bit positions
// GPIO 1
#define USR0 (1<<21)
#define USR1 (1<<22)
#define USR2 (1<<23)
#define USR3 (1<<24)

// Shared memory
#define AM33XX_DATARAM0_PHYS_BASE		0x4a300000
#define AM33XX_DATARAM1_PHYS_BASE		0x4a302000
#define AM33XX_PRUSS_SHAREDRAM_BASE		0x4a310000

#endif
// /4 to convert from byte address to word address
#define GPIO_CLEARDATAOUT	0x190/4     // Write 1 here to set a given bit    
#define GPIO_SETDATAOUT 	0x194/4     // A 1 here clears the corresponding bit
#define GPIO_DATAOUT		0x138/4     // For reading the GPIO registers