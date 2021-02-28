#pragma once
#include <TimeInterrupt.h>
#include "Data.h"
#include "SDModule.h"

#define MINUTE 60000	// Minute defintion for how long to wait

static int stop; // interupt change this global which will let the bluetooth know to stop listening
void setStop();	//Function that interupt calls to change global to a one
void clearStop(); // function to set global to zero

class Bluetooth_Control
{
private:
	SDModule & m_SDModule;	// reff to the SD module
	int m_TxD;	//the Transmit port
	int m_RxD;	// the Recieve port 
public:

	Bluetooth_Control(SDModule & sdRef,int TxD, int RxD);	//Ctor	Only one should exist at a time
	
	~Bluetooth_Control();	// Dtor
	void Setup();	// Call during setup 
	void turnOn();	//turns it on               actually just enables the Serial  
	void turnOff();	//turns it off				just disables the Serial. Not worth doing
	int available();	// Is there anything on the serial line from bluetooth
	int readyToSend();	// Call this when we are ready to send cause the Bluetooth button got presed
						// IT WILL WAIT FOR 5 MINUTES WHILE IN THIS FUNCTION!!!
	
};
