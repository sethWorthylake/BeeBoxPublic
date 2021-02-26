#pragma once
#include "RTClib.h"	//Uses RTC library
					// A big idea is that no other class has to have the RTClib library to use this class 
class Data
{
public:
	float m_internal_temp;
	float m_external_temp;
	float m_humidity;
	float m_weight;
	DateTime m_time;
 

private:
	static RTC_DS3231 m_rtc;
	static int m_connection;  

public:
	Data();	
	~Data();
	Data(float internal_temp, float external_temp, float humidity, float weight);
	Data(float internal_temp, float external_temp, float humidity, float weight, DateTime m_time); 
	Data(const Data & copy);	//Copy CTOR
	void updateTime();	//Updates the Data Objects m_time to the current date+time
	int getYear();	
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();

};
