#include "U8glib.h"
#include "oled_menu.h"
#include <Encoder.h>

#define SSD_WIDTH 128
#define SSD_HEIGH 64

U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_DEV_0|U8G_I2C_OPT_FAST);	// Dev 0, Fast I2C / TWI

void setup(void) {
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);
}

// ----- VARIABILI -----
int selected = 0; //selezione corrente
int prev_selected; //selezione precedente
int next_selected; //selezione successiva

char menu_names[menu_size][20] = {
  {"Spritz"},
  {"GinLem"},
  {"Birra"},
  {"GinTon"},
  {"Prosec"},
  {"VodLem"},
  {"VodTon"},
  {"Acqua"},
  {"Info"}
};

Encoder enc(3, 4);
long oldPos = 0;

// ----- FUNZIONI -----

void drawStrings(int sel, int prev, int next)
{
  switch(sel)
  {
    case 0:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(12, 45, menu_names[prev]);  //left
      u8g.drawStr(98, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //center

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "1/9");
      break;

    case 1:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(100, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "2/9");
      break;

    case 2:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(97, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(48, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "3/9");
      break;

    case 3:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(10, 45, menu_names[prev]);  //left
      u8g.drawStr(99, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "4/9");
      break;

    case 4:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(98, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "5/9");
      break;

    case 5:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(98, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "6/9");
      break;
    case 6:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(100, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(44, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "7/9");
      break;

    case 7:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(8, 45, menu_names[prev]);  //left
      u8g.drawStr(102, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(47, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "8/9");
      break;
    
    case 8:
      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(10, 45, menu_names[prev]);  //left
      u8g.drawStr(98, 45, menu_names[next]);  //right

      u8g.setFont(u8g_font_7x14B);
      u8g.drawStr(51, 50, menu_names[sel]);  //cent

      u8g.setFont(u8g_font_4x6);
      u8g.drawStr(115, 64, "9/9");
      break;
  }
}

void loop(void) {

// ----- ENCODER -----

  long newPos = enc.read();
  if (newPos != oldPos) {
    if(newPos < oldPos)
      selected--;
    else
      selected++;
    oldPos = newPos;
  }

  if(!digitalRead(5))
    Serial.println(menu_names[selected]);


// ----- SETTAGGI -----

  prev_selected = selected - 1;
  next_selected = selected + 1;

// ----- CONTROLLI INTEGRITA -----
  if(prev_selected < 0)
    prev_selected = menu_size - 1;
  
  if(next_selected > (menu_size - 1))
    next_selected = 0;

  if(selected > menu_size - 1)
    selected = 0;

  if(selected < 0)
    selected = menu_size - 1;

// ----- OLED DISPLAY -----

  u8g.firstPage();  
  do {
    u8g.drawXBMP(0, 0, SSD_WIDTH, SSD_HEIGH, menu[selected]); //image
    drawStrings(selected, prev_selected, next_selected);  //strings
  } while( u8g.nextPage() );

}

