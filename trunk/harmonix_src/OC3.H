// File **********OC3.H***********
// 1000 Hz Periodic Interrupt using TOC3

//  This example accompanies the books
//   "Embedded Microcomputer Systems: Real Time Interfacing", Brooks-Cole, copyright (c) 2000,
//   "Introduction to Embedded Microcomputer Systems: 
//    Motorola 6811 and 6812 Simulation", Brooks-Cole, copyright (c) 2002,
//    Jonathan W. Valvano 2/17/04

// You may use, edit, run or distribute this file 
//    as long as the above copyright notices remain 

//---------------------OC_Start---------------------
// arm output compare 3 for 1000Hz periodic interrupt
// Input: thePeriod is a time period in ms
//        fp is a function to be executed at this period
// Output: none 
// example
//   void toggle(void){PORTT^=0x40;}
//   OC_Start(100,&toggle);
void OC_Start(unsigned short Period, void(*fp)(void));

