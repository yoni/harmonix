/*
 * ************************ adc.h *****************************
 * Jonathan W. Valvano   8/15/06
 * Simple I/O routines ADC port
 * ************************************************************

 Copyright 2006 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
*/

/*
Filename ******** ADC.h **************
Authors: Jonathan Valvano
Revised by: Yoni Ben-Meshulam ,Milton Villeda
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


/*
******** ADC_Init ***************
Initialize ADC, sequence length=1, 10-bit mode
input: none
output: none
errors: none
*/
void ADC_Init(void);

/*
******** ADC_In ***************
 perform 10-bit analog to digital conversion
 input: chan is 0 to 7 specifying analog channel to sample, pointer to array of four chars
 output: four 10-bit ADC sample (left justified)

*/
void ADC_In(unsigned char chan, unsigned char* data);

