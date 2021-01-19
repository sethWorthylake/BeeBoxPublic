#pragma once
#include "SDModule.h"
#include "Data.h"

class Data_Storage
{
private:
	SDModule m_SD_module;
	Data* m_current_array;
	Data** m_storage;

public:
	Data_Storage();
	~Data_Storage();
	void Store_Data(Data data);
	Data* getCurrent_Array();
	Data* getArray(int location);
};

