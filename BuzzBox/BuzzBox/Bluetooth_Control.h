#pragma once
#include <TimeInterrupt.h>
#include "Data.h"

#define TxD 18
#define RxD 19	//maybe need to take out to larger project

static int stop; // interupt change this global which will let the bluetooth know to stop listening
void setStop();	//Function that interupt calls to change global to a one
void clearStop(); // function to set global to zero

class Bluetooth_Control
{
private:
	
public:

	Bluetooth_Control();	//Ctor	Only one should exist at a time
	~Bluetooth_Control();	// Dtor
	void Setup();	// Call during setup 
	void turnOn();	//turns it on 
	void turnOff();	//turns it off
			// Need to add function that iterates through the Data_Container and sends each instance of data in it
	int readyToSend(Data info);	// Will wait for the code, then send the data	
	void sending(Data info); //Actually sending the data
	int available();	// Is there anything on the serial line from bluetooth
	
	
};
