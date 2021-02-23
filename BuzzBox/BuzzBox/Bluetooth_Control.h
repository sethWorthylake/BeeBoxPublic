#pragma once
#include <TimeInterrupt.h>
#include "Data.h"

#define TxD 18
#define RxD 19	//maybe need to take out to larger proj

static int stop; // interupt will tell bluetooth to stop listening
void setStop();
void clearStop();


class Bluetooth_Control
{
private:

public:

	Bluetooth_Control();
	~Bluetooth_Control();
	void Setup();
	void turnOn();
	void turnOff();
	int readyToSend(Data info);	// Will wait for the code, then send the data	
	void sending(Data info);
	int available();
	
	// Need to disable ISRs when calling this, then re enable after
	
};
