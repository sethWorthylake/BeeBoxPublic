#include "Data.h"

int Data::m_connection = 0; // Have to do this for static var

Data::Data(): m_internal_temp(0.0),m_external_temp(0.0),m_humidity(0.0),m_weight(0.0)
{
	if(m_connection != 1)	//if no data object has started the connection to the RTC do it
	{
		m_rtc.begin();
		m_connection = 1;	// then dont let it happen again
	}
	m_time = m_rtc.now();	//getting current time
}

Data::~Data()
{
}

Data::Data(float internal_temp, float external_temp, float humidity, float weight): m_internal_temp(internal_temp),m_external_temp(external_temp),m_humidity(humidity),m_weight(weight)
{
	if(m_connection != 1)	//if no data object has started the connection to the RTC do it
	{
		m_rtc.begin();
		m_connection = 1;	// then dont let it happen again
	}
	m_time = m_rtc.now(); //getting current time
}

Data::Data(float internal_temp, float external_temp, float humidity, float weight, DateTime time)
: m_internal_temp(internal_temp),m_external_temp(external_temp),m_humidity(humidity),m_weight(weight),m_time(time)
{
	if(m_connection == 0)	//if no data object has started the connection to the RTC do it
	{
		m_rtc.begin();
		m_connection = 1;	// then dont let it happen again
	}
	m_time = m_rtc.now(); //getting current time
}

Data::Data(const Data & copy)
 : m_external_temp(copy.m_external_temp),m_humidity(copy.m_humidity),
   m_internal_temp(copy.m_internal_temp),m_weight(copy.m_weight),m_time(copy.m_time)
{ }

void Data::updateTime()
{
	m_time = m_rtc.now();
}

int Data::getYear()
{
	return m_time.year();
}

int Data::getMonth()
{
	return m_time.month();
}

int Data::getDay()
{
	return m_time.day();
}

int Data::getHour()
{
	return m_time.hour();
}

int Data::getMinute()
{
	return m_time.minute();
}

String Data::toString()
{

	int width = 4;
	int precision = 4;	
	char buff[15];
	String string2Send = "";
	float data[4] = {m_internal_temp,m_external_temp,m_humidity,m_weight};
	int time[5] = {m_time.month(),m_time.day(),m_time.year(),m_time.hour(),m_time.minute()}; 

	for(int ii =0; ii < 5;ii++)
	{
		string2Send += String(time[ii]);
		
		if(ii < 2)
			string2Send += '/';
		else if(ii == 2)
			string2Send += ' ';
		else if(ii == 3)
			string2Send += ':';
		else if(ii == 4)
			string2Send += ',';
	}	
	
	for(int ii =0; ii < 4;ii++)
	{
		dtostrf(data[ii], width, precision, buff); // these are floats so they need more precision
		string2Send += buff;
		
		if(ii != 3)
			string2Send += ',';
	
		for(int ff = 0; ff < 15;ff++)
		{
			buff[ff] = 0;
		}
	}
	
	return string2Send;
}
