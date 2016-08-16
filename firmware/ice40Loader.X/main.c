/*********************************************************************
 * Platform: 	Explorer-16 with PIC32MX PIM
 ********************************************************************/
#define SET_CONFIG_FUSES
#include "../HardwareProfile.h"

#include <plib.h>
#include "../top_bitmap.bin.h"

int main(void)
{
    int i;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Configure the device for maximum performance but do not change the PBDIV
    // Given the options, this function will change the flash wait states, RAM
    // wait state and enable prefetch cache but will not change the PBDIV.
    // The PBDIV value is already set via the pragma FPBDIV option above..
    SYSTEMConfig(GetSystemClock(), SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);

    // Explorer16 LEDs are on lower 8-bits of PORTA and to use all LEDs, JTAG
    // port must be disabled.
    mJTAGPortEnable(DEBUG_JTAGPORT_OFF);
    
    DISABLE_ALL_ANALOG_PINS;
    
/*
    // Make all lower 8-bits of PORTA as output. Turn them off before changing
    // direction so that we don't have unexpected flashes
    mPORTAClearBits(BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
        BIT_3 | BIT_2 | BIT_1 | BIT_0 );

    mPORTASetPinsDigitalOut( BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
        BIT_3 | BIT_2 | BIT_1 | BIT_0 );

    // Now blink all LEDs ON/OFF forever.
    while(0)
    {
        mPORTAToggleBits(BIT_7 | BIT_6 | BIT_5 | BIT_5 | BIT_4 | \
            BIT_3 | BIT_2 | BIT_1 | BIT_0 );

        // Insert some delay
        i = 1024*1024;
        while(i--);
    }
*/
    
    ice40Init();
    ice40Configure(top_bitmap_bin, sizeof(top_bitmap_bin));
    if(ice40IsConfigured())
    {
        mPORTAClearBits(BIT_7);
    }
    else
    {
        mPORTASetBits(BIT_7);
    }
}

void _general_exception_handler (unsigned cause, unsigned status)
{
    while(1);
}