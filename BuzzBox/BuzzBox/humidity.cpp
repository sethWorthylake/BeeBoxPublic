//Author: Braedon
//Class: humidity
//MUST DOWNLOAD DHT Sensor Library

#include "humidity.h"

humidity::humidity(int port) : m_dht(DHT(port, DHT11))
{ }

humidity::humidity(const humidity& copy) : m_dht(copy.m_dht)
{ }

humidity& humidity::operator=(const humidity& LHS)
{
	if (this != &LHS)
	{
		m_dht = DHT(LHS.m_dht);
	}
	return *this;	// is this correct?
}

humidity::~humidity()
{
}

void humidity::begin()
{
	m_dht.begin();
}

float humidity::get_humidity()
{
	return m_dht.readHumidity();
}