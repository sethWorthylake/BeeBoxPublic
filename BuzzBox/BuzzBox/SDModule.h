/*
*	Author: 	Killian Laws
*	Date: 		February 23 2021
*	Project: 	Buzzbox Beehive Monitor
*
*	Description: SD Module Driver File
*
*		Pin Configuration (Permanent): onboard 3.3Vpin for power
*									   onboard GND pin for GND
*
*									ARDUINO UNO PINOUT:
*									   MOSI = Digital 11
*									   MISO = Digital 12
*									   SCK = Digital 13
*
*									ARDUINO MEGA PINOUT:
*									   MOSI = Digital 51
*									   MISO = Digital 50
*									   SCK = Digital 52
*			
*
*	The SD class has a setup that will start the SD. If the SD setup returns a zero
*	we are in a bad spot cause we cant detect the SD card.  
*
*	Write takes a String Data, This is ment to be an instance of the data class with its toString() 
*	function called. The year and month are important because that is how we are going to break up files
*	
*	The readToBluetooth should only be called by the Bluetooth function so i should probably make it private
*	then make the bluetooth and SDModule friends but I think it will be okay as long as people read this. 
*	The readToBluetooth takes all the data that is .TXT files and sends it to Serial2 which is what 
*	Bluetooth is hooked up to. 
*	DONT CALL IT UNLESS THE CLIENT DEVICE IS READY TO RECIEVE!
*	
*
*/




#ifndef SDMODULE_H_
#define SDMODULE_H_

#include <SPI.h>
#include <SD.h>		//probably change these to " " and have the files in the folder

class SDModule
{

public:
	SDModule(int port);
	~SDModule();
	SDModule(const SDModule & copy);
	int setup();
	int write(String data,int year,int month);
	void readToBluetooth();
	
private:
	int m_port;	//port num
};

#endif // ! SDMODULE_H_