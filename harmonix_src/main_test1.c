// filename ******** Main_Test.C ************** 
// Stepper Motor and Switches on PTT, PTM
// Yoni Ben-Meshulam
// Milton Villeda
// 10/1/07
// Lab #4
// TA: Sandy
// File created: 10/1/2007
// File updated: 10/9/2007
// Hardware configuration: Stepper Motor and four switches



#include <hidef.h>      /* common defines and macros */
#include <mc9s12c32.h>  /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c32"

#include "PLL.h"
#include "DAC.h" 
#include "SCI.h"



void main_3(void) {
  unsigned short number;
  DAC_Init();
  DAC_Out(12);
  while(1) {
    //
  }
}

//dynamic testing. generates a triangle waveform
void main_1(void) {
  unsigned short n;
  PLL_Init();
  DAC_Init();
  while(1) {
    for(n=0; n<4096; n++){// up 0 to 4095
      DAC_Out(n); //output to SPI
    }
    for(n=4094; n > 0; n--){// down 4094 to 1
      DAC_Out(n); //output to SPI
    }
  }
}
