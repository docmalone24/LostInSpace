// Include the 7-segment display library:
#include <TM1637Display.h>
 
// Define the display connections pins:
#define CLK 6
#define DIO 5
 
// Create display object of type TM1637Display:
TM1637Display myFabulousDisplay = TM1637Display(CLK, DIO);
 
// Create array that turns all segments on:
const uint8_t all_on[] = {0xff, 0xff, 0xff, 0xff}; // 0xff is a hexidecimal number whose binary
                                                  // representation is all ones
 
// Create array that turns all segments off:
const uint8_t blank[] = {0x00, 0x00, 0x00, 0x00}; // 0xff is a hexidecimal number whose binary
                                                  // representation is all zeros
 
// You can set the individual segments to spell digits, words or create other symbols
// by performing bitwise OR operations of the segments you need to turn on:
const uint8_t done[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
void setup() {
  // Clear the display:
  myFabulousDisplay.clear();
  delay(1000);
}
 
void loop() {
  // Set the brightness:
  myFabulousDisplay.setBrightness(7);
  // All segments on:
  myFabulousDisplay.setSegments(all_on);
  delay(2000);
  myFabulousDisplay.clear();
  delay(1000);
 
  // demonstrate counter:
  int i;
  for (i = 0; i <= 123; i++) {
    myFabulousDisplay.showNumberDec(i);  // this knows how to make decimal numbers
    delay(100);
  }
  delay(2000);
  myFabulousDisplay.clear();
  delay(1000);
  myFabulousDisplay.setSegments(done);
  while(1);  // after one pass, hang here forever...
}