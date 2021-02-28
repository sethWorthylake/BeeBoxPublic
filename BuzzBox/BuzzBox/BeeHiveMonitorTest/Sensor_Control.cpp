#include "Sensor_Control.h"


Sensor_Control::Sensor_Control():
m_internal_temp_module(inTemp_pin), m_external_temp_module(exTemp_pin)
, m_humidity_module(hum_pin),m_weight_module(weight_pin) 
{ }

void Sensor_Control::setup()
{
	//No tempurature setup function YET
    m_humidity_module.begin();
	//Weight setup function ?
}


Data Sensor_Control::Collect_Data()
{
	return Data(m_internal_temp_module.collectTemp(),m_external_temp_module.collectTemp(),m_humidity_module.get_humidity(),m_weight_module.Get_Data()); 
}
