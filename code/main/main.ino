#include "U8glib.h"
#include "oled_menu.h"

#define SSD_WIDTH 128
#define SSD_HEIGH 64

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);	// Dev 0, Fast I2C / TWI

void draw(void) {
  // graphic commands to redraw the complete screen should be placed here  
  u8g.drawXBMP(0, 0, SSD_WIDTH, SSD_HEIGH, all_menus[0]);
}

void setup(void) {
}

void loop(void) {
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  
  // rebuild the picture after some delay
  delay(1000);
}

