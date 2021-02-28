//#include <SoftwareSerial.h>
#include "Bluetooth_Control.h"
#include "Data.h"
#include "TemperatureModule.h"
#include "humidity.h"
#include "SDModule.h"
#include <stdlib.h>

///*
// Name:    BlueTooth_Test.ino
// Created: 1/24/2021 1:22:36 PM
// Author:  Seth
//*/
SDModule SD_test(53);
Bluetooth_Control Bluetooth_test(SD_test,18,19);	//TxD 18, RxD 19
TemperatureModule Temperature_test(2);
humidity Humiture_test(3); // add thing where we get to specify port

void setup()
{
    Bluetooth_test.Setup();
    Bluetooth_test.turnOn();
    if(!SD_test.setup())
      Serial.println("SD NOT CORRECT"); 
    //No tempurature setup function
    Humiture_test.begin();
}

void loop()
{    
  Data user(Temperature_test.collectTemp(),Temperature_test.collectTemp(),Humiture_test.get_humidity(),104.01987);

  if(SD_test.write(user.toString(),user.getYear(),user.getMonth()))
    Serial.println("Sd Confirmed Send");
  
  Serial.println(user.toString());  
	Serial.write("Entering While Loop ");
	while(1)
	{
			int retval = 0;
			if(Bluetooth_test.available())
			{
				Serial.write("Entering Send\r\n");
				retval = Bluetooth_test.readyToSend();
				if(retval == 0)
					Serial.write("No Send\r\n");
				else
					Serial.write("Sent it\r\n");	
			}
	}
}