//identify how to show digits in specfiic spots on 7 segment display
#include <TM1637Display.h>

// Define the display connection pins:
#define CLK 6
#define DIO 5

// Create display object of type TM1637Display:
TM1637Display OurDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t data[] = {0xff, 0xff, 0xff, 0xff};
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00};
 
int pw1 = 0;
int pw2 = 2;
int pw3 = 3;
int pw4 = 4;

void setup() {
  // Setup Serial Monitor
  Serial.begin(9600);

  // Clear the display:
  OurDisplay.clear();
  delay(1000);
  OurDisplay.setBrightness(7);
}

void loop() {
  OurDisplay.showNumberDec(pw1,true,1,0);
  delay(1000);
  OurDisplay.clear();
  OurDisplay.showNumberDec(((pw1*10)+pw2),true,2,0);
  delay(1000);
  OurDisplay.clear();
  OurDisplay.showNumberDec(((pw1*100)+(pw2*10)+pw3),true,3,0);
  delay(1000);
  OurDisplay.clear();
  OurDisplay.showNumberDec(((pw1*1000)+(pw2*100)+(pw3*10)+pw4),true,4,0);
  delay(1000);
  OurDisplay.clear();
}
