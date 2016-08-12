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

#define ICE40_SPI_SCK_TRIS TRISDbits.TRISD10 // on riser card
#define ICE40_SPI_MISO_TRIS TRISCbits.TRISC4 // on riser card
#define ICE40_SPI_MOSI_TRIS TRISDbits.TRISD0 // on riser card
#define ICE40_SPI_CS_TRIS TRISDbits.TRISD9 // on riser card
#define ICE40_SPI_CS_LAT LATDbits.LATD9 // on riser card
#define ICE40_CRESET_TRIS TRISCbits.TRISC1 // on riser card
#define ICE40_CRESET_LAT LATCbits.LATC1 // on riser card
#define ICE40_CDONE_TRIS TRISCbits.TRISC2 // on riser card
#define ICE40_CDONE_PORT PORTCbits.RC2 // on riser card

/*
#define ice40_SPI_CHANNEL SPI_CHANNEL2

#define ICE40_SPI_SCK_TRIS TRISGbits.TRISG6 // on riser card
#define ICE40_SPI_MISO_TRIS TRISGbits.TRISG7 // on riser card
#define ICE40_SPI_MOSI_TRIS TRISGbits.TRISG8 // on riser card
#define ICE40_SPI_CS_TRIS TRISGbits.TRISG9 // on riser card
#define ICE40_SPI_CS_LAT LATGbits.LATG9 // on riser card
#define ICE40_CRESET_TRIS TRISCbits.TRISC1 // on riser card
#define ICE40_CRESET_LAT LATCbits.LATC1 // on riser card
#define ICE40_CDONE_TRIS TRISCbits.TRISC2 // on riser card
#define ICE40_CDONE_PORT PORTCbits.RC2 // on riser card
*/

int ice40Init(void);
int ice40SendBitstream(char* bitstreamToSend, int len);
int ice40IsConfigured(void);

int ice40Init(void)
{
    //configure GPIO for SPI and ice40 control signals.
    ICE40_SPI_SCK_TRIS = 0;
    ICE40_SPI_MISO_TRIS = 0;
    ICE40_SPI_MOSI_TRIS = 0;
    ICE40_SPI_CS_TRIS = 0;
    ICE40_CRESET_TRIS = 0;
    ICE40_CDONE_TRIS = 1;

    //configure SPI master port.
    //SpiChnOpen(ice40_SPI_CHANNEL, (SPI_OPEN_MSTEN | SPI_OPEN_CKP_HIGH), 1);
    
    int i = SPI1BUF; //clear SPI buffer
    SPI1BRG = 1; //Fpb/4
    SPI1STATbits.SPIROV = 0; //clear overflow bit
    SPI1CONbits.MSTEN = 1;
    SPI1CONbits.ON = 1;

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
        SPI1BUF = *(c++);
    }

    //check FPGA for CDONE.
    if(ICE40_CDONE_PORT)
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
    return ICE40_CDONE_PORT;
}
