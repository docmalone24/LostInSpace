int curState = 0; //this will be used to store the current number
bool stateHigh = true;

int LED1 = 6;//pins 10 thru 12 will be light outputs
int LED2 = 7;
int LED3 = 8;
int LED4 = 9;
int LED5 = 10;
int LED6 = 11;
int LED7 = 12;

int Switch1 = 2; //pin 2 will be an input from Switch1
int Switch2 = 3; //pin 3 will be an input from Switch2
int Switch3 = 4; //pin 4 will be an input from Switch3

void setup() {
  // Setting up both an input and an output on the HERO
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(LED4, OUTPUT);
pinMode(LED5, OUTPUT);
pinMode(LED6, OUTPUT);
pinMode(LED7, OUTPUT);
pinMode(Switch1, INPUT);
pinMode(Switch2, INPUT);
pinMode(Switch3, INPUT);
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, stateHigh);
//stateHigh = !stateHigh;
}

void switch_num(int S1, int S2, int S3)
{
  //swap_builtIn();
if (S1 == LOW && S2 == LOW && S3 == LOW){ //switches set to 0
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  //delay(1000);
  swap_builtIn(0);
}
if (S1 == HIGH && S2 == LOW && S3 == LOW){ //switches set to 1
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  swap_builtIn(1);
}
if (S1 == LOW && S2 == HIGH && S3 == LOW){ //switches set to 2
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  swap_builtIn(2);
}
if (S1 == HIGH && S2 == HIGH && S3 == LOW){ //switches set to 3
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  swap_builtIn(3);
}
if (S1 == LOW && S2 == LOW && S3 == HIGH){ //switches set to 4
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  swap_builtIn(4);
}
if (S1 == HIGH && S2 == LOW && S3 == HIGH){ //switches set to 5
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  swap_builtIn(5);
}
if (S1 == LOW && S2 == HIGH && S3 == HIGH){ //switches set to 6
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, LOW);
  swap_builtIn(6);
}
if (S1 == HIGH && S2 == HIGH && S3 == HIGH){ //switches set to 7
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, HIGH);
  swap_builtIn(7);
}

}

void swap_builtIn(int newState)
{
  if (curState != newState) {
    // if (!LED_BUILTIN){
      digitalWrite(LED_BUILTIN, !stateHigh);
      //delay(1000);
      stateHigh = !stateHigh;
    }
    // else if(LED_BUILTIN){
    //   digitalWrite(LED_BUILTIN, LOW);
    // }
    curState = newState;
  //}
}
void loop() {
//read switches and call function to like corresponding LED
switch_num(digitalRead(Switch1),digitalRead(Switch2),digitalRead(Switch3));
// delay(1000);
// if (LED_BUILTIN){
//   digitalWrite(LED_BUILTIN, LOW);
// }
//digitalWrite(LED7,HIGH);
}
