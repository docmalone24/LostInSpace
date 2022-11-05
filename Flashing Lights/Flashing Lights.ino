// Code written by Inventr.io for the 30 Day Adventure Kit
// Learn more at https://inventr.io/adventure
 
 
int Light1 = 12; // The HERO Board Pin that the LED is wired to
int Light2 = 10; // The HERO Board Pin that the LED is wired to
int flashDelay = 150;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(Light1, OUTPUT);
  pinMode(Light2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

}
 
// the loop function runs over and over again forever
void loop() {
 digitalWrite(Light1, HIGH);
 digitalWrite(Light2, LOW);
 delay(flashDelay);
 digitalWrite(Light2, HIGH);
 digitalWrite(Light1, LOW);
 delay(flashDelay);

}