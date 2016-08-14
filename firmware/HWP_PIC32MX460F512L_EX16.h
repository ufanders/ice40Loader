/* 
 * File:   HWP_PIC32MX460F512L_EX16.h
 * Author: ufanders
 *
 * Created on August 13, 2016, 4:40 PM
 */

#ifndef HWP_PIC32MX460F512L_EX16_H
#define	HWP_PIC32MX460F512L_EX16_H

#ifdef	__cplusplus
extern "C" {
#endif

#define VERSION_HARDWARE_MAJOR 'E'
#define VERSION_HARDWARE_MINOR 16

// Set configuration fuses (but only in Main.c where SET_CONFIG_FUSES is defined)
#if defined(SET_CONFIG_FUSES)

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

#endif

// Clock frequency values
// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
#define GetSystemClock()	(80000000ul)		// Hz
#define GetInstructionClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/1)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.

//Firmware block inclusions
//Microchip Technology "MPFS2" filesystem
#define STACK_USE_MPFS2
#define MPFS_USE_SPI_FLASH
#define MAX_MPFS_HANDLES 1

//Framesync timer mapping
#define FRAMESYNC_TIMER_PERIOD PR1
#define FRAMESYNC_TIMER_CONBITS T1CONbits
    
#define DISABLE_ALL_ANALOG_PINS AD1PCFG = 0xFFFFFFFF

// Hardware I/O pin mappings
//SPI
#define LED_SPI_SCK_TRIS TRISBbits.TRISB14 //RC2 on riser card
#define LED_SPI_MOSI_TRIS TRISBbits.TRISB5 //RG14 on riser card
#define LED_SPI_CS_TRIS TRISBbits.TRISB7 //RE5 on riser card
#define LED_SPI_SCK_LAT LATBbits.LATB14
#define LED_SPI_MOSI_LAT LATBbits.LATB5
#define LED_SPI_CS_LAT LATBbits.LATB7

#define MEM_SPI_SCK_TRIS TRISBbits.TRISB14 // on riser card
#define MEM_SPI_MOSI_TRIS TRISBbits.TRISB1 // on riser card
#define MEM_SPI_CS_TRIS TRISBbits.TRISB2 // on riser card
#define MEM_SPI_SCK_LAT LATBbits.LATB14
#define MEM_SPI_MOSI_LAT LATBbits.LATB1
#define MEM_SPI_CS_LAT LATBbits.LATB2

#define SPIFLASH_CS_TRIS	TRISBbits.TRISB11
#define SPIFLASH_CS_IO		LATBbits.LATB11
#define SPIFLASH_SCK_TRIS	TRISBbits.TRISB15
#define SPIFLASH_SDI_TRIS	TRISCbits.TRISC3
#define SPIFLASH_SDI_IO		LATCbits.LATC3
#define SPIFLASH_SDO_TRIS	TRISBbits.TRISB13
#define SPIFLASH_SPI_IF		IFS1bits.SPI2RXIF
#define SPIFLASH_SSPBUF		SPI2BUF
#define SPIFLASH_SPICON1	SPI2CON
#define SPIFLASH_SPICON1bits	SPI2CONbits
#define SPIFLASH_SPISTATbits	SPI2STATbits
#define SPIFLASH_SPIBRG		SPI2BRG

//UART
#define UART_RX_TRIS TRISCbits.TRISC1 //RB11 on riser card
#define UART_TX_TRIS TRISBbits.TRISB3 //RD4 on riser card

//CONTROL LINES
#define BT_RESET_TRIS TRISAbits.TRISA0 //RE7 on riser card
#define BT_RESET_LAT LATAbits.LATA0
#define BT_CONNECTED_TRIS TRISAbits.TRISA1 //RE6 on riser card
#define BT_CONNECTED_PORT PORTAbits.RA1

#define CPLD_RESET_TRIS TRISAbits.TRISA8 //RD1 on riser card
#define CPLD_RESET_LAT LATAbits.LATA8
#define CPLD_CLK_TRIS TRISCbits.TRISC0 //RB10 on riser card
#define CPLD_CLK_LAT LATCbits.LATC0

#define SLOW_CLK_TRIS TRISCbits.TRISC6 // on riser card
#define SLOW_CLK_ODC ODCCbits.ODCC6
#define SLOW_CLK_RP_REG RPC6R

//BUTTONS
#define SW_BUTTON_1_TRIS TRISCbits.TRISC9 //RG13 on riser card
#define SW_BUTTON_1_PORT PORTCbits.RC9
#define SW_BUTTON_1_PU CNPUCbits.CNPUC9

//EEPROM LINES
#define EEPROM_CS_TRIS	TRISCbits.TRISC2 //RG6 on riser card
#define EEPROM_CS_LAT	LATCbits.LATC2


#ifdef	__cplusplus
}
#endif

#endif	/* HWP_PIC32MX460F512L_EX16_H */

