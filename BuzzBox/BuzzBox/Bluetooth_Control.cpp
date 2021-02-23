#include "Bluetooth_Control.h"

void setStop()
{
	stop = 1;
}

void clearStop()
{
	stop = 0;
}

Bluetooth_Control::Bluetooth_Control()
{}
Bluetooth_Control::~Bluetooth_Control()
{}

void Bluetooth_Control::Setup()
{
	pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);
}

void Bluetooth_Control::turnOn()
{
	Serial.begin(9600);
    Serial.println("Enter AT commands:");
    //BTserial.begin(38400);
    Serial1.begin(38400);
    Serial.println("BTserial started at 38400");
}

void Bluetooth_Control::turnOff()
{
	Serial.end();
	Serial1.end();
}

int Bluetooth_Control::readyToSend(Data info)
{
	char hello[] = { 'S','E','T','H','W' };
	char c = ' ';
	int index = 0;
	int sentIt = 0;
	int minute = 60000;
	int fiveMinutes = minute * 5; 
	
	clearStop();
	TimeInterrupt.begin(PRECISION);
	TimeInterrupt.addInterrupt(setStop,30000);	// in 1 minute stop this function
	
	while(stop == 0)
	{
		if (Serial1.available())
		{
			c = Serial1.read();
			Serial.write(c);   
			if (c == hello[index])
			{
				if (index == 4)
				{
					index = 0;
					Serial.write("Sending\r\n");
					sentIt = 1;
					sending(info);
					setStop();
				}
				else
					index++;
			}
			else
				setStop();
		}

	}

	TimeInterrupt.removeInterrupt(setStop);
	return sentIt;
}

void Bluetooth_Control::sending(Data info)
{
	Serial.write("\r\nWriting Data\r\n");
	int width = 4;
	int precision = 6;
	char buff[15];
	String string2Send = "";
	float data[4] = {info.m_internal_temp,info.m_external_temp,info.m_humidity,info.m_weight};
  
	for(int ii =0; ii < 4;ii++)
	{
		dtostrf(data[ii], width, precision, buff); 
		string2Send += buff;
		if(ii != 3)
			string2Send += ',';
	
		for(int ff = 0; ff < 15;ff++)
		{
			buff[ff] = 0;
		}
	}
	//Serial.write(string2Send.c_str()); // take out
	Serial1.write(string2Send.c_str());
}

int Bluetooth_Control::available()
{
	return Serial1.available();
}
