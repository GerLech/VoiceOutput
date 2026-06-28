#include <VoiceOutput.h>
#include <time.h>
#include <LittleFS.h>
#include "SD.h"
#include "SPI.h"

//Pins for I2S bus
#define LRCLK 25//Clock to switch data between left and right channel
#define BCLK 26 //Bitclock
#define DOUT 27  //Data output

#define SD_MISO 32
#define SD_MOSI 13
#define SD_SCK 14
#define SD_CS 33

VoiceOutput td = VoiceOutput();

uint32_t tim;
SPIClass mySPI(HSPI);


void setup() {
  Serial.begin(115200);
  mySPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  audioLogger = &Serial;Serial.println();
  Serial.println("Start");
  if(!SD.begin(SD_CS, mySPI)) {
    Serial.println("Karte konnte nicht initialisiert werden!");
  }
  LittleFS.begin();
  //LittleFS.format();
  td.begin(BCLK,LRCLK,DOUT,true,true,29192);
  td.setVolume(80.0);
  td.setBaseDir("/wav003");
  td.setLogLevel(1);

  
  tim = millis();

  Serial.println("Commands: E=english, G=german, I##=integer, F##.#=float, f##.##=float,");
  Serial.println("Wkk##=word, D=date1, d=date2, T=time1, t=time2, Mxx##.##=Messwert,");
  Serial.println("mxx##.##=Messwert Automatik, Vxxx=Verzeichnis für WAV dateien, L#=Log level");
}

void loop() {
  char s1,s2;
  uint16_t u;
  int8_t m;
  String key;
  if (Serial.available()) {
    time_t t1 = 607016004; //is Mon, 27 Mar 1989 15:33:24 
    time_t t2 = 1610602200; //is Thu, 14 Jan 2021 05:30:00 
    struct tm * s_time;
    String x = Serial.readString();
    Serial.println(x);
    char cmd = x[0];
    x = x.substring(1);
    switch (cmd) {
      case 'E' : td.setEnglish(true); break;
      case 'G' : td.setEnglish(false); break;
      case 'F' : td.sayFloat(x.toFloat(),1); break;
      case 'f' : td.sayFloat(x.toFloat(),2); break;
      case 'I' : td.sayInt(x.toInt()); break;
      case 'T' :  
         s_time = localtime(&t1);
         Serial.println("15:33:24");
         td.sayTime(s_time,true,true);
         break;
      case 't' : 
         s_time = localtime(&t2);
         Serial.println("05:30:00");
         td.sayTime(s_time,false,false);
         break;
      case 'D' : 
         s_time = localtime(&t1);
         Serial.println("Mon, 27 Mar 1989");
         td.sayDate(s_time,true);
         break;
      case 'd' : 
         s_time = localtime(&t2);
         Serial.println("14 Jan 2021");
         td.sayDate(s_time,false);
         break;
      case 'W' : 
         key = x.substring(0,2);
         x = x.substring(2);
         td.say(key.c_str(), x.toInt()); 
         break;
      case 'V' : td.setVolume(x.toFloat()); break;
      case 'L' : td.setLogLevel(x.toInt()); break;
      case 'M' : 
         s1 = x[0];
         s2 = x[1];
         x = x.substring(2);
         m = 0;
         u = WORD_VOLT;
         switch (s1) {
          case 'k' : m = WORD_KILO; break;
          case 'M' : m = WORD_MEGA; break;
          case 'G' : m = WORD_GIGA; break;
          case 'T' : m = WORD_TERA; break;
          case 'm' : m = WORD_MILLI; break;
          case 'u' : m = WORD_MIKRO; break;
          case 'n' : m = WORD_NANO; break;
          case 'p' : m = WORD_PIKO; break;
         }
         switch (s2) {
          case 'V' : u = WORD_VOLT; break;
          case 'A' : u = WORD_AMPER; break;
          case 'W' : u = WORD_WATT; break;
          case 'O' : u = WORD_OHM; break;
          case 'F' : u = WORD_FARAD; break;
          case 'H' : u = WORD_HENRY; break;
          case 'S' : u = WORD_SECOND; break;
         }
         td.sayMeasurement(x.toFloat(),2,m,u); 
         
         break;

      case 'm' : 
         s1 = x[0];
         x = x.substring(1);
         u = WORD_VOLT;
         switch (s1) {
          case 'V' : u = WORD_VOLT; break;
          case 'A' : u = WORD_AMPER; break;
          case 'W' : u = WORD_WATT; break;
          case 'O' : u = WORD_OHM; break;
          case 'F' : u = WORD_FARAD; break;
          case 'H' : u = WORD_HENRY; break;
          case 'S' : u = WORD_SECOND; break;
         }
         td.sayAutoMeasurement(x.toFloat(),2,u); 
         break;
            case 'v' : 
        x = x.substring(0,x.length() - 1);
        td.setBaseDir(x); break;

    }
     
  }

}
