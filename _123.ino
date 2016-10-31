/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

int MIC_PIN = A0;
int led = 13;

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

const int buzzer = 8;
const int toneTable[7][5]={  
  { 66, 131, 262, 523, 1046},  // C Do
  { 74, 147, 294, 587, 1175},  // D Re
  { 83, 165, 330, 659, 1318},  // E Mi
  { 88, 175, 349, 698, 1397},  // F Fa
  { 98, 196, 392, 784, 1568},  // G So
  {110, 220, 440, 880, 1760},  // A La
  {124, 247, 494, 988, 1976}   // B Si
};
char toneName[]="CDEFGAB";
char beeTone[]="GEEFDDCDEFGGGGEEFDDCEGGEDDDDDEFEEEEEFGGEEFDDCEGGC";
char starTone[]="CCGGAAGFFEEDDCGGFFEEDGGFFEEDCCGGAAGFFEEDDC";
 
int beeBeat[]={
  1,1,2, 1,1,2, 1,1,1,1,1,1,2,
  1,1,2, 1,1,2, 1,1,1,1,4,
  1,1,1,1,1,1,2, 1,1,1,1,1,1,2,
  1,1,2, 1,1,2, 1,1,1,1,4
};
int starBeat[]={
  1,1,1,1,1,1,2, 1,1,1,1,1,1,2,
  1,1,1,1,1,1,2, 1,1,1,1,1,1,2,
  1,1,1,1,1,1,2, 1,1,1,1,1,1,2
};
int getTone(char symbol) {
  int toneNo = 0;
  for ( int ii=0; ii<7; ii++ ) {
      if ( toneName[ii]==symbol ) {
          toneNo = ii;
          break;
      }
  }
  return toneNo;
}

float timer=0;

void setup() {
  Serial.begin(115200);
  pinMode(MIC_PIN, INPUT); 
  pinMode(led, OUTPUT);   
  pinMode(buzzer,OUTPUT);
  noTone(buzzer); 
  attachInterrupt(digitalPinToInterrupt(MIC_PIN), blink, CHANGE);
}

int count = 0; // 計算收到幾次的高音量

void loop() {
 // put your main code here, to run repeatedly:
  int mic = analogRead(MIC_PIN); // 讀取麥克風輸出
  Serial.println(mic);
  /*if(mic >= 400){ // 這裡寫死400，可試試別的值
    count++;
    Serial.print("mic >= 400, count=");
    Serial.println(count);
   digitalWrite(led, HIGH); 
  }
  else{
    digitalWrite(led, LOW);
  }*/
  
int ii, length, toneNo;
  int duration;
   
    // bee
  length = sizeof(beeTone)-1;
  for ( ii=0; ii<length; ii++ ) {
      toneNo = getTone(beeTone[ii]);
      duration = beeBeat[ii]*333;
        tone(buzzer,toneTable[toneNo][3]);
       
      delay(duration);
      blink();
      noTone(buzzer);
  }
 // delay(2000);
// star
//  length = sizeof(starTone)-1;
//  for ( ii=0; ii<length; ii++ ) {
//      toneNo = getTone(starTone[ii]);
//      duration = starBeat[ii]*333;
//      tone(buzzer,toneTable[toneNo][3]);
//      delay(duration);
//      noTone(buzzer);
//  }
//  noTone(buzzer);
//  delay(2000);
  
}

void blink(){
  int aaa=analogRead(MIC_PIN);
  if(aaa<260){
    digitalWrite(led,LOW);
  }else{
    digitalWrite(led,HIGH);
  }
}

