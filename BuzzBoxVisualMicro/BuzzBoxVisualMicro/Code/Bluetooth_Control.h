#pragma once
#include "BluetoothModule.h"
class Bluetooth_Control
{
private:
	BluetoothModule m_bluetooth_module;

public:
	Bluetooth_Control();
	~Bluetooth_Control();
	void Pair_Device();
	void Transmit_Data();
};

