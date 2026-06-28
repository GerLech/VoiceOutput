/*
||
|| @file VoiceOutput.h
|| @version 1.0
|| @author Gerald Lechner
|| @contact lechge@gmail.com
||||
|| @description
|| | The library uses the ESP8266 library to play mp3 files with numbers and other
|| | keywords. MP3 files are stored in the flash using LittleFS filesystem
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/
#ifndef VoiceOutput_h
#define VoiceOutput_h

#include <Arduino.h>
#include <time.h>
#include "LittleFS.h"
#include "AudioFileSourceLittleFS.h"
#include "AudioFileSourceSD.h"
#include "AudiogeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "vocabulary.h"





//class definition
class VoiceOutput {
public:
  //initializer
  VoiceOutput();

  //start working send reset command and wait for an answer
  bool begin(uint8_t bitClk, uint8_t RLClk, uint8_t dataOut);
  //set the volume vakues from 0 to 30 are allowed
  void setVolume(float volume);
  //set or unset English for date/time format
  void setEnglish(boolean english);
  //set directory
  void setBaseDir(String dir);
  //set the log level >0 = detail log
  void setLogLevel(uint8_t level);
  //output the file named by filename from selected base folder
  void playFile(char * filename);
  //find filename for word number
  void say(const char* key, int16_t word);
  //speaks three digit numbers
  void sayHundreds(uint16_t number);
  //speaks any 32 bit integer
  void sayInt(int32_t number);
  //speaks a float number with 1 or two decimals
  //max value +/- 2147483647.99999
  void sayFloat(float number, uint8_t decimals = 2);
  //say a time using 24 hours and switching seconds off can be done by parameter
  void sayTime(struct tm * s_time, boolean h24 = true, boolean seconds = false);
  //say a date switching weekday and year off can be done by parameter
  //for english month will be followed by day
  //for german day will be followed by month
  void sayDate(struct tm * s_time, boolean weekday = true, boolean sayYear = true);
  void sayMeasurement(float value, uint8_t decimals, int8_t multiplier, int8_t unit);
  void sayAutoMeasurement(float value, uint8_t decimals, int8_t unit);

  boolean _english = false;
  String _base_dir = "/wav";
  uint8_t _fileindex;
  uint8_t _loglevel =0;
  AudioGenerator *audio_gen = NULL;
  AudioFileSource *audio_file = NULL;
  AudioOutputI2S *audio_out = NULL;
};


#endif
