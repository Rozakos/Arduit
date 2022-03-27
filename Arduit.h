/* This library controls the functions of Arduit

1. - Nokia LCD display and backlight (PCD8544)
2. - x16 digitalIO(i2c)  MCP23017
  //- Buzzer
  //- Thermocouple
  -Timer
// Change History:
 17/11/2014        Initial Version
*/

#ifndef ARDUIT_H
#define ARDUIT_H

#ifdef USE_595
	#include "Arduit_595.h"	
#endif
#ifdef USE_23017
	#include "Arduit_MCP23017.h"	
#endif
#ifdef USE_4067
	#include "Arduit_4067.h"
#endif

//#include "Arduit_Timer.h"
//#include "Arduit_Timmer.h"
//#include "Arduit_PCD8544.h"
//*********************************************************************************
//***************************  Comunication Set  **********************************
//*********************************************************************************
char c;
byte index = 0;
String masege[20]={};
boolean reading = false; //Char Read
boolean getInputComplete = false;
boolean getComand = false;
#define SerialBoud 115200 // Taxita Seriaki
#define Delimiter '&' // Diaxoristis gia endoles {38}
#define SubDelimiter '#' // Diaxoristis gia endoles {35}
#define StartInput '?' // Pos Ksekinai i grami  {63}
#define EndInput '!' // Pos tlioni i grami  {33}
#define ID "a1"    // ID tis siskevis
#define EndLiine "\r\n"//"\n\r" // 

#define ONELES {int len = masege[index].length();masege[index] = masege[index].substring(0, len -1);} //Za Backspase i Delite 
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj; }  //Print Class <<


#ifdef DEBUG
	#define DEBUG_PRINTLN(x)  Serial << (x) << EndLiine;
	#define DEBUG_PRINT(x)  Serial << (x);
#else
	#define DEBUG_PRINTLN(x)
	#define DEBUG_PRINT(x)
#endif 


#endif // ARDUIT_H
