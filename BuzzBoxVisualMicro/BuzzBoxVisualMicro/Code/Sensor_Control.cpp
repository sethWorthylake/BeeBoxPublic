#include "Sensor_Control.h"

Sensor_Control::Sensor_Control()
{
}

void Sensor_Control::Collect_Data(Data & data)
{
	data.m_external_temp = Collect_External_Temp();
	data.m_internal_temp = Collect_Internal_Temp();
	data.m_humidity = Collect_Humidity();
	data.m_weight = Collect_Weight();
}

float Sensor_Control::Collect_External_Temp()
{
	return 0.0f;
}

float Sensor_Control::Collect_Internal_Temp()
{
	return 0.0f;
}

float Sensor_Control::Collect_Humidity()
{
	return 0.0f;
}

float Sensor_Control::Collect_Weight()
{
	return 0.0f;
}
