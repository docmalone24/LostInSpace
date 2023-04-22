#include <Key.h>
#include <Keypad.h>

//light sensor range is 0 - 671
int sensorPin = A0; //select the *analog zero* input pin for probing the photoresistor 
int senMax = 680; //maximum light value received by the sensor
int buzzer = 8;  //sound output pin
int redPin = 11;   //  PWM color output pins
int greenPin = 10;
int bluePin = 9;
 
const byte ROWS = 4;
const byte COLS = 4;
const byte PassLength = 4;  // passwords will be 4 characters long
char currentPassword[PassLength] = {'0','0','0','0'}; // default before setting
 
char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // 1st row
  {'4', '5', '6', 'B'},  // 2nd row
  {'7', '8', '9', 'C'},  // 3rd row
  {'*', '0', '#', 'D'}   // 4th row
};
 
char result;
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 12, 13};  // reassigned two of the column pins
 
Keypad securityPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
 
//  custom function to process a login attempt *******************************
 
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

}
 
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
 
  RGB_color(125, 125, 125);  //set LED to white on startup...
  delay(2000);
  RGB_color(0, 0, 0);  //... and off again
 
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000);
  // Serial.println("Enter password to access the system:");
  // Serial.println("Press * to set a new password.");
  // Serial.println("Press # to access the system with the existing one.");
}

void showMenu(){
  Serial.println("Enter an option:");
  Serial.println("A: Light Controls Sound");
  Serial.println("B: Something Else");
  Serial.println("C: Change Password");
  Serial.println("9: Exit");
}
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
    Serial.print("Sensor: ");
    Serial.print(sensorValue);
    Serial.print("  Tone: ");
    Serial.print(buzzTone);
    Serial.print("  Should be: ");
    Serial.println(senPercent);
    tone(buzzer, buzzTone, 100);
    delay(10);
    noTone(buzzer);
    delay(10);
  }
  return;
}

void loop() {
  Serial.println("Enter password to access the system:");
  int access = unlockMode();
 
  if (access >= 0){
    //Serial.println("You have entered the menu");
    showMenu();
  }

  while (access >= 0) {           // enter menu mode
    //result = securityPad.getKey();
    //Serial.println("In the menu loop");
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
      Serial.println("This is option B");
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
    }
  }
}
 