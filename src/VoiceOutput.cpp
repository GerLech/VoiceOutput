//Version 1.0

#include "LittleFS.h"
#include "SD.h"
#include "VoiceOutput.h"

VoiceOutput::VoiceOutput(){

};


bool VoiceOutput::begin(uint8_t bitClk, uint8_t RLClk, uint8_t dataOut){ //external I2S device {
  audio_file = new AudioFileSourceSD();
  audio_out = new AudioOutputI2S();
  audio_out->SetPinout(bitClk, RLClk, dataOut);
  setVolume(100);
  audio_gen = new AudioGeneratorWAV();
  return true;
}

//set the volume vakues from 0 to 30 are allowed
void VoiceOutput::setVolume(float volume)
{
    if (volume > 100) volume = 100;
    audio_out->SetGain(volume * volume / 10000.0);
}

//set or unset English for language
void VoiceOutput::setEnglish(boolean english) {
  _english = english;
}

//set the log level >0 = details
void VoiceOutput::setLogLevel(uint8_t level) {
  _loglevel = level;
}

void VoiceOutput::setBaseDir(String dir) {
  _base_dir = dir;
}
void VoiceOutput::playFile(char * filename)
{
  //Serial.printf("File %s öffnen\n",filename);
  if (audio_file->open(filename)) {
    if (_loglevel > 0) Serial.println("Start output");
    audio_gen->begin(audio_file, audio_out);
    if (_loglevel > 0) Serial.println("Wait for End");
    while (audio_gen->isRunning() && audio_gen->loop()) yield;
    audio_gen->stop();
    if (_loglevel > 0) Serial.println("Done");
    audio_file->close();
  } else {
    Serial.printf("Kann File %s nicht öffnen\n",filename);
  }
}
//get filename for word number
void VoiceOutput::say(const char* key,int16_t word) {
  char filename[32];
  if ((key == "mu")&&(word == 0)) return;
  sprintf(filename,"%s/%s%d.wav",_base_dir.c_str(),key,word);
  if (_loglevel > 0) Serial.printf("Play file%s\n",filename );
  playFile(filename);
}

//speaks three digit numbers
void VoiceOutput::sayHundreds(uint16_t number) {
  uint16_t h = number / 100;
  uint16_t e = number%100;
  if (h==1) say(KEY_HUNDREDS,WORD_ONEHUNDRED);
  if (h>1) {
    say(KEY_NUMBERS,h);
    say(KEY_HUNDREDS,WORD_HUNDREDS);
  }
  if (e>0) say(KEY_NUMBERS,e);
}

//speaks any 32 bit integer
void VoiceOutput::sayInt(int32_t number) {
 if (number == 0) {
   say(KEY_NUMBERS,0);
 } else {
   boolean minus = (number < 0);
   if (minus) number *= -1;
   uint16_t einer = number%1000;
   number /= 1000;
   uint16_t tausender = number%1000;
   number /= 1000;
   uint16_t millionen = number%1000;
   number /= 1000;
   uint16_t milliarden = number%1000;
   if (minus) say(KEY_SPECIAL, WORD_MINUS);
   if (milliarden > 0) {
    if (milliarden == 1) {
      say(KEY_BILLION, WORD_ONEBILLION);
    } else  {
      sayHundreds(milliarden);
      say(KEY_BILLION, WORD_BILLION);
    }
   }
   if (millionen > 0) {
    if (millionen == 1) {
      say(KEY_MILLION, WORD_ONEMILLION);
    } else  {
      sayHundreds(millionen);
      say(KEY_MILLION, WORD_MILLION);
    }
   }
   if (tausender > 0) {
    if (tausender == 1) {
      say(KEY_TOUSENDS, WORD_ONETOUSEND);
    } else  {
      sayHundreds(tausender);
      say(KEY_TOUSENDS, WORD_TOUSEND);
    }
   }
   sayHundreds(einer);
 }
}

//speaks a float number with 1 or two decimals
//max value +/- 2147483647.99999
void VoiceOutput::sayFloat(float number, uint8_t decimals) {
  int32_t num = (int)number;
  float n = number - (float)num;
  if (n<0) n = n * -1;
  int dez = 0;
  if ((decimals == 2) && (n >= 0.1) && (n <= 0.99)) {
    dez = round(n * 100);
    sayInt(num);
    say(KEY_SPECIAL, WORD_DOT);
    sayInt(dez);
  }
  else
  {
    uint32_t d = 1;
    for (uint8_t i = 0; i<decimals; i++) d = d * 10;
    dez = round(n * d);
    if (dez == d) {
      dez = 0;
      num ++;
    }
    sayInt(num);
    say(KEY_SPECIAL, WORD_DOT);
    d = d/10;
    for (uint8_t i = 0; i<decimals; i++) {
      say(KEY_NUMBERS,dez / d);
      dez = dez % d;
      d = d/10;
    }
  }
}

//say a time using 24 hours and switching seconds off can be done by parameter
void VoiceOutput::sayTime(struct tm * s_time, boolean h24, boolean seconds) {
   uint16_t ampm = WORD_AM;
   uint8_t hour = s_time->tm_hour;
   if ((hour > 11) && (!h24)) {
     ampm = WORD_PM;
     hour = hour - 12;
   }
   if (hour == 0) hour = 12;
   say(KEY_NUMBERS, hour);
   if (_english) {
     delay(200);
   } else {
     say(KEY_SPECIAL, WORD_CLOCK);
   }
   say(KEY_NUMBERS,s_time->tm_min);
   if(!h24) say(KEY_SPECIAL,ampm);
   if (seconds) {
     say(KEY_SPECIAL, WORD_AND);
     if (s_time->tm_sec == 1) {
       say(KEY_UNITS,WORD_1_SECOND);
     } else {
       say(KEY_NUMBERS,s_time->tm_sec);
       say(KEY_UNITS, WORD_SECOND);
     }
   }
}

//say a date switching weekday and year off can be done by parameter
//for english month will be followed by day
//for german day will be followed by month
void VoiceOutput::sayDate(struct tm * s_time, boolean weekday, boolean sayYear) {
  if (weekday) say(KEY_WEEKDAY,s_time->tm_wday);
  if (_english) {
    say(KEY_MONTH, s_time->tm_mon);
    say(KEY_NUMBERS,s_time->tm_mday);
  } else {
    say(KEY_ORDINAL_NUMBERS, s_time->tm_mday);
    say(KEY_MONTH, s_time->tm_mon);
  }
  if (sayYear) {
    uint16_t year = s_time->tm_year + 1900;
    if (year < 2000) {
      say(KEY_NUMBERS,year/100);
      say(KEY_HUNDREDS,WORD_HUNDREDS);
      say(KEY_NUMBERS, year%100);
    } else {
      sayInt(year);
    }
  }
}

void VoiceOutput::sayMeasurement(float value, uint8_t decimals, int8_t multiplier, int8_t unit) {
  sayFloat(value,decimals);
  say(KEY_MULTIPLICATOR,multiplier);
  say(KEY_UNITS, unit);
}

void VoiceOutput::sayAutoMeasurement(float value, uint8_t decimals, int8_t unit) {
  int8_t mult = 0;
  if (value >= 1.0){
    while (value >= 1000.0) {
      value = value/1000.0;
      mult += 1;
    }
  }else{
    while (value < 1.0) {
      value = value*1000.0;
      mult -= 1;
    }
  }
  sayFloat(value,decimals);
  say(KEY_MULTIPLICATOR,mult);
  say(KEY_UNITS, unit);
}
