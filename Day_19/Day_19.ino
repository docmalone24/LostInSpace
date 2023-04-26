#include <TM1637Display.h>
 
// Rotary Encoder Inputs
#define CLK2 2
#define DT2 3
 
// Define the display connection pins:
#define CLK 6
#define DIO 5
 
#define SECRET1 23
#define SECRET2 353
#define SECRET3 1688
 
// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
// You can set the individual segments per digit to spell words or create other symbols:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
int counter = 0;    // keep a running tally of steps...
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
int buzzer = 10;  // pin 10 drives the buzzer
int toneFreq = 0;
 
void setup() {
 
  // Set encoder pins as inputs
  pinMode(CLK2,INPUT);
  pinMode(DT2,INPUT);
 
  // Setup Serial Monitor
  Serial.begin(9600);
 
  // Read the initial state of A (CLK)
  lastStateCLK = digitalRead(CLK2);
 
  // Clear the display:
  OurDisplay.clear();
  delay(1000);
  OurDisplay.setBrightness(7);
 
  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK2) interrupt  (pin 2), or B (DT2) interrupt (pin 3)
 
  attachInterrupt(digitalPinToInterrupt(CLK2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT2), updateEncoder, CHANGE);
}
 
void loop() {
  OurDisplay.showNumberDec(counter);
  delay(50);
 
  if(counter == SECRET1) {
    toneFreq=SECRET1 ;
    tone(buzzer, toneFreq, 1000);  // ... and play the tone for one second
    delay(1000);
    noTone(buzzer);
    delay(2000);
    OurDisplay.clear();
    counter++;
  }
 
 if(counter == SECRET2) {
    toneFreq=SECRET2 ;
    tone(buzzer, toneFreq, 1000);  // ... and play the tone for one second
    delay(1000);
    noTone(buzzer);
    delay(2000);
    OurDisplay.clear();
    counter++;
 }
 
  if(counter == SECRET3) {
    toneFreq=SECRET3 ;
    tone(buzzer, toneFreq, 1000);  // ... and play the tone for one second
    delay(1000);
    noTone(buzzer);
    delay(2000);
    OurDisplay.clear();
    OurDisplay.setSegments(done);
    delay(10000);
    OurDisplay.clear();
    counter++;
 }
 
}
 
//  This is our ISR which has the job of responding to interrupt events
//
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);
 
  // If last and current state of CLK are different, then a pulse occurred;
  // React to only 0->1 state change to avoid double counting
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
 
    // If the DT state is different than the CLK state then
    // the encoder is rotating CW so INCREASE counter by 1
    if (digitalRead(DT2) == currentStateCLK) {
      counter ++;
      currentDir ="CW";
     
    } else {
      // Encoder is rotating CCW so DECREASE counter by 1
      counter --;
      currentDir ="CCW";
    }
 
    Serial.print("Direction: ");
    Serial.print(currentDir);
    Serial.print(" | Counter= ");
    Serial.println(counter);
  }
 
  // Remember last CLK state to use on next interrupt...
  lastStateCLK = currentStateCLK;
}