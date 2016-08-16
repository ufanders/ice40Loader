//this file implements a loader to configure a Lattice ice40 FPGA.
#include "HardwareProfile.h"
#include <plib.h>
#include "TimeDelay.h"

int ice40Init(void);
int ice40SendBitstream(char* bitstreamToSend, int len);
int ice40IsConfigured(void);
int softSpi(unsigned int c, unsigned char bits);

int ice40Init(void)
{
    //configure GPIO for SPI and ice40 control signals.
    ICE40_SPI_SCK_ODC = 1;
    //ICE40_SPI_MOSI_ODC = 1;
    //ICE40_SPI_CS_ODC = 1;
    ICE40_CRESET_ODC = 1;
    
    ICE40_SPI_SCK_TRIS = 0;
    ICE40_SPI_MISO_TRIS = 0;
    ICE40_SPI_MOSI_TRIS = 0;
    ICE40_SPI_CS_TRIS = 0;
    ICE40_CRESET_TRIS = 0;
    ICE40_CDONE_TRIS = 1;

    //configure SPI master port.
    //SpiChnOpen(ice40_SPI_CHANNEL, (SPI_OPEN_MSTEN | SPI_OPEN_CKP_HIGH), 1);
    
    /*
    int i = SPI1BUF; //clear SPI buffer
    SPI1BRG = 16; //Fpb/4*16
    SPI1STATbits.SPIROV = 0; //clear overflow bit
    SPI1CONbits.MSTEN = 1;
    SPI1CONbits.ON = 1;
     */

    return 0;
}

int ice40Configure(char* bitstreamToSend, int len)
{
    ICE40_CRESET_LAT = 0;
    ICE40_SPI_CS_LAT = 0;
   
    //wait 200ns.
    int i;
    i = 16;
    while(i--);
    
    ICE40_CRESET_LAT = 1;
    
    //wait 300us.
    i = 24000;
    while(i--);

    //send bitstream.
    char* c = bitstreamToSend;
    while(len--)
    {
        /*
        if(len == 1)
        {
            len = 1;
        }
         */
        //SPI1BUF = *(c++);
        softSpi(*(c++), 8);
    }

    //check FPGA for CDONE.
    if(ICE40_CDONE_PORT)
    {
        //send at least 49 dummy bits to init FPGA I/O.
        i = 7;
        while(i--)
        {
            softSpi(0xFF, 8);
        }

        return 0;
    }
    
    return 1;
}

int ice40IsConfigured(void)
{
    return ICE40_CDONE_PORT;
}

int softSpi(unsigned int c, unsigned char bits)
{
    unsigned int i, shiftReg;
    
    shiftReg = c;
    
    for(i=0; i<bits; i++)
    {
        if(shiftReg & 0x80)
        {
            ICE40_SPI_MOSI_LAT = 1;
        }
        else
        {
            ICE40_SPI_MOSI_LAT = 0;
        }

        ICE40_SPI_SCK_LAT = 1;
        ICE40_SPI_SCK_LAT = 0;

        shiftReg <<= 1;
    }
    
    return 0;
}