#pragma once
#include "TemperatureModule.h"
#include "humidity.h"
#include "Weight_Driver.h"
#include "Data.h"


#define inTemp_pin 4
#define exTemp_pin 5
#define hum_pin 6
#define weight_pin_dout 10
#define weight_pin_clk 11

class Sensor_Control
{
private:
	TemperatureModule m_internal_temp_module;
	TemperatureModule m_external_temp_module;
	humidity m_humidity_module;
	Weight_Driver m_weight_module;

public:
	
	Sensor_Control();
	void setup();
	Data Collect_Data();
};
