#ifndef Arduit_595_h
#define Arduit_595_h

//988-20
//#if defined(__AVR__)
//#endif
//#elif defined(ARDUINO_ARCH_ESP8266)
//#elif defined(ARDUINO_ARCH_ESP32)

class Arduit_595
{
    public:
        Arduit_595(uint8_t chipCount, uint8_t latchPin, uint8_t clockPin, uint8_t dataPin);
        void pinWrite(uint8_t pin, bool level);
		void pinsWrite(uint8_t from, uint8_t to, bool level); 
		void pinInvert(uint8_t pin);
		int pinRead(uint8_t pin);
    private:
		boolean getChipAndBit (unsigned int digital_Output, uint8_t & chip, byte & mask);
		uint8_t _chipCount;
		uint8_t _latchPin;
		//uint8_t _clockPin;
		//uint8_t _dataPin;
		uint8_t Shift_DO [16] ;  // initial pattern
		//uint8_t _maxDOs ;
		void refreshDOs (); 
};

#endif