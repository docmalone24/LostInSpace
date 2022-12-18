#include <Key.h>
#include <Keypad.h>
 
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
 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 12, 13};  // reassigned two of the column pins
 
Keypad securityPad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
 
//  custom function to process a login attempt *******************************
 
int unlockMode(){
    char result ;
    bool correctPass = true;
 
    RGB_color(0, 0, 0); // turn LED OFF
    Serial.println("Unlock Mode: Type Password to continue");
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
  Serial.println("Press * to set a new password.");
  Serial.println("Press # to access the system with the existing one.");
}
 
void loop() {
  char result = securityPad.getKey();
 
 
   if (result == '*'){           // choice to change password
    int access = unlockMode();
   
    if(access < 0) {
      Serial.println("Access Denied. Cannot change password without knowing the previous or default.");
      //RGB_color(125, 0, 0); // LED to RED
      playError();
    }
    else {
      //RGB_color(0, 125, 0); // LED to GREEN
      playSuccess();
      delay(2000);
      RGB_color(0, 0, 0);  //... and off again
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);
   
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
    }
  }
 
  else if (result == '#') {           // choice to access system with current password
    int access = unlockMode();

    if(access < 0) {
      Serial.println("Password error. Access Denied.");
      //RGB_color(125, 0, 0); // LED to RED
      //delay(1000);
      playError();
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
      //RGB_color(0, 125, 0); // LED to GREEN
      //delay(1000);
      playSuccess();
   }
  }
 
}
 