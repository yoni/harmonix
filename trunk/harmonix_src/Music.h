/*
  Filename ******** Music.h **************
  Authors: Yoni Ben-Meshulam ,Milton Villeda
  Interface for accessing musical notes.
  "Harmonix" project
  TA: Sandy
  File created: 11/29/2007
  File updated: 02:30 11/30/2007
  Hardware configuration: N/A
*/


/*
******** Music_getPitch ***************
 Returns the pitch of the required note
 inputs:
   keyPressed: value between 1-10 representing which key has been pressed
   key: value between 0-11 representing the key in which we are playing
   scale: value between 0 and 2 representing which scale we are playing in
   octave: value between 1 and 5 representing which octave we are playing in
   
 output: frequency of the note
 errors: returns 0 if values are out of bounds
*/
short Music_getPitch(char keyPressed, char key,char scale,char octave);

