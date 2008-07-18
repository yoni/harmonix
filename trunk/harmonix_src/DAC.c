/*
Filename ******** DAC.c **************
Authors: Yoni Ben-Meshulam ,Milton Villeda
"Harmonix" project
TA: Sandy
File created: 11/29/2007
File updated: 11/29/2007
Hardware configuration:
  HD6811 Motorola microcontroller
  8kB EEPROM at $E000
  ADC converter
  DAC converter
  Amplifier
  10 switches (10 music keys, one harmony selector),
  two LED's: one power led (hard-wired to power source), one harmony LED
  four potentiometers: three linear (key selector, octave selector, scale selector), one logarithmic (volume selector - hard-wired to amplifier)

  PORTA
  PA7: Key 9 (switch)
  PA6: Harmony indicator (LED)
  PA5, PA4: (unused)
  PA3: Key 8 (switch)
  PA2: Key 7 (switch)
  PA1: Key 6 (switch)
  PA0: Key 5 (switch)

  PORTE
  PE7: Key 4 (switch)
  PE6: Key 3 (switch)
  PE5: Key 2 (switch)
  PE4: Key 1 (switch)
  PE3: Harmony Selector (switch)
  PE2/AN2: Octave selector (linear potentiometer)
  PE1/AN1: Scale selector (linear potentiometer)
  PE0/AN0: Key Selector (linear potentiometer)

  PORTD
  PD5, PD4, PD3, PD2: (unused)
  PD1: TxD (transmit data for SPI interface)
  PD0: RxD (receive data for SPI interface)
  
*/


#include <mc9s12c32.h>  /* derivative information */
/*
--------------------DAC_Init-------------------
Initializes the SPI protocol
Input: none
Output: none
*/

void DAC_Init(void){
/*1) Make PM5, PM4, PM3 outputs*/
  DDRM_DDRM3 = 1; // set PM3 to output
  DDRM_DDRM4 = 1; // set PM4 to output
  DDRM_DDRM5 = 1; // set PM5 to output
/*2) Enable SPI, no interrupts, master, CPOL, CPHA*/
  SPICR1_SPE = 1;
  SPICR1_SPTIE = 0;
  SPICR1_MSTR = 1;
  SPICR1_CPOL = 0;
  SPICR1_CPHA = 0;
/*3) Set up PM3 as a regular output*/
  /*   SSOE = 0, MODFEN = 0 */
  SPICR1_SSOE = 0;
  SPICR2_MODFEN = 0;
/*4) Set the baud rate  BaudRateDivisor = (SPPR+1)*2^(SPR+1). BaudRate = BusClock/BaudRateDivisor */
  SPIBR_SPR = 0;
  SPIBR_SPPR = 0;
/*5) Make PM3 = CS high*/
  PTM_PTM3 = 1; /* CS high */
}

/*
--------------------DAC_Out-------------------
Sends a new data value to the DAC
Input: none
Output: none

to transmit one SPI frame:
1) wait for SPTEF to be 1
2) write 8-bit data to SPIDR (4 bits at a time)
3) wait for SPIF to be 1
4) clear the SPIF flag by reading the data: dummy = SPIDR;
*/

void DAC_Out(unsigned short data){
  char msb = (data >> 8) & 0x00FF;
  char lsb = data & 0x00FF;
  unsigned char dummy;
  dummy = SPIDR;
  dummy = SPISR;
/*  1) set PM3 = CS low  */
  PTM_PTM3 = 0;
/*  2) transmit most significant 8-bit data to the DAC */
        /* A) wait for SPTEF to be 1 */
  while(!SPISR_SPTEF){}
        /* B) write 4-bit data to SPIDR */
  SPIDR = msb;
        /* C) wait for SPIF to be 1 */
  while(!SPISR_SPIF){}
        /* D) clear the SPIF flag by reading the data: dummy = SPIDR; */
  dummy = SPIDR;
//  3) transmit least significant 8-bit data to the DAC
        /* A) wait for SPTEF to be 1 */
  while(!SPISR_SPTEF){}
        /* B) write 4-bit data to SPIDR */
  SPIDR = lsb;
        /* C) wait for SPIF to be 1 */
  while(!SPISR_SPIF){}
        /* D) clear the SPIF flag by reading the data: dummy = SPIDR; */
  dummy = SPIDR;

/*  4) set PM3=CS high*/
  PTM_PTM3 = 1;
}
