// File **********OC3.C***********
// 1000 Hz Periodic Interrupt using TOC3

//  This example accompanies the books
//   "Embedded Microcomputer Systems: Real Time Interfacing", Brooks-Cole, copyright (c) 2000,
//   "Introduction to Embedded Microcomputer Systems: 
//    Motorola 6811 and 6812 Simulation", Brooks-Cole, copyright (c) 2002,
//    Jonathan W. Valvano 2/17/04

// You may use, edit, run or distribute this file 
//    as long as the above copyright notices remain 
#include <mc9s12c32.h>     /* derivative information */

 
unsigned short static volatile Count;
unsigned short static Period;
void (*CallBack)(void);  // call back function
#define RATE 1500  

interrupt 11 void TOC3handler(void){ // executes at 1000 Hz 
  TFLG1 = 0x08;         // acknowledge OC3
  Count++;
  TC3 = TC3+RATE;       // 1 ms
  if(Count==Period){
    Count = 0;
    (*CallBack)();      // execute call back process
  } 
}

//---------------------OC_Start---------------------
// arm output compare 3 for 1000Hz periodic interrupt
// Input: thePeriod is a time period in ms
//        fp is a function to be executed at this period
// Output: none 
// example
//   void toggle(void){PTT^=0x01;}
//   OC_Start(100,&toggle);
void OC_Start(unsigned short thePeriod, void(*fp)(void)){
  asm sei      // make ritual atomic 
  Period = thePeriod;
  CallBack = fp;
  Count  = 0;
  TIOS  |= 0x08;  // activate TC3 as output compare
  TSCR1 = 0x80;   // Enable TCNT, 24MHz boot mode, 4MHz in run mode
  TSCR2 = 0x04;   // divide by 128 TCNT prescale, TOI disarm
  PACTL = 0;      // timer prescale used for TCNT
/* Bottom three bits of TSCR2 (PR2,PR1,PR0) determine TCNT period
    divide  FastMode(24MHz)    Slow Mode (4MHz)
000   1     42ns  TOF  2.73ms  250ns TOF 16.384ms
001   2     84ns  TOF  5.46ms  500ns TOF 32.768ms 
010   4    167ns  TOF  10.9ms    1us TOF 65.536ms   
011   8    333ns  TOF  21.8ms 	 2us TOF 131.072ms
100  16    667ns  TOF  43.7ms 	 4us TOF 262.144ns
101  32   1.33us  TOF  87.4ms		 8us TOF 524.288ms
110  64   2.67us  TOF 174.8ms   16us TOF 1.048576s
111 128   5.33us  TOF 349.5ms   32us TOF 2.097152s */ 
  TIE  |= 0x08;    // arm OC3
  TC3    = TCNT+50; // first interrupt right away
  asm cli
}
