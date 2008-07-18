/*
Filename ******** ACD.c **************
Authors: Yoni Ben-Meshulam ,Milton Villeda
"Harmonix" project
TA: Sandy
File created: 11/29/2007
File updated: 02:30 11/30/2007
Hardware configuration:
  HD6811 Motorola microcontroller
  8kB EEPROM at $E000
  ADC converter
  DAC converter
  Amplifier
  10 switches (10 music keys, one harmony selector),
  two LED's: one power led (hard-wired to power source), one harmony LED
  four potentiometers: three linear (key selector, octave selector, scale selector), one logarithmic (volume selector - hard-wired to amplifier)

  PA7: Key 9 (switch)
  PA6: Harmony indicator (LED)
  PA5: (unused)
  PA4: (unused)
  PA3: Key 8 (switch)
  PA2: Key 7 (switch)
  PA1: Key 6 (switch)
  PA0: Key 5 (switch)
  PE7: Key 4 (switch)
  PE6: Key 3 (switch)
  PE5: Key 2 (switch)
  PE4: Key 1 (switch)
  PE3: Harmony Selector (switch)
  PE2: Octave selector (linear potentiometer)
  PE1: Scale selector (linear potentiometer)
  PE0: Key Selector (linear potentiometer)

*/




#include <mc9s12c32.h>  /* derivative information */
#include "ADC.h"

/*
******** ADC_In ***************
 perform 10-bit analog to digital conversion
 input: chan is 0 to 7 specifying analog channel to sample, pointer to array of four shorts
 output: four 10-bit ADC sample (left justified)

*/
void ADC_In(unsigned char chan, unsigned char* data){
  /*
   bit 7 CCF conversion complete flag, read only, cleared by writing data to the ADCTL
   bit 5 SCAN=0 starts a single-sequence conversion, 1 starts a continuous sequence conversion
   bit 4 MULT=1 multiple channel=1 single channel=0
   bit 3 CD = 0 start conversion with channel 0 (PE0)
   bit 2 CC = 0
   bit 1 CB = 0
   bit 0 CA = 0
  */
  ATDCTL = 0x10 + (unsigned char) chan; /* start sequence */

  while((ATDCTL&0x80)==0){};    /* wait for CCF */
  /* retrieve data */
  data[0] = ADR1;
  data[1] = ADR2;
  data[2] = ADR3;
  data[3] = ADR4;
}

/*
******** ADC_Init ***************
 Initialize ADC, sequence length=1, 10-bit mode
 input: none
 output: none
 errors: none
*/
void ADC_Init(void){
  OPTION |= 0xC0;
  /*
   bit 7 ADPU=1 enable ADC conversion
   bit 6 CSEL=1 for E clock frequencies below 750 KHz
  */
}
