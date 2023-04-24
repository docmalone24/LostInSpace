#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGHT 8
#define NINE 9
#include <Arduino.h>
#include <TM1637Display.h>
 
// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
 
// The amount of time (in milliseconds) between tests
#define TEST_DELAY   2000
 
TM1637Display myFabulousDisplay = TM1637Display(CLK, DIO);
 
void setup()
{
}
 
void loop()
{
 myFabulousDisplay.setBrightness(0x0f); // hex 0f is the same as decimal 15
 uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 }; //all segments off
 myFabulousDisplay.setSegments(data);
 
 int code1 = TWO*10+THREE ;
 myFabulousDisplay.showNumberDec(code1, false, 3, 1); // first code 23
 //  false doesn't show leading zeros, 3 means show three digits,
 //  1 means start in position one (where the first position is zero)
 delay(TEST_DELAY);
 myFabulousDisplay.setSegments(data);
 
 
 int code2 = THREE*100+FIVE*10+THREE ;
 myFabulousDisplay.showNumberDec(code2, true, 3, 1); //second code 353
 delay(TEST_DELAY);
 myFabulousDisplay.setSegments(data);
 
 int code3 = 1000+SIX*100+EIGHT*10+EIGHT ;
 myFabulousDisplay.showNumberDec(code3, true, 4, 0); //third code 1688
 delay(TEST_DELAY);
}
