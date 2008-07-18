/*
Filename ******** DAC.h **************
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
--------------------DAC_Init-------------------
Initializes the SPI protocol
Input: none
Output: none
*/
void DAC_Init(void);


/*
--------------------DAC_Out-------------------
Sends a new data value to the DAC
Input: unsigned short
Output: none
*/
void DAC_Out(unsigned short data);

