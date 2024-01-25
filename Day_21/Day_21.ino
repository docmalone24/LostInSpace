#include <U8glib.h>
 
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
 
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  My_u8g_Panel.setFont(u8g_font_unifont);
  My_u8g_Panel.drawStr( 0, 1, ".");
  My_u8g_Panel.drawStr( 123, 1, ".");
  My_u8g_Panel.drawStr( 0, 65, ".");
  My_u8g_Panel.drawStr( 123, 65, ".");
 
}
 
void setup(void) {
  // Setup Serial Monitor
  Serial.begin(9600);
  // flip screen, if required
  // My_u8g_Panel.setRot180();
 
  // assign default color value
  My_u8g_Panel.setColorIndex(1); // pixel on
 
 // pinMode(8, OUTPUT);
}
 
void loop(void) {
  // picture loop
  My_u8g_Panel.firstPage();
  do {
    draw();
    delay(500);
    Serial.print("Inside: ");
    // Serial.println(My_u8g_Panel.nextPage());
  } while( My_u8g_Panel.nextPage() );

  delay(500);
  Serial.print("Outside: ");
  Serial.println(My_u8g_Panel.nextPage());
 
 
}