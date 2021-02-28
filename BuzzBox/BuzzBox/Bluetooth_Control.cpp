#include "Bluetooth_Control.h"

void setStop()
{
	stop = 1;
}

void clearStop()
{
	stop = 0;
}

Bluetooth_Control::Bluetooth_Control(SDModule & sdRef,int TxD, int RxD) : m_SDModule(sdRef),m_TxD(TxD),m_RxD(RxD)
{}

Bluetooth_Control::~Bluetooth_Control()
{}

void Bluetooth_Control::Setup()
{
	pinMode(m_RxD, INPUT);
    pinMode(m_TxD, OUTPUT);
}

void Bluetooth_Control::turnOn()
{
	Serial.begin(9600);
    //Serial.println("Enter AT commands:");
    //BTserial.begin(38400);
    Serial1.begin(38400);	
    //Serial.println("BTserial started at 38400");	// can probably get rid of this
}

void Bluetooth_Control::turnOff()
{
	Serial.end();	// Not worth calling
	Serial1.end();
}

int Bluetooth_Control::available()
{
	return Serial1.available();	// returns if there is serial communication from the bluetooth waiting
}

int Bluetooth_Control::readyToSend()
{
	char hello[] = { 'S','E','T','H','W' };	// Secret code that when recieved we will send all data to the Bluetooth
	char c = ' ';	// Character pointer 
	int index = 0;	// current index of the code
	int sentIt = 0;	// Have we sent the stuff
	int delay = MINUTE * 3; 
	
	clearStop();	// Clear the global 
	TimeInterrupt.begin(PRECISION);	// Set the interupt mode to precise
	TimeInterrupt.addInterrupt(setStop,delay);	// in delay time: call the setStop function 
	
	while(stop == 0)
	{
		if (Serial1.available())
		{
			c = Serial1.read();
			if (c == hello[index])
			{
				if (index == 4)
				{
					
					index = 0;
					sentIt = 1;
					TimeInterrupt.removeInterrupt(setStop);	// disable that interupt
					setStop();							// set the stop bit 
					m_SDModule.readToBluetooth();		// give the SD the go ahead to send

				}
				else
					index++;
			}
			else
				setStop();	// We got junk data so stop waiting 
		}

	}
	if(sentIt == 0)
		TimeInterrupt.removeInterrupt(setStop);	// Remove if we didnt in the loop
	
	return sentIt;	// return if we sent the files 
}
