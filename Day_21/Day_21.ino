#include <U8glib.h>
 
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
 
void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  My_u8g_Panel.setFont(u8g_font_unifont);
  My_u8g_Panel.drawStr( 0, 10, "Build");
  My_u8g_Panel.drawStr( 0, 30, "everything!");
  My_u8g_Panel.drawStr( 0, 50, "Invent safe!!");
 
}
 
void setup(void) {
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
  } while( My_u8g_Panel.nextPage() );
 
 
}