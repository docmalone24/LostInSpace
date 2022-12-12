#include <Key.h>
#include <Keypad.h>
 
 
const byte ROWS = 4;
const byte COLS = 4;
const byte PassLength = 4;  // passwords will be 4 characters long
char currentPassword[PassLength] = {'0','0','0','0'}; // default before setting
 
char buttons[ROWS][COLS] = {
  {'A', 'B', 'C', 'D'},  // 1st row
  {'3', '6', '9', '#'},  // 2nd row
  {'2', '5', '8', '0'},  // 3rd row
  {'1', '4', '7', '*'}   // 4th row
};
 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};
 
Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
 
//  custom function to process a login attempt *******************************
 
int unlockMode(){
    char result ;
    bool correctPass = true;
   
    Serial.println("Unlock Mode: Type Password to continue");
    delay(500);
   
    for(int i = 0; i < PassLength; i++) {
       while(!(result = myAwesomePad.getKey())) {
         // wait indefinitely for keypad input of any kind
       }
       if(currentPassword[i] != result){     // a wrong key was pressed
        correctPass = false;
       }
       Serial.print("*");  // print a phantom character for a successful keystroke
    }  //  done after 4 characters are accepted

    if (correctPass){
      Serial.println("");
      Serial.println("Device Successfully Unlocked!");
      return 0;           //  0 means succeeded
    }  
    else {
      Serial.println("WRONG PASSWORD");
      //Serial.println(result);
      return -1;                    //  -1 means failed -- return immediately    
    }
}
//  ************************************************************************
 
void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  delay(2000);
  Serial.println("Press * to set a new password.");
  Serial.println("Press # to access the system with the existing one.");
}
 
void loop() {
  char result = myAwesomePad.getKey();
 
 
   if (result == '*'){           // choice to change password
    int access = unlockMode();
   
    if(access < 0) {
      Serial.println("Access Denied. Cannot change password without knowing the previous or default.");
    }
    else {
      Serial.println("Welcome, authorized user. Please Enter a new password: ");
      delay(500);
   
      for(int i = 0; i < PassLength; i++) {
        while(!(result = myAwesomePad.getKey())) {
        // wait indefinitely for keypad input of any kind
        }
   
        currentPassword[i] = result;
        Serial.print("*");    // print a phantom character for a successful keystroke
      }   //  done after 4 characters are accepted
     
      Serial.println("");
      Serial.println("Password Successfully Changed!");
    }
  }
 
  else if (result == '#') {           // choice to access system with current password
    int access = unlockMode();
    if(access < 0) {
      Serial.println("Password error. Access Denied.");
    }
    else {
      Serial.println("Welcome, authorized user. You may now begin using the system.");
    }
  }
 
}
 