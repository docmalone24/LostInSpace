//Day 6

int sensorPin = A0; //select the *analog zero* input pin for probing the photoresistor
int onboardLED = 13;  //select the pin for the HERO's built-in LED
int sensorValue = 0;  //variable that we'll use to store the value reading from the sensor
int senMin = 600;   //this will store the sensor minimum value
int senMax = 0;   //this will store the sensor maximum value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(onboardLED, OUTPUT);
}

void loop() {
  // Pluse the builtin LED for a time determined by the sensor
  sensorValue = analogRead(sensorPin);
  digitalWrite(onboardLED, HIGH);
  delay(sensorValue);
  digitalWrite(onboardLED, LOW);
  delay(sensorValue);

  if (sensorValue < senMin) {
    senMin = sensorValue;
  }
  if (sensorValue > senMax) {
    senMax = sensorValue;
  }

  //Read the analog sensor value and send it to the serial monitor
  Serial.print("Value: ");
  Serial.print(sensorValue);
  Serial.print("  Min: ");
  Serial.print(senMin);
  Serial.print("  Max: ");
  Serial.println(senMax);
  delay(sensorValue);
}
