
#include "U8glib.h"
int dat = 0;

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);  //(clock, Mosi,cs, ao or DC on mine)

void draw() {
  
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  u8g.setPrintPos(0,22);
  u8g.print(dat);
  //u8g.drawStr( 0, 22, "Hello Kay!"); //This is my output here
}
void setup(void) {
  Serial.begin(9600);//Set Baud Rate to 9600 bps
  // flip screen, if required
  // u8g.setRot180();
   // set SPI backup if required
  //u8g.setHardwareBackup(u8g_backup_avr_spi);
 // assign default color value
  if ( u8g.getMode() == U8G_MODE_R3G3B2 ) {
    u8g.setColorIndex(255);     // white
  }
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT ) {
    u8g.setColorIndex(3);         // max intensity
  }
  else if ( u8g.getMode() == U8G_MODE_BW ) {
    u8g.setColorIndex(1);         // pixel on
  }
  else if ( u8g.getMode() == U8G_MODE_HICOLOR ) {
    u8g.setHiColorByRGB(255,255,255);
  }}
void loop(void) {
  // Temp Loop
  int val;
    
    val=analogRead(0);//Connect LM35 on Analog 0
    dat=(500 * val) /1024;;
    Serial.print("Temp:"); //Display the temperature on Serial monitor
    Serial.print(dat);
    Serial.println("C");
    ;
    delay(500);
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
   // rebuild the picture after some delay
  delay(50);
}
