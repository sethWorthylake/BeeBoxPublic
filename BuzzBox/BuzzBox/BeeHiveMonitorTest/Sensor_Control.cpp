#include "Sensor_Control.h"

Sensor_Control::Sensor_Control():
m_internal_temp_module(inTemp_pin), m_external_temp_module(exTemp_pin)
, m_humidity_module(hum_pin),m_weight_module(weight_pin_dout,weight_pin_clk) 
{ }

void Sensor_Control::setup()
{
  
	//No tempurature setup function YET
  m_humidity_module.begin();
  m_weight_module.WeightSetup();
	//Weight setup function ?
}


Data Sensor_Control::Collect_Data()
{
    for(int ii = 0; ii < 10; ii++)
    {
        m_weight_module.GetWeight();
    }
  
  float weight = m_weight_module.GetWeight();
  
	return Data(m_internal_temp_module.collectTemp(),m_external_temp_module.collectTemp(),m_humidity_module.get_humidity(),weight); 
}
