//LIBRARIES
#include <TM1637Display.h>
#include <U8glib.h>
 
// MACRO DEFINES
#define numberOfMinutes(_time_) ((_time_ / 1000) / 60)
#define numberOfSeconds(_time_) ((_time_ / 1000) % 60)  
#define PropulsionSW 8 //dip switch #1
#define AvionicsSW 7   //dip switch #2
#define ProceedSW 6    //dip switch #3
#define AudibleConfirm 9  //buzzer
 
// 7 SEGMENT PIN ASSIGNMENTS
#define CLKsev 5
#define DIOsev 4
 
// DEFINE DISPLAY OBJECTS
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
TM1637Display My_display(CLKsev, DIOsev);
 
// HANDY CONSTANTS
const uint8_t OFF[] = {0, 0, 0, 0};
 
// GLOBAL VARIABLES
unsigned long timeLimit = 20000;
int pause = 0;
int pause2 = 0;
 
 
// *********************************************
void setup(){
  Serial.begin(9600);
  // Set brightness
  My_display.setBrightness(7);
  // Clear the display
  My_display.setSegments(OFF);
 
  pinMode(PropulsionSW, INPUT);
  pinMode(AvionicsSW, INPUT);
  pinMode(ProceedSW, INPUT);
 
  My_u8g_Panel.setColorIndex(1); // pixel on
  My_u8g_Panel.drawStr( 0, 1, ".");
  My_u8g_Panel.firstPage();
  do {
    My_u8g_Panel.begin();
    // My_u8g_Panel.setFont(u8g_font_unifont);
    // My_u8g_Panel.drawStr( 0, 12, "-----------");
    // My_u8g_Panel.drawStr( 0, 34, "-----------");
    // My_u8g_Panel.drawStr( 0, 54, "-----------");
  } while (My_u8g_Panel.nextPage());
}
 
// *********************************************
void loop() {
 if(digitalRead(PropulsionSW) == 1 &&
     digitalRead(AvionicsSW) == 1 &&
     digitalRead(ProceedSW) == 1) {
      pause = 1;
  }
  if(pause == 1 && pause2 == 0) {
      playBeepBoop();   // after a set of warning tones and brief pause
      pause2 = 1;       // the countdown will commence
  }
  else if(pause2 == 1) {
    countdown();      // HANG ON!!!
  }
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
        } while( My_u8g_Panel.nextPage() );
        while(1);
    }
}
 
void playBeepBoop() {
  tone(AudibleConfirm, 476, 1500);
  delay(1500);
  tone(AudibleConfirm, 600, 1500);
  delay(1500);
  tone(AudibleConfirm, 800, 1500);
  delay(1500);
  noTone(AudibleConfirm);
}
 
// OLED Display output
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  My_u8g_Panel.setFont(u8g_font_unifont);
 
 
  My_u8g_Panel.drawStr( 0, 12, "LIFTOFF!!");
  My_u8g_Panel.drawStr( 0, 34, "(this is not ");
  My_u8g_Panel.drawStr( 0, 54, " a test)");
}