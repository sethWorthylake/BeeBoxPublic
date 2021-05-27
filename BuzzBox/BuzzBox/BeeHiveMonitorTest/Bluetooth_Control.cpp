#include "Bluetooth_Control.h"

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
	  //Serial.begin(9600);
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
	unsigned long delay = millis() + MINUTE;
	
	while(delay > millis())
	{
		if (Serial1.available())
		{
			c = Serial1.read();
			if (c == hello[index])
			{
				if (index == 4)
				{
					
					index = 0;	// reset index just in case
					sentIt = 1;	// confirm we sent it
					delay = 0;	// Stop the loop 
					m_SDModule.readToBluetooth();		// give the SD the go ahead to send

				}
				else
					index++;	// Increase the index of the code
			}
			else
				delay = 0; 	// We got junk data so stop it
		}

	}

  while(Serial1.available())
  {
      c = Serial1.read();     // Clear out the Bluetooth line ! There is commonly 5 Null characters that are sent after data transfer. Reason Unkown.
  }
  
	return sentIt;	// return if we sent the files 
}
