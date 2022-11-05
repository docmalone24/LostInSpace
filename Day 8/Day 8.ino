//Day 7

int redLED = 11; //pin for red LED
int greenLED = 10; //pin for yellow LED
int blueLED = 9; //pin for white LED
int onboardLED = 13;

// unsigned int batteryCapacity = 50000;
// unsigned int batteryLevel = 0;
// unsigned int ticks = 0;
int wait = 800;
// double PercentFull;

void setup() {
  // put your setup code here, to run once:
  // Serial.begin(9600);
  pinMode(onboardLED, OUTPUT);

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  
  digitalWrite(onboardLED, HIGH);
}

void RGB_color(int red_value, int green_value, int blue_value){
  //custom function to set three PWM color channel to any given mixture

  analogWrite(redLED, red_value);
  analogWrite(greenLED, green_value);
  analogWrite(blueLED, blue_value);
}

void loop() {
  //cycle throgh several differnt color settings

  RGB_color(125, 0, 0); //red
  delay(wait);
  RGB_color(0, 125, 0); //green
  delay(wait);
  RGB_color(0, 0, 125); //blue
  delay(wait);
  RGB_color(64, 32, 0); //yellow
  delay(wait);
  RGB_color(125, 0, 125); //purple
  delay(wait);
  RGB_color(125, 125, 125); //white
  delay(wait * 3);
  
}
