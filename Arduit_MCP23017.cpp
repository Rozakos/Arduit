// Controls MCP23017 16-bit digital I/O chips

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "Arduit_MCP23017.h"
#include <Wire.h>

uint8_t IODataArray[2] = {0};

#define IOAddress 0b0100000

Arduit_MCP23017::Arduit_MCP23017()
{
  // no constructor tasks yet
}

// Set device to default values
void Arduit_MCP23017::initialize()
{
	Wire.begin(); // Wake up I2C bus
	for (int j = 0; j < 7; j++) 
	{

		IODataArray[0] = 255;
		IODataArray[1] = 255;
		WriteRegisters(j, 0x00, 2);
		IODataArray[0] = 0;
		IODataArray[1] = 0;

		for (int k = 2; k < 0x15; k+=2) 
		{
			WriteRegisters(j, k, 2);
		}

	}

}

void Arduit_MCP23017::WriteRegisters(int port, int startregister, int quantity) 
{

	Wire.beginTransmission(IOAddress + port);
    Wire.write((byte)startregister);
    for (int i = 0; i < quantity; i++) 
	{
        Wire.write((byte)IODataArray[i]);
    }
	Wire.endTransmission();

}

void Arduit_MCP23017::ReadRegisters(int port, int startregister, int quantity) 
{

	Wire.beginTransmission(IOAddress + port);
    Wire.write((byte)startregister);
    Wire.endTransmission();
    Wire.requestFrom(IOAddress + port, quantity);
    for (int i = 0; i < quantity; i++) 
	{               
		IODataArray[i] = Wire.read();        
	}

}

void Arduit_MCP23017::WriteRegisterPin(int port, int regpin, int subregister, int level) 
{

	ReadRegisters(port, subregister, 1);   
	if (level == 0) 
	{
		IODataArray[0] &= ~(1 << regpin);
	}
	else 
	{
		IODataArray[0] |= (1 << regpin);
	} 
	WriteRegisters(port, subregister, 1);
  
}

void Arduit_MCP23017::pinMode(int pin, int mode) 
{
  
	int port = pin >> 4;
	int subregister = (pin & 8) >> 3;
	int regpin = pin - ((port << 1) + subregister)*8;
	WriteRegisterPin(port, regpin, subregister, mode ^ 1);
  
}

void Arduit_MCP23017::pinPullup(int pin, int mode) 
{
  
	int port = pin >> 4;
	int subregister = (pin & 8) >> 3;
	int regpin = pin - ((port << 1) + subregister)*8;
	WriteRegisterPin(port, regpin, 0x0C + subregister, mode);
  
}

void Arduit_MCP23017::pinWrite(int pin, bool level) 
{
  
	int port = pin >> 4;
	int subregister = (pin & 8) >> 3;
	int regpin = pin - ((port << 1) + subregister)*8;
	WriteRegisterPin(port, regpin, 0x12 + subregister, level);
  
}

void Arduit_MCP23017::pinInvert(int pin) 
{
	pin = pin -1;
	bool Stat = pinRead(pin);
	pinWrite(pin , !Stat);
}

void Arduit_MCP23017::pinsWrite(uint8_t pinStart, uint8_t pinStop, bool level) 
{
  
	for (int i = pinStart ; i <= pinStop ; i++) 
	{
		pinWrite(i, level);
	}
  
}

int Arduit_MCP23017::pinRead(int pin) 
{

	int port = pin >> 4;
	int subregister = (pin & 8) >> 3;
	ReadRegisters(port, 0x12 + subregister, 1);
	int returnval = (IODataArray[0] >> (pin - ((port << 1) + subregister)*8)) & 1;

	return returnval;

}

void Arduit_MCP23017::portMode(int port, int value) 
{
  
	IODataArray[0] = value;
	IODataArray[1] = value>>8;  
	WriteRegisters(port, 0x00, 2);
  
}

void Arduit_MCP23017::portWrite(int port, int value) 
{
  
	IODataArray[0] = value;
	IODataArray[1] = value>>8; 
	WriteRegisters(port, 0x12, 2);
  
}

void Arduit_MCP23017::portPullup(int port, int value) 
{
  
	IODataArray[0] = value;
	IODataArray[1] = value>>8;
	WriteRegisters(port, 0x0C, 2);
  
}

int Arduit_MCP23017::portRead(int port) 
{

	ReadRegisters(port, 0x12, 2);
	int receivedval = IODataArray[0];
	receivedval |= IODataArray[1] << 8;

	return receivedval;  

}
