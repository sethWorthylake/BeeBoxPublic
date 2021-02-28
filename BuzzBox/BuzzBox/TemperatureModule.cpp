#include "TemperatureModule.h"

TemperatureModule::TemperatureModule(int port) : m_tempSensor(port)
{
}

float TemperatureModule::collectTemp()
{
	return m_tempSensor.getTempC();
}
