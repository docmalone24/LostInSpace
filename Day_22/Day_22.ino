#include <U8glib.h>
 
U8GLIB_SH1106_128X64  My_u8g_Panel(U8G_I2C_OPT_NONE); // I2C / TWI
 
/*
 * For documentation on u8glib functions:
https://github.com/olikraus/u8glib/wiki/userreference
 */
 
uint8_t draw_state = 0;
 
// ************************************************
void setup(void) {
 
  // flip screen, if required
  //u8g.setRot180();
 
  #if defined(ARDUINO)
    pinMode(13, OUTPUT);          
    digitalWrite(13, HIGH);  
  #endif
}
 
// ************************************************
void loop(void) {
 
  // picture loop  
  My_u8g_Panel.firstPage();  
  do {
    draw();
  } while( My_u8g_Panel.nextPage() );
 
  // increase the state
  draw_state++;
  if ( draw_state >= 9*8 )
    draw_state = 0;
 
  // rebuild the picture after some delay
  //delay(150);
 
}
 
// ************************************************
 
void draw(void) {
  u8g_prepare();
  switch(draw_state >> 3) {
    case 0: u8g_box_frame(draw_state&7); break;
    case 1: u8g_disc_circle(draw_state&7); break;
    case 2: u8g_r_frame(draw_state&7); break;
    case 3: u8g_string(draw_state&7); break;
    case 4: u8g_line(draw_state&7); break;
    case 5: u8g_triangle(draw_state&7); break;
    case 6: u8g_ascii_1(); break;
    case 7: u8g_ascii_2(); break;
    case 8: u8g_extra_page(draw_state&7); break;
  }
}
 
void u8g_prepare(void) {
  My_u8g_Panel.setFont(u8g_font_6x10);
  My_u8g_Panel.setFontRefHeightExtendedText();
  My_u8g_Panel.setDefaultForegroundColor();
  My_u8g_Panel.setFontPosTop();
}
 
void u8g_box_frame(uint8_t a) {
  My_u8g_Panel.drawStr( 0, 0, "drawBox");
  My_u8g_Panel.drawBox(5,10,20,10);
  My_u8g_Panel.drawBox(10+a,15,30,7);
  My_u8g_Panel.drawStr( 0, 30, "drawFrame");
  My_u8g_Panel.drawFrame(5,10+30,20,10);
  My_u8g_Panel.drawFrame(10+a,15+30,30,7);
}
 
void u8g_disc_circle(uint8_t a) {
  My_u8g_Panel.drawStr( 0, 0, "drawDisc");
  My_u8g_Panel.drawDisc(10,18,9);
  My_u8g_Panel.drawDisc(24+a,16,7);
  My_u8g_Panel.drawStr( 0, 30, "drawCircle");
  My_u8g_Panel.drawCircle(10,18+30,9);
  My_u8g_Panel.drawCircle(24+a,16+30,7);
}
 
void u8g_r_frame(uint8_t a) {
  My_u8g_Panel.drawStr( 0, 0, "drawRFrame/Box");
  My_u8g_Panel.drawRFrame(5, 10,40,30, a+1);
  My_u8g_Panel.drawRBox(50, 10,25,40, a+1);
}
 
void u8g_string(uint8_t a) {
  My_u8g_Panel.drawStr(30+a,31, " 0");
  My_u8g_Panel.drawStr90(30,31+a, " 90");
  My_u8g_Panel.drawStr180(30-a,31, " 180");
  My_u8g_Panel.drawStr270(30,31-a, " 270");
}
 
void u8g_line(uint8_t a) {
  My_u8g_Panel.drawStr( 0, 0, "drawLine");
  My_u8g_Panel.drawLine(7+a, 10, 40, 55);
  My_u8g_Panel.drawLine(7+a*2, 10, 60, 55);
  My_u8g_Panel.drawLine(7+a*3, 10, 80, 55);
  My_u8g_Panel.drawLine(7+a*4, 10, 100, 55);
}
 
void u8g_triangle(uint8_t a) {
  uint16_t offset = a;
  My_u8g_Panel.drawStr( 0, 0, "drawTriangle");
  My_u8g_Panel.drawTriangle(14,7, 45,30, 10,40);
  My_u8g_Panel.drawTriangle(14+offset,7-offset, 45+offset,30-offset, 57+offset,10-offset);
  My_u8g_Panel.drawTriangle(57+offset*2,10, 45+offset*2,30, 86+offset*2,53);
  My_u8g_Panel.drawTriangle(10+offset,40+offset, 45+offset,30+offset, 86+offset,53+offset);
}
 
void u8g_ascii_1() {
  char s[2] = " ";
  uint8_t x, y;
  My_u8g_Panel.drawStr( 0, 0, "ASCII page 1");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 32;
      My_u8g_Panel.drawStr(x*7, y*10+10, s);
    }
  }
}
 
void u8g_ascii_2() {
  char s[2] = " ";
  uint8_t x, y;
  My_u8g_Panel.drawStr( 0, 0, "ASCII page 2");
  for( y = 0; y < 6; y++ ) {
    for( x = 0; x < 16; x++ ) {
      s[0] = y*16 + x + 160;
      My_u8g_Panel.drawStr(x*7, y*10+10, s);
    }
  }
}
 
void u8g_extra_page(uint8_t a)
{
  if ( My_u8g_Panel.getMode() == U8G_MODE_HICOLOR || My_u8g_Panel.getMode() == U8G_MODE_R3G3B2) {
    /* draw background (area is 128x128) */
    u8g_uint_t r, g, b;
    b = a << 5;
    for( g = 0; g < 64; g++ )
    {
      for( r = 0; r < 64; r++ )
      {
    My_u8g_Panel.setRGB(r<<2, g<<2, b );
    My_u8g_Panel.drawPixel(g, r);
      }
    }
    My_u8g_Panel.setRGB(255,255,255);
    My_u8g_Panel.drawStr( 66, 0, "Color Page");
  }
  else if ( My_u8g_Panel.getMode() == U8G_MODE_GRAY2BIT )
  {
    My_u8g_Panel.drawStr( 66, 0, "Gray Level");
    My_u8g_Panel.setColorIndex(1);
    My_u8g_Panel.drawBox(0, 4, 64, 32);    
    My_u8g_Panel.drawBox(70, 20, 4, 12);
    My_u8g_Panel.setColorIndex(2);
    My_u8g_Panel.drawBox(0+1*a, 4+1*a, 64-2*a, 32-2*a);
    My_u8g_Panel.drawBox(74, 20, 4, 12);
    My_u8g_Panel.setColorIndex(3);
    My_u8g_Panel.drawBox(0+2*a, 4+2*a, 64-4*a, 32-4*a);
    My_u8g_Panel.drawBox(78, 20, 4, 12);
  }
  else
  {
    My_u8g_Panel.drawStr( 0, 12, "setScale2x2");
    My_u8g_Panel.setScale2x2();
    My_u8g_Panel.drawStr( 0, 6+a, "setScale2x2");
    My_u8g_Panel.undoScale();
  }
}