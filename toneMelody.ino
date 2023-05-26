#include "pitches.h"


#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0

#define BUZZER A5
#define BOTTON 2

struct song {
  int melody[30];
  int noteDurations[30];
  int len;
};


struct song songs[2];

const int row[] = { ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};
const int col[] = { COL1, COL2, COL3, COL4, COL5, COL6, COL7, COL8};

byte scan[8][8] = { {1,0,0,0,0,0,0,0},
                    {0,1,0,0,0,0,0,0},
                    {0,0,1,0,0,0,0,0},
                    {0,0,0,1,0,0,0,0},
                    {0,0,0,0,1,0,0,0},
                    {0,0,0,0,0,1,0,0},
                    {0,0,0,0,0,0,1,0},
                    {0,0,0,0,0,0,0,1} };

byte W[8][8] = { {1,1,1,1,1,1,1,1},
                 {0,1,1,1,1,1,1,0},
                 {0,1,1,0,0,1,1,0},
                 {0,1,1,0,0,1,1,0},
                 {0,1,1,0,0,1,1,0},
                 {1,0,0,1,1,0,0,1},
                 {1,1,1,1,1,1,1,1},
                 {1,1,1,1,1,1,1,1}};

byte T[8][8] = { {1,1,1,1,1,1,1,1},
                 {1,0,0,0,0,0,0,1},
                 {1,0,0,0,0,0,0,1},
                 {1,1,1,0,0,1,1,1},
                 {1,1,1,0,0,1,1,1},
                 {1,1,1,0,0,1,1,1},
                 {1,1,1,0,0,1,1,1},
                 {1,1,1,0,0,1,1,1}};


int trackID = 0;

void blink() {
  trackID++;
  if(trackID == 2) {
    trackID = 0;
  }
}

void setup() {

  for (byte i = 0; i <= sizeof(row); i++) {
    pinMode(row[i], OUTPUT);
  }
  for (byte i = 0; i <= sizeof(col); i++) {
    pinMode(col[i], OUTPUT);
  }
  setSongs();
  
  pinMode(BOTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BOTTON), blink, FALLING );
}

long preTime = 0, curTime = 0, pauseBetweenNotes = 0;
int thisNote = -1, noteDuration = 0;

void loop() {
  showPattern(trackID);
}

void showPattern(int id){
  if(id == 0) {
    for(byte i = 0; i < 8; i++){
      for(byte j = 0; j < 8; j++){
        digitalWrite(row[j], 1 - scan[i][j]);
        digitalWrite(col[j], 1 - W[i][j]);
      }
      for(byte j = 0; j < 8; j++){
        digitalWrite(row[j], HIGH);
        digitalWrite(col[j], LOW);
      }
      check(id);
    }
  }
  if(id == 1) {
    for(byte i = 0; i < 8; i++){
      for(byte j = 0; j < 8; j++){
        digitalWrite(row[j], 1 - scan[i][j]);
        digitalWrite(col[j], 1 - T[i][j]);
      }
      for(byte j = 0; j < 8; j++){
        digitalWrite(row[j], HIGH);
        digitalWrite(col[j], LOW);
      }
      check(id);
    }
  }
}

void check(int id){
  curTime = millis();
  if(curTime - preTime >= pauseBetweenNotes) {
    thisNote ++;
    if(thisNote >= songs[id].len) {
      thisNote = -1;
      pauseBetweenNotes = 1000;
    }
    else{
      noteDuration = 1000 / songs[id].noteDurations[thisNote];
      tone(BUZZER, songs[id].melody[thisNote], noteDuration);
      pauseBetweenNotes = noteDuration * 1.30;
    }
    preTime = millis();
  }
}



void setSongs() {
  
songs[0].melody[0] = NOTE_C6;
songs[0].melody[1] = NOTE_A5;
songs[0].melody[2] = NOTE_C6;
songs[0].melody[3] = NOTE_A5;
songs[0].melody[4] = NOTE_C6;
songs[0].melody[5] = NOTE_A5;
songs[0].melody[6] = NOTE_C6;
songs[0].melody[7] = NOTE_G5;
songs[0].melody[8] = NOTE_E5;
songs[0].melody[9] = NOTE_E5;

songs[0].noteDurations[0] = 4;
songs[0].noteDurations[1] = 4;
songs[0].noteDurations[2] = 4;
songs[0].noteDurations[3] = 4;
songs[0].noteDurations[4] = 8;
songs[0].noteDurations[5] = 8;
songs[0].noteDurations[6] = 8;
songs[0].noteDurations[7] = 8;
songs[0].noteDurations[8] = 8;
songs[0].noteDurations[9] = 8;

songs[0].len = 10;

songs[1].melody[0] = NOTE_C6;
songs[1].melody[1] = NOTE_A5;
songs[1].melody[2] = NOTE_C6;
songs[1].melody[3] = NOTE_E6;
songs[1].melody[4] = NOTE_E6;
songs[1].melody[5] = 0;
songs[1].melody[6] = NOTE_G6;
songs[1].melody[7] = NOTE_E6;
songs[1].melody[8] = NOTE_C6;
songs[1].melody[9] = NOTE_A5;
songs[1].melody[10] = NOTE_A5;

songs[1].noteDurations[0] = 4;
songs[1].noteDurations[1] = 4;
songs[1].noteDurations[2] = 8;
songs[1].noteDurations[3] = 8;
songs[1].noteDurations[4] = 4;
songs[1].noteDurations[5] = 16;
songs[1].noteDurations[6] = 8;
songs[1].noteDurations[7] = 8;
songs[1].noteDurations[8] = 4;
songs[1].noteDurations[9] = 8;
songs[1].noteDurations[10] = 8;

songs[1].len = 11;

}
