//Goal: recreate day 15 project using rotary encoder in the place of the keypad
#include <TM1637Display.h>

// Define the display connection pins:
#define CLK 7
#define DIO 6

// Rotary Encoder Inputs
#define CLK2 3
#define DT2 4
// Switch Input
#define SW2 2

//light sensor range is 0 - 671
int sensorPin = A0; //select the *analog zero* input pin for probing the photoresistor 
int senMax = 680; //maximum light value received by the sensor
int buzzer = 8;  //sound output pin
int redPin = 11;   //  PWM color output pins
int greenPin = 10;
int bluePin = 9;

int access = 0;

// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
// Characters to display while in the menu
const uint8_t aChar[] = {SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G};
const uint8_t bChar[] = {SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G};
const uint8_t cChar[] = {SEG_A | SEG_D | SEG_E | SEG_F};
const uint8_t eChar[] = {SEG_A | SEG_D | SEG_E | SEG_F | SEG_G};

//  menu option currently being displayed
char menuOption = 'X';

int pw1 = 0;
int pw2 = 0;
int length = 1;
int password = 2469;
int multiplier = 10;

int currentStateCLK;
int lastStateCLK;
 
//  custom function to process a login attempt *******************************
 /*
int unlockMode(){
    char result ;
    bool correctPass = true;
 
    RGB_color(0, 0, 0); // turn LED OFF
    //Serial.println("Unlock Mode: Type Password to continue");
    delay(500);
   
    for(int i = 0; i < PassLength; i++) {
       while(!(result = securityPad.getKey())) {
         // wait indefinitely for keypad input of any kind
       }
       if(currentPassword[i] != result){     // a wrong key was pressed
          correctPass = false;
       }
       Serial.print("*");  // print a phantom character for a successful keystroke
       playInput();
       RGB_color(0, 0, 125); // flash LED blue
       delay(100);
       RGB_color(0, 0, 0);
    }  //  done after 4 characters are accepted

    if (correctPass){   
      Serial.println("");
      Serial.println("Device Successfully Unlocked!");
      // playSuccess();
      return 0;           //  0 means succeeded
    }
    else {
      Serial.println("");
      Serial.println("WRONG PASSWORD");
      //Serial.println(result);
      // playError();
      return -1;                    //  -1 means failed -- return immediately    
    }

} */
 
//  custom functions to give audio feedback *******************************
 
void playSuccess() {
  RGB_color(0, 125, 0); // LED to GREEN
  tone(buzzer, 1000, 200);
  delay(200);
  tone(buzzer, 2700, 1000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  RGB_color(0, 0, 0);
}
 
void playError() {
  RGB_color(255, 0, 0); // LED to RED
  tone(buzzer, 147, 1000);
  delay(1000);
  noTone(buzzer);
  delay(1000);
  RGB_color(0, 0, 0);
}
 
void playInput() {
  tone(buzzer, 880, 200);
  delay(50);
  noTone(buzzer);
}
 
//  custom function to light the LED *******************************
void RGB_color(int red_value, int green_value, int blue_value)
{
  analogWrite(redPin, red_value);
  analogWrite(greenPin, green_value);
  analogWrite(bluePin, blue_value);
}
 
//  ************************************************************************
 
void setup() {
  pinMode(redPin, OUTPUT);  // designate pins for PWM LED output
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

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

  RGB_color(125, 125, 125);  //set LED to white on startup...
  delay(2000);
  RGB_color(0, 0, 0);  //... and off again
 
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000);
  // Serial.println("Enter password to access the system:");
  // Serial.println("Press * to set a new password.");
  // Serial.println("Press # to access the system with the existing one.");

  Serial.println("Enter password to access the system:");

}

void showMenu(){
  Serial.println("Enter an option:");
  Serial.println("A: Light In Controls Sound Pitch");
  Serial.println("B: Light In Controls Light Out");
  Serial.println("C: Change Password");
  Serial.println("E: Exit");
}
/*
void passwordChange() {
    for(int i = 0; i < PassLength; i++) {
    while(!(result = securityPad.getKey())) {
    // wait indefinitely for keypad input of any kind
    }

    currentPassword[i] = result;
    Serial.print("*");    // print a phantom character for a successful keystroke
    playInput();
    RGB_color(0, 0, 125); // flash LED blue
    delay(100);
    RGB_color(0, 0, 0);
  }   //  done after 4 characters are accepted

  Serial.println("");
  Serial.println("Password Successfully Changed!");
  RGB_color(0, 125, 0); // LED to GREEN
  delay(2000);
  RGB_color(0, 0, 0);

}

void menuOptA(){
  int sensorValue = 0;
  int buzzTone = 100;
  float senPercent = 0.0;
  Serial.println("Press any key to return to menu.");
  while(!(result = securityPad.getKey())) {
    // run photo sound operation until a key is pressed
    sensorValue = analogRead(sensorPin);
    senPercent = (float)sensorValue / (float)senMax;
    buzzTone = int(senPercent * 4000);
    // Serial.print("Sensor: ");
    // Serial.print(sensorValue);
    // Serial.print("  Tone: ");
    // Serial.print(buzzTone);
    // Serial.print("  Should be: ");
    // Serial.println(senPercent);
    tone(buzzer, buzzTone, 100);
    delay(10);
    noTone(buzzer);
    delay(10);
  }
  return;
}

void menuOptB(){
  int sensorValue = 0;
  int lightLevel = 0;
  float senPercent = 0.0;
  int redLevel;
  int greenLevel;
  int blueLevel;
  Serial.println("Press any key to return to menu.");
  while(!(result = securityPad.getKey())) {
    // run photo sound operation until a key is pressed
    sensorValue = analogRead(sensorPin);
    senPercent = (float)sensorValue / (float)senMax;
    lightLevel = int(senPercent * 255);

    //Test variables
    // Serial.print("Sensor: ");
    // Serial.print(sensorValue);
    // Serial.print("  Tone: ");
    // Serial.print(lightLevel);
    // Serial.print("  Should be: ");
    // Serial.println(senPercent);

    //Option 1: increasing red for the first third, green for the middle, blue for the last 
    // if(lightLevel < 33){
    //   redLevel = ((float)lightLevel / 32.0) * 100;
    //   RGB_color(redLevel, 0, 0);
    // }
    // if(lightLevel >= 33 && lightLevel < 66){
    //   greenLevel = (((float)lightLevel - 32.0) / 33.0) * 100;
    //   RGB_color(0, greenLevel, 0);
    // }
    // if(lightLevel >= 66){
    //   blueLevel = (((float)lightLevel - 65.0) / 35.0) * 100;
    //   RGB_color(0, 0, blueLevel);
    // }
    
    //Option 2: all white light
    RGB_color(lightLevel, lightLevel, lightLevel);

  }
  RGB_color(0,0,0);
  return;
} */

void loop() {
 
 if (access <= 0){
  OurDisplay.showNumberDec(pw1,true,length,0);
  delay(10);
 }
  //debuging readout 
    // Serial.print("pw1: ");
    // Serial.print(pw1);
    // Serial.print("  length: ");
    // Serial.print(length);
    // Serial.print("  password: ");
    // Serial.print(password);
    // Serial.print("  multiplier: ");
    // Serial.print(multiplier);
    // Serial.print("  access: ");
    // Serial.println(access);

  if (access > 0){
    //Serial.println("You have entered the menu");
    showMenu();
  }

  while (access > 0) {           // enter menu mode
    //result = securityPad.getKey(); 
    Serial.println("In the menu loop"); 
    delay(2000);
    /*
    while(!(result = securityPad.getKey())) {
         // wait indefinitely for keypad input of any kind
       }
    //Serial.println(result);
    if (result == 'A'){
      //Serial.println("This is option A.");
      menuOptA();
      showMenu();
    }
    if (result == 'B'){
      //Serial.println("This is option B");
      menuOptB();
      showMenu();
    }
    if (result == 'C'){
      Serial.println("Enter the new password:");
      passwordChange();
      showMenu();
    }
    if (result == '9'){
      access = -1;
      Serial.println("Exiting the system");
    } */
  }
}
 
//  This is our ISR which has the job of responding to interrupt events
void updateEncoder(){
  // Read the current state of CLK
  currentStateCLK = digitalRead(CLK2);

  if (access <= 0) {  //actions while validating password
    // If last and current state of CLK are different, then a pulse occurred;
    // React to only 0->1 state change to avoid double counting
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      // If the DT state is different than the CLK state then
      // the encoder is rotating CW so INCREASE counter by 1
      if (digitalRead(DT2) == currentStateCLK) {
        if((pw1 - (pw2 * multiplier)) == 9){
          pw1 = pw2 * multiplier;
        }
        else {
          pw1 ++;
        }
      } else {
        // Encoder is rotating CCW so DECREASE counter by 1
        if(pw1 == (pw2 * multiplier)){
          pw1 = pw1 + 9;
        }
        else {
          pw1 --;
        }
      }
    }
    // Remember last CLK state to use on next interrupt...
    lastStateCLK = currentStateCLK;
  }
  if (access > 0) {   //actions after password has been validated and system access has been granted
    Serial.println("Here you need to code to scroll through the menu options");
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){
      if (digitalRead(DT2) == currentStateCLK) {
        switch (menuOption) {
          case 'A':
            menuOption = 'B';
            OurDisplay.setSegments(bChar,1,3);
            break;
          case 'B':
            menuOption = 'C';
            OurDisplay.setSegments(cChar,1,3);
            break;
          case 'C':
            menuOption = 'E';
            OurDisplay.setSegments(eChar,1,3);
            break;
          default:
            menuOption = 'A';
            OurDisplay.setSegments(aChar,1,3);
            break;
        }
      } 
      else {
        switch (menuOption) {
          case 'B':
            menuOption = 'A';
            OurDisplay.setSegments(aChar,1,3);
            break;
          case 'C':
            menuOption = 'B';
            OurDisplay.setSegments(bChar,1,3);
            break;
          case 'E':
            menuOption = 'C';
            OurDisplay.setSegments(cChar,1,3);
            break;
          default:
            menuOption = 'E';
            OurDisplay.setSegments(eChar,1,3);
            break;
        }
      }
    }
    // Serial.print("Direction: ");
    // Serial.print(currentDir);
    // Serial.print(" | Counter= ");
    // Serial.println(counter);
    // Remember last CLK state to use on next interrupt...
    lastStateCLK = currentStateCLK;
  }
}

//function makes onboard LED flash when button is pushed
void record(){
  Serial.println(digitalRead(SW2));

  if (access <= 0)  {   //actions while validating password
    if (digitalRead(SW2) == HIGH){
      Serial.println("in loop");
      pw2 = pw1;
      //multiplier = multiplier * 10;
      if (length == 4){ //entering of password complete, validate if correct
        //pw1 = pw2;
        //length = 4;
        if (pw1 == password){
          Serial.println("Looks Good");
          access = 1;
          OurDisplay.clear();
        }
        else {
          Serial.println("Fuck off imposter!");
          Serial.println("Enter the correct password to access the system:");
          pw1 = 0;
          pw2 = 0;
          length = 1;
          OurDisplay.clear();
          return;
        }
      }
      if (length < 4) { //while validating password
      length ++;
      pw1 = pw1 * multiplier;
      }
    //debuging readout 
      Serial.print("pw1: ");
      Serial.print(pw1);
      Serial.print("  pw2: ");
      Serial.print(pw2);
      Serial.print("  length: ");
      Serial.print(length);
      Serial.print("  password: ");
      Serial.print(password);
      Serial.print("  multiplier: ");
      Serial.println(multiplier);
    }
  }
  if (access == 1 && digitalRead(SW2) == HIGH){  //while in the main menu
    Serial.println("Add select a menu option");
  }
  if (access == 2 && digitalRead(SW2) == HIGH){  //while you are inside of a menu option
    Serial.println("Add return to the menu state");
  }
}