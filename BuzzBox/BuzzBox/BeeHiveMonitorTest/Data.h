//Seth Worthylakes Version
#pragma once
#include "RTClib.h"	//Uses RTC library
// A big idea is that no other class has to have the RTClib library to use this class 

// Whenever a Data class is intancated (created) then it will be imeditly time stamped
// The only noteworthy function is the toString function that turns our Data class into 
// a string with this format
// MONTH/DAY/YEAR HOUR:MINUTE,INTERNAL_TEMP,EXTERNAL_TEMP,HUMIDITY,WEIGHT
// the floats are converted to strings with a precision of 4

// It has two static data members, static means only one will exist no matter how many Datas are created
// C initializes it to 0 and whenever a instance of data is created we check if its not 1.
// If its not it means we have not established a connection to the real time clock and we must.
// Data is nothing without the context of time.

class Data
{
public:
	float m_internal_temp;
	float m_external_temp;
	float m_humidity;
	float m_weight;
	DateTime m_time;
 
private:
	static RTC_DS3231 m_rtc;	// Real time clock data member 
	static int m_connection;  	// 1 if we have established a connection to the rtc

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
	String toString();
};
