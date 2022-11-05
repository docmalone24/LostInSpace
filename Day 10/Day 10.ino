// Day 10 code...
//Added a battery drain function which corresponds to switches 2 & 3 and adjusts the amount of battery draw accordingly
//Added a charging switch and LED indicator to disable the charging with Switch 1 and LED will light accordingly
 
int sensorPin = A0;   // select the *analog zero* input pin for probing the photoresistor
int sensorValue = 0;  // variable that we'll use to store the value reading from the sensor
 
int red = 11;  // these are our output pins for three LED colors
int green = 10;
int blue = 9;

int chargeLED = 8;  //port for LED used to indicate charging is on
int redDrainLED = 6;  //port used to indicate level one battery drain
int yellowDrainLED = 7; //port used to indicate level two battery drain

int chargeSwitch = 2; //port for switch 1 to be used to turn charging on or off
int drainOneSwitch = 3; //port to turn on level one drain
int drainTwoSwitch = 4; //port to turn on level two drain
 
unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;
 
//******************************************
 
void setup() {
  // Declare the RGB LED pins as outputs:
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(chargeLED, OUTPUT);
  pinMode(chargeSwitch, INPUT);
  pinMode(redDrainLED, OUTPUT);
  pinMode(yellowDrainLED, OUTPUT);
  pinMode(drainOneSwitch, INPUT);
  pinMode(drainTwoSwitch, INPUT);

  // Start serial monitor
  Serial.begin(9600);
  digitalWrite(chargeLED, LOW);
}
 
//******************************************
 
void RGB_color(int red_value, int green_value, int blue_value)
 {
// custom function to set three PWM color channels to any given mixture
// it returns NO numerical result (void)
 
  analogWrite(red, red_value);
  analogWrite(green, green_value);
  analogWrite(blue, blue_value);
}
 
//******************************************
 
 double getBatteryPercentage() {
// custom function calculates battery charge percentage
// and returns the result as a double precision number
 
  return (((double)batteryLevel / (double)batteryCapacity)*100);
 
}
 
//******************************************
 
void ShowBatteryPercentage() {
  //  send battery results to both serial and LED outputs
   //  calculate the charge percentage with a custom function...
  PercentFull=getBatteryPercentage();
 
    if(batteryLevel >= batteryCapacity) {
      Serial.print(ticks);
      Serial.print("ms - Sensor Value:");
      Serial.print(sensorValue);
      Serial.print(" - Drain:");
      Serial.print(BatteryDrain());
      Serial.println(" - FULLY CHARGED");
      batteryLevel = batteryCapacity; // to prevent integer from continuing to increase
      ticks = 0;
      RGB_color(0, 125, 0); // Green for charging complete
      delay(5000);      // long pause
    }
    else{
    // print the elasped time
      Serial.print(ticks);
      Serial.print("ms - Sensor Value: ");
      Serial.print(sensorValue);
      Serial.print(" - Drain:");
      Serial.print(BatteryDrain());
      Serial.print(" - Charge:");
    // print the percent charge
      Serial.print(PercentFull);
    // print a percent character and line return...
      Serial.println("%");
    
    // Now let's light the LED with the appropriate color...
    
      if (PercentFull == 0) {
        RGB_color(0, 0, 0);
      }
      else if (PercentFull > 0 && PercentFull <= 25)
      {
        RGB_color(125, 0, 0); // red
      }
      else if (PercentFull > 25 && PercentFull <= 50){
        RGB_color(255, 80, 0); // yellow-ish
      }
      else if (PercentFull > 50 && PercentFull <= 75) {
        RGB_color(0, 125, 125); // blue-ish
      }
      else if (PercentFull > 75 && PercentFull < 100) {
        RGB_color(125, 125, 125); // white
      }
    } 
}
 
//******************************************

int BatteryDrain(){
  if (digitalRead(drainOneSwitch) == LOW && digitalRead(drainTwoSwitch) == LOW){
    digitalWrite(redDrainLED, LOW);
    digitalWrite(yellowDrainLED, LOW);
    return (0);
  }
  if (digitalRead(drainOneSwitch) == HIGH && digitalRead(drainTwoSwitch) == LOW){
    digitalWrite(redDrainLED, HIGH);
    digitalWrite(yellowDrainLED, LOW);
    return (10);
  }
  if (digitalRead(drainOneSwitch) == LOW && digitalRead(drainTwoSwitch) == HIGH){
    digitalWrite(redDrainLED, LOW);
    digitalWrite(yellowDrainLED, HIGH);
    return (100);
  }
  if (digitalRead(drainOneSwitch) == HIGH && digitalRead(drainTwoSwitch) == HIGH){
    digitalWrite(redDrainLED, HIGH);
    digitalWrite(yellowDrainLED, HIGH);
    return (500);
  }
}
 
void loop() {

  sensorValue = analogRead(sensorPin); // read the value from the sensor

  if (digitalRead(chargeSwitch) == HIGH){
    digitalWrite(chargeLED, HIGH);  //turn on charging LED
    batteryLevel += sensorValue;
    //add function call to check battery drain
    ticks += wait;
  }
  else {
    digitalWrite(chargeLED, LOW); //turns off charging LED
  }
  
  if (batteryLevel > BatteryDrain()){
    batteryLevel -= BatteryDrain();
  }
  else {
    batteryLevel = 0;
  }

  ShowBatteryPercentage();
  delay(wait);
}
 