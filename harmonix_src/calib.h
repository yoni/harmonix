/*
Filename ******** calib.h **************
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


/* Calibration paramaters for potentiometers

 Measured data:   Potentiometer angle:
                  Resistance:

*/
#define C  0
#define Cs 1
#define D  2
#define Ds 3
#define E  4
#define F  5
#define Fs 6
#define G  7
#define Gs 8
#define A  9
#define As 10
#define B  11


/* Note: Key refers to musical key (C, C#, D, D#, E, F, etc.), not keyboard */
unsigned short const KeyADCData[12]={0,23,46,70,93,116,139,162,185,209,232,255}; /* assuming perfect linearity, need to test this */
unsigned short const KeyValueData[12]={C,Cs,D,Ds,E,F,Fs,G,Gs,A,As,B);
unsigned short const OctaveADCData[5]={0,64,128,191,255}; /* assuming perfect linearity, need to test this */
unsigned short const OctaveValueData[5]={1,2,3,4,5};
unsigned short const ScaleADCData[3]={0,128,255}; /* assuming perfect linearity, need to test this */
unsigned short const ScaleValueData[3]={0,1,2};

