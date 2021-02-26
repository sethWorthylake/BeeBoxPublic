#include "Data.h"

int Data::m_connection = 0; // Have to do this for static var

Data::Data(): m_internal_temp(0.0),m_external_temp(0.0),m_humidity(0.0),m_weight(0.0)
{
	if(m_connection == 0)	//if no data object has started the connection to the RTC do it
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
	if(m_connection == 0)	//if no data object has started the connection to the RTC do it
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
