#include <Key.h>
#include <Keypad.h>

int greenLED = 10; //port for green LED
int redLED = 11;  //port for red LED

char p1 = '2';  //first character of the password
char p2 = '4';  //second character of the password
char p3 = '6';  //third character of the password
char p4 = '9';  //fourth character of the password
 
const byte ROWS = 4;
const byte COLS = 4;
 
char result = 'a';  //make result a global variable so it can be used in the function
char result2 = 'b'; //place holder for result while loop clears out original
bool passLoop = true; //used to control while loops
char buttons[ROWS][COLS] = {
  {'1', '2', '3', 'A'},  // 1st row
  {'4', '5', '6', 'B'},  // 2nd row
  {'7', '8', '9', 'C'},  // 3rd row
  {'*', '0', '#', 'D'}   // 4th row
};
 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};
 
Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
char GetKey(){

  result = myAwesomePad.getKey();
 
  if (result){                    // if a button is pressed
    Serial.println(result);
  }
  
  return result;
}

void Password(){
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);

  do {
    result2 = GetKey();

    if (result2 == p2){
      Password2();
    }
    else if (result2){
      BadPass();
      passLoop = false;
    }
  } while (passLoop);
}

void Password2(){
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);

  do {
    result2 = GetKey();

    if (result2 == p3){
      Password3();
    }
    else if (result2) {
      BadPass();
      passLoop = false;
    }
  } while (passLoop);
}

void Password3(){
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);

  do {
    result2 = GetKey();

    if (result2 == p4){
      GoodPass();
      passLoop = false;
    }
    else if (result2) {
      BadPass();
      passLoop = false;
    }
  } while (passLoop);
}

void BadPass(){ //when a key is presed as not part of the password, the red LED will blink 3 times
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(redLED, LOW);
  delay(100);
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(redLED, LOW);
  delay(100);
  digitalWrite(redLED, HIGH);
  delay(100);
  digitalWrite(redLED, LOW);
  delay(100);
}
 
void GoodPass(){ //when the password has been entered correctly, the green LED will blink 3 times
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  delay(1000);
  digitalWrite(greenLED, LOW);
  //delay(100);
}

void setup() {
  Serial.begin(9600); // Begin monitoring via the serial monitor
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}
 
void loop() {

  result2 = GetKey();

  if (result2 == p1){
    passLoop = true;
    Password();
    //digitalWrite(greenLED, HIGH);
  }
  else if(result){
    BadPass();
    //Serial.println(result);
    //digitalWrite(greenLED, LOW);
  }
}

// void loop() {
//   char result = myAwesomePad.getKey();
 
//   if (result){                    // if a button is pressed
//     Serial.println(result);
//   }
 
// }