//use rotary encoder to build four digit number
#include <TM1637Display.h>

// Define the display connection pins:
//#define CLK 11
//#define DIO 10
#define CLK 7
#define DIO 6

// Rotary Encoder Inputs
#define CLK2 3
#define DT2 4
// Switch Input
#define SW2 2

// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
int pw1 = 0;
// int pw2 = 2;
// int pw3 = 3;
// int pw4 = 4;  
int length = 1;
int password = 1111;
int multiplier = 10;

int currentStateCLK;
int lastStateCLK;

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);

  // Set encoder pins as inputs
  pinMode(CLK2,INPUT);
  pinMode(DT2,INPUT);
  pinMode(SW2,INPUT_PULLUP);

  pinMode(13, OUTPUT);
 
  // Clear the display:
  OurDisplay.clear();
  delay(1000);
  OurDisplay.setBrightness(7);

  // Read the initial state of A (CLK)
  lastStateCLK = digitalRead(CLK2);

  // Call Interrupt Service Routine (ISR) updateEncoder() when any high/low change
  // is seen on A (CLK2) interrupt  (pin 2), or B (DT2) interrupt (pin 3)
  //hardware interrupts are only available on pins 2 and 3
  attachInterrupt(digitalPinToInterrupt(CLK2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW2), record, CHANGE);

  //debuging readout 
  Serial.print("pw1: ");
  Serial.print(pw1);
  Serial.print("  length: ");
  Serial.print(length);
  Serial.print("  password: ");
  Serial.print(password);
  Serial.print("  multiplier: ");
  Serial.println(multiplier);

}

void loop() {
  OurDisplay.showNumberDec(pw1,true,length,0);
  delay(10);
  //Serial.println(digitalRead(SW2));
  // OurDisplay.clear();
}

//  This is our ISR which has the job of responding to interrupt events
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);
 
  // If last and current state of CLK are different, then a pulse occurred;
  // React to only 0->1 state change to avoid double counting
  if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
 
    // If the DT state is different than the CLK state then
    // the encoder is rotating CW so INCREASE counter by 1
    if (digitalRead(DT2) == currentStateCLK) {
      if((pw1 - (password * multiplier)) == 9){
        pw1 = password * multiplier;
      }
      else {
        pw1 ++;
      }
     
    } else {
      // Encoder is rotating CCW so DECREASE counter by 1
      if(pw1 == (password * multiplier)){
        pw1 = pw1 + 9;
      }
      else {
        pw1 --;
      }
    }
 
    // Serial.print("Direction: ");
    // Serial.print(currentDir);
    // Serial.print(" | Counter= ");
    // Serial.println(counter);
  }
 
  // Remember last CLK state to use on next interrupt...
  lastStateCLK = currentStateCLK;
}

//function makes onboard LED flash when button is pushed
void record(){
    Serial.println(digitalRead(SW2));
  if (digitalRead(SW2) == LOW){
    Serial.println("in loop");
    password = pw1;
    //multiplier = multiplier * 10;
    if (length < 4) {
    length ++;
    pw1 = pw1 * multiplier;
    }
  //debuging readout 
    Serial.print("pw1: ");
    Serial.print(pw1);
    Serial.print("  length: ");
    Serial.print(length);
    Serial.print("  password: ");
    Serial.print(password);
    Serial.print("  multiplier: ");
    Serial.println(multiplier);
  }
  if (length == 5){
    pw1 = password;
    length == 4;
  }
}