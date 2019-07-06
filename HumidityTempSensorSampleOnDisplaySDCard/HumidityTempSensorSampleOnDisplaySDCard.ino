#include <dht.h>
#include "U8glib.h"
#include <SD.h>
#include <SPI.h>
// Got SD code from here https://howtomechatronics.com/tutorials/arduino/arduino-sd-card-data-logging-excel-tutorial
File myFile;

int pinCS = 53;

float tem = 0;
float hum = 0;

U8GLIB_SH1106_128X64 u8g(13, 11, 10, 9);  //(clock, Mosi,cs, ao or DC on mine)
dht DHT;

#define DHT11_PIN 4
void draw() {
  
  // graphic commands to redraw the complete screen should be placed here  
  u8g.setFont(u8g_font_unifont);
  
  u8g.setPrintPos(0,22);
  u8g.print("Temp: ");
  u8g.setPrintPos(40,22);
  u8g.print(tem);
  u8g.setPrintPos(0,50);
  u8g.print("Humidity: ");
  u8g.setPrintPos(75,50);
  u8g.print(hum);
  u8g.setPrintPos(115,50);
  u8g.print("%");
}
void setup(){
  Serial.begin(9600);
  pinMode(pinCS,OUTPUT);

// SD Card Use
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
//  DHT.begin();    //Starts the DHT sensor

  //Setup for the Display
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
  float chk = DHT.read11(DHT11_PIN);
  tem = DHT.temperature*9/5 + 32;//Set as C, I converted it to F
  hum = DHT.humidity;
  /*Serial.print("Temperature = ");
  Serial.println(tem);
  Serial.print("Humidity = ");
  Serial.println(hum);*/
  Serial.print(tem);
  Serial.print(",");
  Serial.println(hum);
  //Serial.print(",");

  myFile = SD.open("test.txt", FILE_WRITE);
  if(myFile){
    myFile.print(tem);
    myFile.print(",");
    myFile.println(hum);
    //myFile.print(",");
    myFile.close();
  }

  else{
    Serial.println("error opening test.txt");
  }
  
  
  // picture loop
  u8g.firstPage();  
  do {
    draw();
      } while( u8g.nextPage() );
   
   // rebuild the picture after some delay
  delay(3000);
}
 
