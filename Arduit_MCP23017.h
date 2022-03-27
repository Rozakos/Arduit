// Controls MCP23017 16-bit digital I/O chips

#ifndef Arduit_MCP23017_h
#define Arduit_MCP23017_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

extern uint8_t IODataArray[2];

class Arduit_MCP23017
{
    public:
        Arduit_MCP23017();
        void pinMode(int pin, int mode);
        void pinPullup(int pin, int mode);
        void pinWrite(int pin, bool level);
		void pinInvert(int pin); 
        void pinsWrite(uint8_t pinStart, uint8_t pinStop, bool level);		
        int pinRead(int pin);
        void portMode(int port, int value);
        void portPullup(int port, int value);
        void portWrite(int port, int value);
        int portRead(int port);
        void initialize();
    private:
        void WriteRegisters(int port, int startregister, int quantity);
        void ReadRegisters(int port, int startregister, int quantity);
        void WriteRegisterPin(int port, int regpin, int subregister, int level);
};

#endif
