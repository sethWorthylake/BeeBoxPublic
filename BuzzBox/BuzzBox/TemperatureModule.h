#pragma once
#include "DS18B20.h"

class TemperatureModule
{
private:
	DS18B20 m_tempSensor;

public:
	TemperatureModule(int port);
	float collectTemp();
};