// Filename ******** Music.h ************** 
// Authors: Yoni Ben-Meshulam ,Milton Villeda
// Music functions implementation, Mario Bros song
// Lab #6
// TA: Sandy
// File created: 10/13/2007
// File updated: 10/16/2007
// Hardware configuration: N/A

 
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

#define silence 0;

struct NoteStruct{
  short pitch;
  short duration; // in sixteenth notes
};

typedef const struct NoteStruct Note; 

struct InstrumentStruct{
  Note* notes;
  short numNotes;
};

typedef const struct InstrumentStruct Instrument;

struct MusicStruct{
  short tempo;
  short numInstruments;
  Instrument* instruments;
};

typedef struct MusicStruct Music;
  
const Note i1[8] = {{C3,4},{D3,4},{E3,4},{F3,4},{G3,4},{A3,4},{B3,4},{C4,4}};
const Note i2[8] = {{G2,4},{A2,4},{B2,4},{C2,4},{D2,4},{E2,4},{F2,4},{G2,4}};

const Instrument j[2] =  {{i1,8},{i2,8}};


const Music MarioBros = {
  60,
  2,
  &j
};


short Music_getNumNotes(char instr){
  return MarioBros.instruments[instr].numNotes;
}

short Music_getPitch(char instr, short index){
  return MarioBros.instruments[instr].notes[index].pitch;
}

short Music_getDuration(char instr, short index){
  return MarioBros.instruments[instr].notes[index].duration;
}

short Music_getTempo(void){
  return MarioBros.tempo;
}

short Music_getNumInstr(void){
  return MarioBros.numInstruments;
}


