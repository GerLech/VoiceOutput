# Voice Output
This library allows to speak number, date or time. It uses the library ESP8266Audio. The output to speaker is handled over I2S with the MAX98357A . The speech output is based on WAV files. Files are on a SD card.
The constructor

**VoiceOutput()**

**bool begin(*uint8&#95;t bitClk, uint8&#95;t RLClk, uint8&#95;t dataOut)***  Starts the instance, to use I2S bus. Parameter are the pin-numbers for I2S bus.

**void setEnglish(float volume)** Set the volume in percent

**void setVolume(boolean english)** Select the english way for date and time

**void setBaseDir(String dir)** set the base directory for the words on the SD card

**void setLogLevel(uint8&#95;t level)** Set the log level 0 = no logs except errors

**void playFile(char &#42; filename)** Play a file from SD card

**void say(const char&#42; key, int16&#95;t word)** Say the word in the group with the key

**void sayHundreds(uint16&#95;t number)** Speaks positive three digit numbers from 0 to 999

**void sayInt(int32&#95;t number)** Speaks any 32 bit integer. Range +/- 2147483647

**void sayFloat(float number, uint8&#95;t decimals = 2)** Speaks a float number with 1 or two decimals. Range +/- 2147483647.99

**void sayTime(struct tm &#42; s&#95;time, boolean h24 = true, boolean seconds = false)** Speak the time specified in the tm structure. Using 24 hours and switching seconds off can be selected by parameter.

**void sayDate(struct tm &#42; s&#95;time, boolean weekday = true, boolean sayYear = true)** Speak the date specified by the tm structure. Switching weekday and year off can be selected by parameter

**void sayMeasurement(float value, uint8&#95;t decimals, int8&#95;t multiplier, int8&#95;t unit)** Speak a result of a measurement. Number of decimals is the same as for sayFloat. The multiplier is the index for multiplier words "pico" = - 4 up to "tera" = 4, The unit is the index in the unit group.

**void sayAutoMeasurement(float value, uint8&#95;t decimals, int8&#95;t unit)** The same as sayMeasurement, but multiplier is calculated by program- A Value of 0.123 will be changed to "123 mili" or 15200 to "15.2 kilo"



## Vocabulary

the words are splitted into 12 groups. Every group has a two character key
The filename for the words on SD card is buildt from the two chatacter key and the index within the group.
A header file  vocabulary.h contains constants for all necessary keys and indexes:

//vocabulary
//KEY_NUMBERS
#define KEY_NUMBERS "zh"
//KEY_HUNDREDS
#define KEY_HUNDREDS "hu"
#define WORD_HUNDREDS 0
#define WORD_ONEHUNDRED 1
//KEY_TOUSENDS
#define KEY_TOUSENDS "tu"
#define WORD_TOUSEND 0
#define WORD_ONETOUSEND 1
//KEY_MILLION
#define KEY_MILLION "mi"
#define WORD_MILLION 0
#define WORD_ONEMILLION 1
//KEY_BILLION
#define KEY_BILLION "mr"
#define WORD_BILLION 0
#define WORD_ONEBILLION 1
//KEY_ORDINAL_NUMBERS
#define KEY_ORDINAL_NUMBERS "zp"
//KEY_WEEKDAY
#define KEY_WEEKDAY "wt"
//KEY_MONTH
#define KEY_MONTH "mo"
//KEY_SPECIAL
#define KEY_SPECIAL "xx"
#define WORD_IT_IS 0
#define WORD_CLOCK 1
#define WORD_IS 2
#define WORD_AND 3
#define WORD_DOT 4
#define WORD_MINUS 5
#define WORD_PLUS 6
#define WORD_AM 7
#define WORD_PM 8
#define WORD_ERROR 9
#define WORD_DONE 10
#define WORD_READY 11
#define WORD_OK 12
#define WORD_OVERFLOW 13
//KEY_UNITS
#define KEY_UNITS "un"
#define WORD_SECOND 0
#define WORD_1_SECOND 1
#define WORD_MINUTES 2
#define WORD_1_MINUTE 3
#define WORD_HOURS 4
#define WORD_1_HOUR 5
#define WORD_DAYS 6
#define WORD_1_DAY 7
#define WORD_WEEKS 8
#define WORD_1_WEEK 9
#define WORD_MONTHS 10
#define WORD_1_MONTH 11
#define WORD_YEARS 12
#define WORD_1_YEAR 13
#define WORD_PERCENT 14
#define WORD_CELSIUS 15
#define WORD_FAHRENHEIT 16
#define WORD_HECTOPASCAL 17
#define WORD_LUX 18
#define WORD_VOLT 19
#define WORD_AMPER 20
#define WORD_OHM 21
#define WORD_WATT 22
#define WORD_HZ 23
#define WORD_FARAD 24
#define WORD_HENRY 25
//KEY_MULTIPLICATOR
#define KEY_MULTIPLICATOR "mu"
#define WORD_PIKO -4
#define WORD_NANO -3
#define WORD_MIKRO -2
#define WORD_MILLI -1
#define WORD_NONE 0
#define WORD_KILO 1
#define WORD_MEGA 2
#define WORD_GIGA 3
#define WORD_TERA 4
//KEY_MEASUREMENT
#define KEY_MEASUREMENT "ma"
#define WORD_TEMPERATURE 0
#define WORD_HUMIDITY 1
#define WORD_PRESSURE 2
#define WORD_DURATION 3
#define WORD_TIME 4
#define WORD_DATE 5
#define WORD_VOLTAGE 6
#define WORD_CURRENT 7
#define WORD_DIRECT 8
#define WORD_ALTERNATE 9
#define WORD_RESISTOR 10
#define WORD_FREQUENCY 11
#define WORD_POWER 12
#define WORD_CAPACITY 13
#define WORD_INDUCTANCE 14
#define WORD_ILLUMINANCE 15
