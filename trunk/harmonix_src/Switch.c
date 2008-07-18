// Filename ******** Switch.c ************** 
// Authors: Yoni Ben-Meshulam ,Milton Villeda
// Interfaces with four switches
// Lab #4
// TA: Sandy
// File created: 10/1/2007
// File updated: 10/2/2007
// Hardware configuration: Stepper Motor and four switches


//--------------------Switch_Get-------------------
// Checks for user input
// Input: 1, 2, 3, 4 - represent SW1, SW2, SW3, SW4
// Output: 1 if SW4 pressed, 2 if SW3 pressed, 
//         4 if SW2 pressed, 8 if SW1 pressed,
//         12 if SW1 & SW2 pressed
#include <mc9s12c32.h>  /* derivative information */

char Switch_Get(void){
  char switches=PTT&0x0F;
  return switches;

}

//--------------------Switch_Init-------------------
// initialize Switches
// Input: none
// Output: none

void Switch_Init(void){
  DDRT = 0x00; // PortT are inputs. We use only [0,3]
}