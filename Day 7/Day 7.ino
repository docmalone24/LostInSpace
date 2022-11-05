//Day 7

int sensorPin = A0; //select the *analog zero* input pin for probing the photoresistor
int onboardLED = 13;  //select the pin for the HERO's built-in LED
int sensorValue = 0;  //variable that we'll use to store the value reading from the sensor

int lowLED = 8; //pin for red LED
int medLED = 9; //pin for yellow LED
int highLED = 10; //pin for white LED
int fullLED = 11; //pin for green LED

unsigned int batteryCapacity = 50000;
unsigned int batteryLevel = 0;
unsigned int ticks = 0;
unsigned int wait = 100;
double PercentFull;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(onboardLED, OUTPUT);

  pinMode(lowLED, OUTPUT);
  pinMode(medLED, OUTPUT);
  pinMode(highLED, OUTPUT);
  pinMode(fullLED, OUTPUT);

  digitalWrite(onboardLED, HIGH);
}

void PrintBatteryPercentage(){
  //print the elapsed time
  Serial.print(ticks);
  Serial.print("ms:  Light Value:");

  Serial.print(sensorValue);
  Serial.print("  Charge at ");

  //convert the integers to decimal numbers, divide them and print
  PercentFull = 100 * ((double)batteryLevel / (double)batteryCapacity);
  Serial.print(PercentFull);

  //print a percent sign and line return
  Serial.println("%");
}

void ChargeIndicator(){
  if (PercentFull > 0){
    digitalWrite(lowLED, HIGH);
  }
  if (PercentFull > 33){
    digitalWrite(medLED, HIGH);
  }
  if (PercentFull > 66){
    digitalWrite(highLED, HIGH);
  }
  if (PercentFull > 99){
    digitalWrite(fullLED, HIGH);
  }
}

void loop() {
  sensorValue = analogRead(sensorPin); //read the value from the sensor
  batteryLevel += sensorValue;
  ticks += wait;

  if(batteryLevel >= batteryCapacity){
    Serial.print(ticks);
    Serial.print("ms:  ");
    Serial.println("FULLY CHARGED");
    digitalWrite(fullLED, HIGH);
    digitalWrite(onboardLED, LOW);
    batteryLevel = batteryCapacity; //to prevent integer from continuing to increase
    ticks = 0;
    delay(20000); //long pause
  }
  else {
    PrintBatteryPercentage();
  }

  ChargeIndicator();

  delay(wait);
}
