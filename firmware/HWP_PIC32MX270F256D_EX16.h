/* 
 * File:   HWP_PIC32MX270F256_EX16.h
 * Author: ufanders
 *
 * Created on August 13, 2016, 3:54 PM
 */

#ifndef HWP_PIC32MX270F256_EX16_H
#define HWP_PIC32MX270F256_EX16_H

#ifdef	__cplusplus
extern "C" {
#endif

#define VERSION_HARDWARE_MAJOR 'E'
#define VERSION_HARDWARE_MINOR 16

// Set configuration fuses (but only in Main.c where SET_CONFIG_FUSES is defined)
#if defined(SET_CONFIG_FUSES)

    #pragma config FPLLMUL  = MUL_20        // PLL Multiplier
    #pragma config FPLLIDIV = DIV_2 //DIV_4         // PLL Input Divider
    #pragma config FPLLODIV = DIV_2 //DIV_1         // PLL Output Divider
    #pragma config FPBDIV   = DIV_1         // Peripheral Clock divisor
    #pragma config WDTPS    = PS1           // Watchdog Timer Postscale
    #pragma config FCKSM    = CSDCMD        // Clock Switching & Fail Safe Clock Monitor
    #pragma config OSCIOFNC = OFF           // CLKO Enable
    #pragma config POSCMOD  = HS            // Primary Oscillator
    #pragma config IESO     = OFF           // Internal/External Switch-over
    #pragma config FSOSCEN  = ON           // Secondary Oscillator Enable
    #pragma config FNOSC    = PRIPLL        // Oscillator Selection

    #ifdef __DEBUG
        #pragma config CP       = OFF       // Code Protect
        #pragma config FWDTEN   = OFF       // Watchdog Timer
    #else
        #pragma config CP       = OFF        // Code Protect
        #pragma config FWDTEN   = OFF        // Watchdog Timer
    #endif

    #pragma config BWP      = OFF           // Boot Flash Write Protect
    #pragma config PWP      = OFF           // Program Flash Write Protect
    #pragma config ICESEL   = ICS_PGx4      // ICE/ICD Comm Channel Select
    #pragma config DEBUG    = ON            // Background Debugger Enable
    #pragma config IOL1WAY = OFF                    // Multiple PPS configs ok
    #pragma config PMDL1WAY = OFF
    #pragma config FUSBIDIO = OFF
    #pragma config FVBUSONIO = OFF
    #pragma config JTAGEN = OFF

#endif

// Clock frequency values
// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
#define GetSystemClock()	(40000000ul)		// Hz
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.

// Hardware I/O pin mappings
#define ice40_CDONE BIT_1
#define ice40_CRESET_B BIT_2
#define ice40_SPI_SI BIT_3
#define ice40_SPI_SO BIT_4
#define ice40_SPI_SS BIT_5
#define ice40_SPI_SCK BIT_6
    
#define DISABLE_ALL_ANALOG_PINS ANSELA = 0; ANSELB = 0; ANSELC = 0

#define ice40_SPI_CHANNEL SPI_CHANNEL1

#define ICE40_SPI_SCK_TRIS TRISBbits.TRISB14 // on riser card
#define ICE40_SPI_SCK_LAT LATBbits.LATB14 // on riser card
#define ICE40_SPI_MISO_TRIS TRISBbits.TRISB1 // on riser card
#define ICE40_SPI_MOSI_TRIS TRISBbits.TRISB5 // on riser card
#define ICE40_SPI_MOSI_LAT LATBbits.LATB5 // on riser card
#define ICE40_SPI_CS_TRIS TRISBbits.TRISB4 // on riser card
#define ICE40_SPI_CS_LAT LATBbits.LATB4 // on riser card
#define ICE40_CRESET_TRIS TRISAbits.TRISA0 // on riser card
#define ICE40_CRESET_LAT LATAbits.LATA0 // on riser card
#define ICE40_CDONE_TRIS TRISAbits.TRISA1 // on riser card
#define ICE40_CDONE_PORT PORTAbits.RA1 // on riser card
    
/*
 * B1 - SDI1
 B4 - SS1
 * B5 - SDO1
 * B14 - SCK1
 */

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

#ifdef	__cplusplus
}
#endif

#endif	/* HWP_PIC32MX270F256_EX16_H */

