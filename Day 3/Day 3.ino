int LED1 = 10;//pins 10 thru 12 will be light outputs
int LED2 = 11;
int LED3 = 12;

int Switch1 = 2; //pin 2 will be an input from Switch1
int Switch2 = 3; //pin 3 will be an input from Switch2
int Switch3 = 4; //pin 4 will be an input from Switch3

void setup() {
  // Setting up both an input and an output on the HERO
pinMode(LED1, OUTPUT);
pinMode(LED2, OUTPUT);
pinMode(LED3, OUTPUT);
pinMode(Switch1, INPUT);
pinMode(Switch2, INPUT);
pinMode(Switch3, INPUT);
pinMode(LED_BUILTIN, OUTPUT);
digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // actions taken will be based on the value of the input switch

//conditional test
if (digitalRead(Switch1) == HIGH){
  digitalWrite(LED1, HIGH);}
else {
  digitalWrite(LED1, LOW); //turn light off
}
if (digitalRead(Switch2) == HIGH){
  digitalWrite(LED2, HIGH);}
else {
  digitalWrite(LED2, LOW); //turn light off
}
if (digitalRead(Switch3) == HIGH){
  digitalWrite(LED3, HIGH);}
else {
  digitalWrite(LED3, LOW); //turn light off
}

}
