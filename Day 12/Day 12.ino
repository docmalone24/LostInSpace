#include <Key.h>
#include <Keypad.h>

int greenLED = 10; //port for green LED
int redLED = 11;  //port for red LED
int buzzer = 12;  // pin 10 drives the buzzer

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
  // {'1', '2', '3', 'A'},  // 1st row
  // {'4', '5', '6', 'B'},  // 2nd row
  // {'7', '8', '9', 'C'},  // 3rd row
  // {'*', '0', '#', 'D'}   // 4th row
  {'A', 'B', 'C', 'D'},  // 1st row
  {'3', '6', '9', '#'},  // 2nd row
  {'2', '5', '8', '0'},  // 3rd row
  {'1', '4', '7', '*'}   // 4th row
};
 
byte rowPins[ROWS] = {5, 4, 3, 2};
byte colPins[COLS] = {6, 7, 8, 9};
 
Keypad myAwesomePad = Keypad(makeKeymap(buttons), rowPins, colPins, ROWS, COLS);
 
int tones[ROWS][COLS] = {   // a frequency tone for each button
    // {31, 93, 147, 208},
    // {247, 311, 370, 440},
    // {523, 587, 698, 880},
    // {1397, 2637, 3729, 4978}
    {208, 440, 880, 4978},
    {147, 370, 698, 3729},
    {93, 311, 587, 2637},
    {31, 247, 523, 1397}
};

char GetKey(){

  result = myAwesomePad.getKey();
 
  if (result){                    // if a button is pressed
    Serial.print("Key: ");
    Serial.print(result);
    Serial.print("  ");
  }
    
  return result;
}

void Password(){
  MakeTone(result);
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
  MakeTone(result);
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
  MakeTone(result);
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
  MakeTone(result);
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
  Serial.println("You fuckin did it!");
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 147, 200);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 247, 200);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 370, 200);
  delay(100);
  digitalWrite(greenLED, LOW);
  delay(100);
  digitalWrite(greenLED, HIGH);
  tone(buzzer, 587, 200);
  delay(1000);
  digitalWrite(greenLED, LOW);
  noTone(buzzer);
  //delay(100);
}

void MakeTone (char button){
  int toneFreq = 0;

  for (byte j=0; j<ROWS; j++) {
  for (byte i=0; i<COLS; i++) {
      if (result == buttons[j][i]) {   // found it, get the corresponding tone
          toneFreq=tones[j][i];
          }        
    }  // end i loop
  }  // end j loop

  Serial.print("Tone: ");
  Serial.println(toneFreq);
  tone(buzzer, toneFreq, 200);  // ... and play the tone for a half second
  delay(200);
  noTone(buzzer);

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