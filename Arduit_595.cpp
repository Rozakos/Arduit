#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Arduit_595.h"
#include <SPI.h>
  
Arduit_595::Arduit_595(uint8_t chipCount, uint8_t latchPin, uint8_t clockPin, uint8_t dataPin) 
{
	pinMode(latchPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(dataPin, OUTPUT);
	
	_chipCount = chipCount;
	_latchPin = latchPin;
	//_clockPin = clockPin;
	//_dataPin = dataPin;
	
	for (uint8_t i = _chipCount; i > 0; i--)	
	{
		Shift_DO [i] = { 0 };  // initial pattern
	}
	
	refreshDOs();
}//----------------------------------------------------------------------
	
void Arduit_595::refreshDOs ()  
{
	SPI.begin();
	digitalWrite (_latchPin, LOW);
	
	for (uint8_t i = _chipCount; i > 0; i--)	
	{
		SPI.transfer (Shift_DO [i]); 
	}
	
	digitalWrite (_latchPin, HIGH);
	SPI.end();
		
} 	// end of refreshDOs
	
	
boolean Arduit_595::getChipAndBit (unsigned int digital_Output, uint8_t & chip, byte & mask)  // turn an DO number into the position in the array, and a bit mask
{
	//uint8_t _maxDOs = _chipCount * 8;
	
	if (digital_Output > _chipCount * 8)
	{
		return true;  // error
	} // end of too high
    
	digital_Output--;  // make zero relative		
	chip = (digital_Output / 8) + 1;  // divide by 8 to work out which chip		
	mask = 1 << (digital_Output % 8);  // remainder is bit number  
	
	return false;  // no error
}  // end of getChipAndBit
	


void Arduit_595::pinWrite(uint8_t pin, bool level)
{
	if (pin == 0)  // zero means all
	{
		for (uint8_t i = _chipCount; i > 0; i--) 	
		{	
			if(level == 0)
			{
				Shift_DO [i] = 0;  //All 0
			}
			else
			{
				Shift_DO [i] = 0xFF;  //All 1
			}
		}
		refreshDOs();
		return;
	}  // end of if zero
	
	uint8_t chip;
	uint8_t mask;
	if (getChipAndBit (pin, chip, mask))
	{
		return;  // bad number
	}	
		
	if(level == 0)
	{
		Shift_DO [chip] &= ~ mask;  //0
	}
	else
	{
		Shift_DO [chip] |= mask;  //1
	}			

	refreshDOs();	
}


	
void Arduit_595::pinInvert(uint8_t pin)  // invert DO pin (or all if zero)
{	
	if (pin == 0)  // zero means all
	{
		//for (uint8_t i = _chipCount - 1; i >= 0; i--) 
		for (uint8_t i = _chipCount; i > 0; i--)	
		{
			Shift_DO [i] ^= 0xFF;
		}
		refreshDOs () ;
		return;
	} // end of if zero
    
	uint8_t chip;
	uint8_t mask;
	if (getChipAndBit (pin, chip, mask))
	{
		return;  // bad number  
	}

	Shift_DO [chip] ^= mask;
	
	refreshDOs () ;
}  // end of invertDO
  
int Arduit_595::pinRead(uint8_t pin)
{
  	uint8_t chip;
	uint8_t mask;
  	if (getChipAndBit (pin, chip, mask))
	{
		return;  // bad number  
	}
	
	bool actualValue = Shift_DO[chip] & mask;
	if (actualValue == 0)
	{
		return 0;
	}	
	else
	{		
		return 1;
	}
}

void Arduit_595::pinsWrite(uint8_t from, uint8_t to, bool level) 
{
	for (uint8_t i = from ; i <= to ; i++) 
	{
		pinWrite(i, level);
	}
}//setPins()---	