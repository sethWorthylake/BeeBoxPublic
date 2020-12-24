#include "Data.h"

Data::Data()
{
	m_internal_temp = 0.0;
	m_external_temp = 0.0;
	m_humidity = 0.0;
	m_weight = 0.0;
	//m_date = system date
	//m_time = system time

}

Data::Data(float internal_temp, float external_temp, float humidity, float weight)
{
	m_internal_temp = internal_temp;
	m_external_temp = external_temp;
	m_humidity = humidity;
	m_weight = weight;
	//m_date = system date
	//m_time = system time
}

Date Data::getDate()
{
	return Date();
}

Time Data::getTime()
{
	return Time();
}
