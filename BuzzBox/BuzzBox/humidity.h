//Author: Braedon
//humidity.h
//MUST DOWNLOAD DHT Sensor Library
//m_dht: The DHT object.
//void begin: Used to start the DHT module.
//void get_humidity: Used for getting the humidity value from the sensor.

#include "DHT.h"

#ifndef _HUMIDITY_h
#define _HUMIDITY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class humidity
{
public:
	humidity(int port);
	humidity(const humidity& copy);
	humidity& operator=(const humidity& LHS);
	~humidity();

	void begin();
	float get_humidity();
private:
	DHT m_dht;
};

#endif