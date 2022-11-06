int Stop = 4;  //Red LED, Stop light
int Caut = 3;  //Amber LED, Caution light
int Go = 2;    //Green LED, Go when clear light
int Walk = 8;  //White LED, Walk light
int Stay = 9;  //Red LED, Do not walk light
int PB = 13;   //Request to cross push button


void setup() {
  // Setup an input and an output on the HERO
  pinMode(Stop, OUTPUT);           //initialize pin 4 as output to Red traffic LED
  pinMode(Caut, OUTPUT);           //initialize pin 3 as output to Yello traffic LED
  pinMode(Go, OUTPUT);             //initialize pin 2 as output to Green traffic LED
  pinMode(Walk, OUTPUT);           //initialize pin 8 as output indicating "Safe to Cross"
  pinMode(Stay, OUTPUT);           //initialize pin 9 as output indicating "Do Not Walk"
  pinMode(PB, INPUT);              //initialize pin 13 as a controlled input from push button
  pinMode(LED_BUILTIN, OUTPUT);    // initialize onboard LED as an output control
  digitalWrite(LED_BUILTIN, LOW);  // turn onboard LED off to reduce glare, power usage
  digitalWrite(Go, HIGH);          //Begin system with Green traffic LED on, indicating traffic is moving through
  digitalWrite(Stay, HIGH);        //Begin system with Red "Do Not Walk" LED on, indicating pedestrian traffic is instructed to wait
}

void loop() {
  //within loop actions will occur based on push button input

  //this is a simulation of a traffic light, currently green, and a push button requesting safe crossing

  while (digitalRead(PB) == LOW);  {
    if (digitalRead(PB) == HIGH); {
    digitalWrite(Go, LOW);
    digitalWrite(Caut, HIGH);
    delay(3000);
    digitalWrite(Caut, LOW);
    digitalWrite(Stop, HIGH);
    delay(1000);
    digitalWrite(Stay, LOW);
    digitalWrite(Walk, HIGH);
    delay(5000);
    digitalWrite(Walk, LOW);
    digitalWrite(Stay, HIGH);
    delay(1000);
    digitalWrite(Stop, LOW);
    digitalWrite(Go, HIGH);
  
  }
  }
}