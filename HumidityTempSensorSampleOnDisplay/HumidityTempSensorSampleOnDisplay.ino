#include <dht.h>
#include "U8glib.h"
int tem = 0;
int hum = 0;

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);  //(clock, Mosi,cs, ao or DC on mine)
dht DHT;

#define DHT11_PIN 4
void draw() {
  
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  
  u8g.setPrintPos(0,22);
  u8g.print("Temp: ");
  u8g.setPrintPos(50,22);
  u8g.print(tem);
  u8g.setPrintPos(0,50);
  u8g.print("Humidity: ");
  u8g.setPrintPos(75,50);
  u8g.print(hum);
}
void setup(){
  Serial.begin(9600);
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
  }
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  tem = DHT.temperature*9/5 + 32;//Set as C, I converted it to F
  hum = DHT.humidity;
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
      } while( u8g.nextPage() );
   
   // rebuild the picture after some delay
  delay(1000);
}
  //delay(1000);
//}
