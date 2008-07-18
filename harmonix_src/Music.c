/*
  Filename ******** Music.c **************
  Authors: Yoni Ben-Meshulam ,Milton Villeda
  Implements interface for accessing musical notes.
  "Harmonix" project
  TA: Sandy
  File created: 11/29/2007
  File updated: 02:30 11/30/2007
  Hardware configuration: N/A
*/

 
#define C1 33
#define Csh1 35
#define D1 37
#define Dsh1 39
#define E1 41
#define F1 44
#define Fsh1 46
#define G1 49
#define Gsh1 52
#define A1 55
#define Ash1 58
#define B1 62
#define C2 65
#define Csh2 69
#define D2 73
#define Dsh2 78
#define E2 82
#define F2 87
#define Fsh2 93
#define G2 98
#define Gsh2 104
#define A2 110
#define Ash2 117
#define B2 123
#define C3 131
#define Csh3 139
#define D3 147
#define Dsh3 156
#define E3 165
#define F3 175
#define Fsh3 185
#define G3 196
#define Gsh3 208
#define A3 220
#define Ash3 233
#define B3 247
#define C4 262
#define Csh4 277
#define D4 294
#define Dsh4 311
#define E4 330
#define F4 349
#define Fsh4 370
#define G4 392
#define Gsh4 415
#define A4 440
#define Ash4 466
#define B4 494
#define C5 523
#define Csh5 554
#define D5 587
#define Dsh5 622
#define E5 659
#define F5 698
#define Fsh5 740
#define G5 784
#define Gsh5 831
#define A5 880
#define Ash5 932
#define B5 988

#define NUM_NOTES = 60;
#define NUM_SCALES = 3;

const Notes[NUM_NOTES] = {
  C1,Csh1,D1,Dsh1,E1,F1,Fsh1,G1,Gsh1,A1,Ash1,B1,
  C2,Csh2,D2,Dsh2,E2,F2,Fsh2,G2,Gsh2,A2,Ash2,B2,
  C3,Csh3,D3,Dsh3,E3,F3,Fsh3,G3,Gsh3,A3,Ash3,B3,
  C4,Csh4,D4,Dsh4,E4,F4,Fsh4,G4,Gsh4,A4,Ash4,B4,
  C5,Csh5,D5,Dsh5,E5,F5,Fsh5,G5,Gsh5,A5,Ash5,B5,
}

struct ScaleStruct{
  short numNotes; /* the number of notes in the scale */
  short increments[]; /* the pattern of increments */
};

typedef const struct ScaleStruct Scale;


const Scale MAJOR_PENTATONIC = {5,{0,2,4,7,9}};
const Scale ORIENTAL = {5,{0,2,5,9,10}};
const Scale HUNGARIAN_GYPSY = {7,{0,2,3,6,7,8,10}};


const Scale[NUM_SCALES] = {MAJOR_PENTATONIC,ORIENTAL, HUNGARIAN_GYPSY};

/*
******** Music_getPitch ***************
 Returns the pitch of the required note
 inputs:
   keyPressed: value between 1-10 representing which key has been pressed
   key: value between 0-11 representing the key in which we are playing
   scale: value between 0 and 3 representing which scale we are playing in
   octave: value between 1 and 5 representing which octave we are playing in
 output: frequency of the note
 errors: returns 0 if values are out of bounds
 comments: octave wraps around in the case of a scale which has a small number of notes
           this will be a nice "feature"
*/
short Music_getPitch(unsigned char keyPressed,unsigned char key,unsigned char scale,unsigned char octave);
  char increment;
  char notesInScale;
  char noteIndex = 0;
  char note;

  /* error checking */
  if(keyPressed < 1 || keyPressed > 10
       || key > 11
       || scale > NUM_SCALES
       || octave < 1 || octave > 5){
    return 0;
  }

  notesInScale = Scales[scale].numNotes;
  increment = Scales[scale].increments[keyPressed%notesInScale];

  octave += keyPressed/notesInScale;
  /*
    example:
     if key pressed is 10, and the number of notes in the scale is 3
     then we need to jump 10/3 = 3 octaves
  */
  noteIndex = increment; /* note in scale */
  noteIndex += (octave-1)*12; /* jump to octave */
  noteIndex += key; /* transcribe the key */
  noteIndex %= NUM_NOTES; /* wraps around if octave too high */

  note = Notes[noteIndex];
  return note;
}

