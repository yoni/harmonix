// filename ******** Main.C ************** 
// Music Player
// Yoni Ben-Meshulam
// Milton Villeda
// 10/1/07
// Lab #6
// TA: Sandy
// File created: 10/9/2007
// File updated: 10/16/2007
// Hardware configuration: DAC, amplifier, speaker


/* To do:

1) implement envelope
2) implement layering of up to four tones (for chords, or notes)
3) correct all numbers for 6811 frequency
4) update switch.c to accomodate for music keys and harmony switch
5) implement dial.c, dial.h to input key and octave dials
6) add scales.h, scales.c for music scales using tone increments (i.e. major = {0,2,2,1,2,2,2,1}, minor = {0,2,2,2,1,2,2,1}, etc.)
7) add chords.h, chords.c for chords corresponding to scale (i.e. major = {{1,3,5}, {2,4,6}, etc.}, for example in C-major, the first chord is c-major = {C,E,G}, the second is D-minor = {D,F,A})
8) change music.c, music.h to notes.c, notes.h to reflect the notes we need (this is abstracted from scales and chords, hence the separate files)

*/




#include <hidef.h>      /* common defines and macros */
#include <mc9s12c32.h>  /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c32"

#include "DAC.h" 
#include "Switch.h"
#include "SCI.H"
#include "Music.h"


const unsigned short CLOCK_DIV_WAVE = 46852; // (1/TCNT_period)/32, where 32 is the number of elements in the sine wave
unsigned short Out1 = 0; // current frequency output of instrument 1
unsigned short Out2 = 0; // current frequency output of instrument 1
unsigned short I1; // keeps track of note for Instrument 1
unsigned short I2; // keeps track of note for Instrument 2

unsigned short Beat; // counter for song beats
unsigned long BeatTime;
char FIRST_RUN = 1; // used in PlayMusic function
char PlayEn = 1; // CHANGE THIS to '0' after we implement the user controls
char Rewind = 0;
char Stop = 0;


unsigned char W1; // keeps track of wave index for Instr1
unsigned char W2; // keeps track of wave index for Instr2


const unsigned short wave[32] = {
  2048,2438,2813,3159,3462,3711,3896,4010,4048,4010,
  3896,3711,3462,3159,2813,2438,2048,
  1658,1283,937,634,385,200,86,48,86,200,385,634,937,1283,1658
};


//--------------------TimerInit---------------
// initialize timer module to 0.667us(Boot Mode) TCNT clock
// inputs: none
// outputs: none
void TimerInit(void){
  TSCR1 = 0x80;   // Enable TCNT, 24MHz in both boot and run modes
  TSCR2 = 0x04;   // divide by 16 TCNT prescale, TCNT at 667nsec	  //x04
  PACTL = 0;      // timer prescale used for TCNT

}
/* 
Bottom three bits of TSCR2 (PR2,PR1,PR0) determine TCNT period
    divide  24MHz E clock    
000   1     42ns  TOF  2.73ms  
001   2     84ns  TOF  5.46ms   
010   4    167ns  TOF  10.9ms       
011   8    333ns  TOF  21.8ms 	 
100  16    667ns  TOF  43.7ms 	 
101  32   1.33us  TOF  87.4ms		 
110  64   2.67us  TOF 174.8ms   
111 128   5.33us  TOF 349.5ms    
// Be careful, TSCR1 and TSCR2 maybe set in other rituals
*/


void Music_Init(void){
  //Setup timer interrupt for MusicPlayer
  TIOS |= 0x01; //activate OC0
  TIE |= 0x01; // arms C0I = 1
  TC0 = TCNT + 50; // specify time for first interrupt
  //Setup timer interrupt for Instrument 1:
  TIOS |= 0x02; //activate OC1
  TIE |= 0x02; // arms C1I = 1
  TC1 = TCNT + 50; // specify time for first interrupt

  if(Music_getNumInstr() > 1){  //For now, we ignore more than two instruments
    //Setup timer interrupt for Instrument 2:
    TIOS |= 0x04; //activate OC2
    TIE |= 0x04; // arms C2I = 1
    TC2 = TCNT + 50; // specify time for first interrupt
  }
  BeatTime = ((Music_getTempo()/60)*(1499250))/32 ; // (bpm/60)*(1/667ns)=bps*TCNT_cycles_ps, (beat = one quarter note)
}


void getUserInput(void){
  char sw = Switch_Get();
  switch(sw){
    case 0:
      Rewind = 0;
      Stop = 0;
      break;
    case 1:
      Rewind = 1;
      PlayEn = 0;
      Stop = 0;
      break;
    case 2:
      PlayEn = 1;
      Rewind = 0;
      Stop = 0;
      break;
    case 3:
      PlayEn = 1;
      Rewind = 1;
      Stop = 0;
      break;
    case 4:
      Stop = 1;
      PlayEn = 0;
      break;
    default:
      break;
  }
}
   
// MusicPlayer
// Keeps track of the song, and runs user controls
interrupt 8 void MusicPlayer(void){
  static char count1;
  static char count2;

  static char beatCount;

  // Generate Beat
  TC0 += BeatTime;
  TFLG1 = 0x01; // ack
  //Beat++;

  // Implement User Controls
  if(FIRST_RUN){
    I1 = 0; I2 = 0;
    FIRST_RUN = 0;
    beatCount = 0;
    return;
  }
  if(Rewind&&PlayEn){
    if(I1 > 0){ I1--;} else I1 = 0;
    if(I2 > 0){ I2--;} else I2 = 0;
    count1 = 0;
    count2 = 0;
  }else if(Rewind){
    I1 = 0; I2 = 0;
    count1 = 0;
    count2 = 0;
  }
  if(Stop){
    PlayEn = 0;
    return;
  }
  
  if(PlayEn){

    if(beatCount!= 8){
      beatCount++;
      return;
    }
		beatCount = 0;
		
    // increment instrument indexes according to their durations
    count1++; count2++;
    if(Music_getDuration(0,I1) == count1){
      I1 = (I1+1)%(Music_getNumNotes(0)); //wraps around at the end of the song wraps around
      count1 = 0;
    }
    if(Music_getNumInstr() > 1){
      if((Music_getDuration(1,I2) == count2)){
        I2 = (I2+1)%(Music_getNumNotes(1));
        count2 = 0;
      }
    }
  }
}

interrupt 9 void Instr1Out(void){
  TC1 += CLOCK_DIV_WAVE/Music_getPitch(0,I1);
  TFLG1 = 0x02; // ack
  W1 = (W1+1)&0x1F; // 0 to 31
  Out1 = (1/2)*wave[W1]; // 0 to 31
  DAC_Out(Out1+Out2);
}

interrupt 10 void Instr2Out(void){
  TC2 += CLOCK_DIV_WAVE/Music_getPitch(1,I2);
  TFLG1 = 0x04; // ack
  W2 = (W2+1)&0x1F; // 0 to 31
  Out2 = (1/2)*wave[W2]; // 0 to 31
  DAC_Out(Out1+Out2);
}





void main(void) {
  long i = 0;
  PLL_Init();       // set E clock to 24 MHz
  TimerInit();
  Music_Init();
  Switch_Init();
  DAC_Init();
  asm cli   // allows debugger to run
  while(1){}
}
