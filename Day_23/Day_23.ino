//LIBRARIES
#include <TM1637Display.h>
#include <U8glib.h>
 
// MACRO DEFINES
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)  
 
// 7 SEGMENT PIN ASSIGNMENTS
#define CLKsev 5
#define DIOsev 4
 
// DEFINE DISPLAY OBJECTS
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
TM1637Display My_display(5, 4);
 
// HANDY CONSTANTS
const uint8_t OFF[] = {0, 0, 0, 0};
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};
 
// GLOBAL VARIABLES
unsigned long timeLimit = 10000;
unsigned long lastPeriodStart;
 
// *********************************************
void setup(){
  Serial.begin(9600);
  // Set brightness
  My_display.setBrightness(7);
  // Clear the display
  My_display.setSegments(OFF);
 
  My_u8g_Panel.setColorIndex(1);
}
 
// *********************************************
void loop() {
  countdown();
}
// *********************************************
 
void countdown() {
  // Calculate the time remaining
 
  unsigned long timeRemaining = timeLimit - millis();
   Serial.println("Countdown started..: ");
     
    Serial.println(timeRemaining);
    // To display the countdown in mm:ss format, separate the parts
    int seconds = numberOfSeconds(timeRemaining);
    int minutes = numberOfMinutes(timeRemaining);
 
    // This displays the seconds in the last two places
    My_display.showNumberDecEx(seconds, 0, true, 2, 2);
    // Display the minutes in the first two places, with colon
    //My_display.showNumberDecEx(minutes, 0x80>>3, true, 2, 0);
    My_display.showNumberDecEx(minutes, 0x40, true, 2, 0);
 
    // Update the time remaining
    timeRemaining = timeLimit - millis();
    if(timeRemaining < 50){
      Serial.println("BREAK!!");
        My_u8g_Panel.firstPage();  
        do {
          draw();
          Serial.println("First page loop");
        } while( My_u8g_Panel.nextPage() );
        Serial.println("Next page returned false");
        while(1);
    }
}
 
 
// OLED Display output
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  My_u8g_Panel.setFont(u8g_font_unifont);
 
 
  My_u8g_Panel.drawStr( 0, 22, "LIFTOFF!!");
  My_u8g_Panel.drawStr( 0, 44, "End of sim");
}