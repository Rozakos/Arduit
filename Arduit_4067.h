#ifndef Arduit_4067_h
#define Arduit_4067_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#define MUX_IO_READ 0
#define MUX_IO_WRITE 1

class Arduit_4067
{
    public:
        Arduit_4067();
		Arduit_4067(int adresPin0, int adresPin1, int adresPin2, int adresPin3, int signalPin=A0, int enablePin=-1);
		void setup(int adresPin0, int adresPin1, int adresPin2, int adresPin3, int signalPin=A0, int enablePin=-1);
		void setEnabled(bool enabled);
		int pinReadA(int channel);
		int pinReadD(int channel);
		void pinWriteA(int channel, int value);
        void pinWriteD(int pin, int level);
        
    private:
        int enablePin; // EN - HIGH==all outputs disabled, LOW==everything is enabled
		int signalPin;
		int adresPin0;
		int adresPin1;
		int adresPin2;
		int adresPin3;	
		int lastIO;
		int currentChannel;	
		void setChannel(int channel);
};

#endif

