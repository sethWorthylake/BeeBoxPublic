#pragma once
#include "TemperatureModule.h"
#include "HumidityModule.h"
#include "WeightModule.h"
#include "Data.h"

class Sensor_Control
{
private:
	TemperatureModule m_external_temp_module;
	TemperatureModule m_internal_temp_module;
	HumidityModule m_humidity_module;
	WeightModule m_weight_module;

public:
	Sensor_Control();
	void Collect_Data(Data & data);

private:
	float Collect_External_Temp();
	float Collect_Internal_Temp();
	float Collect_Humidity();
	float Collect_Weight();
};

