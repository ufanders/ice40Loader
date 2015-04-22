/*********************************************************************
 * Platform: 	Explorer-16 with PIC32MX PIM
 ********************************************************************/
#include <plib.h>

// Configuration Bit settings
// SYSCLK = 80 MHz (8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 40 MHz
// Primary Osc w/PLL (XT+,HS+,EC+PLL)
// WDT OFF
// Other options are don't care
//
#pragma config FPLLMUL = MUL_20, FPLLIDIV = DIV_2, FPLLODIV = DIV_1, FWDTEN = OFF
#pragma config POSCMOD = HS, FNOSC = PRIPLL, FPBDIV = DIV_8

#define SYS_FREQ (80000000L)

int main(void)
{
    int i;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig(SYS_FREQ, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);


    // Explorer16 LEDs are on lower 8-bits of PORTA and to use all LEDs, JTAG port must be disabled.
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);

    // Make all lower 8-bits of PORTA as output. Turn them off before changing
    // direction so that we don't have unexpected flashes
    mPORTAClearBits(BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
                                                     BIT_3 | BIT_2 | BIT_1 | BIT_0 );

    mPORTASetPinsDigitalOut( BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
                                                     BIT_3 | BIT_2 | BIT_1 | BIT_0 );

    // Now blink all LEDs ON/OFF forever.
    while(1)
    {
        mPORTAToggleBits(BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
                                                 BIT_3 | BIT_2 | BIT_1 | BIT_0 );

        // Insert some delay
        i = 1024*1024;
        while(i--);
    }
}

