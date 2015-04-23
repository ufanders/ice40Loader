//this file implements a loader to configure a Lattice ice40 FPGA.

#include <plib.h>
#include "TimeDelay.h"

#define ice40_CDONE BIT_1
#define ice40_CRESET_B BIT_2
#define ice40_SPI_SI BIT_3
#define ice40_SPI_SO BIT_4
#define ice40_SPI_SS BIT_5
#define ice40_SPI_SCK BIT_6

#define ice40_SPI_CHANNEL SPI_CHANNEL1

int ice40Init(void);
int ice40SendBitstream(char* bitstreamToSend, int len);
int ice40IsConfigured(void);

//the FPGA bitstream (compiled HDL), stored somewhere.
const char bitstream[] = "123456789";

int ice40Init(void)
{
    //configure GPIO for SPI and ice40 control signals.
    mPORTAClearBits(ice40_SPI_SS);

    mPORTASetBits(ice40_SPI_SS);

    mPORTASetPinsDigitalOut(ice40_CRESET_B | ice40_SPI_SO | ice40_SPI_SS \
       | ice40_SPI_SCK);

    //configure SPI master port.
    SpiChnOpen(ice40_SPI_CHANNEL, (SPI_OPEN_MSTEN | SPI_OPEN_CKP_HIGH), 1);

    return 0;
}

int ice40Configure(char* bitstreamToSend, int len)
{
    mPORTAClearBits(ice40_CRESET_B | ice40_SPI_SS);
    
    //wait 200ns.
    
    mPORTASetBits(ice40_CRESET_B);
    
    //wait 300us.

    //send bitstream.
    SpiChnPutS(ice40_SPI_CHANNEL, (unsigned int*)bitstreamToSend, len);

    //check FPGA for CDONE.
    if(mPORTAReadBits(ice40_CDONE))
    {
        //send at least 49 dummy bits to init FPGA I/O.
        //NOTE: 
        SpiChnPutS(ice40_SPI_CHANNEL, (unsigned int*)bitstreamToSend, 7);

        return 0;
    }
    
    return 1;
}

int ice40IsConfigured(void)
{
    return mPORTAReadBits(ice40_CDONE);
}
