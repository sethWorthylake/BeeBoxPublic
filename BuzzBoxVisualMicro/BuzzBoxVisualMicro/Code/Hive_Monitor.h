#pragma once
#include "Sensor_Control.h"
#include "Status_Control.h"
#include "Bluetooth_Control.h"

class Hive_Monitor
{
private:
	Data m_current_data;
	Sensor_Control m_sensor_control;
	Status m_current_status;
	Status_Control m_status_control;
	Bluetooth_Control m_bluetooth_control;


public:
	Hive_Monitor();
	~Hive_Monitor();
	void Collect_Data();
	Status Get_Current_Status();
};

