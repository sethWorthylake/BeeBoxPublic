#pragma once

struct Date {
	int day;
	int month;
	int year;
};

struct Time {
	int hour;
	int minute;
};

class Data
{
public:
	float m_internal_temp;
	float m_external_temp;
	float m_humidity;
	float m_weight;

private:
	Date m_date;
	Time m_time;

public:
	Data();
	~Data();
	Data(float internal_temp, float external_temp, float humidity, float weight);
	Date getDate();
	Time getTime();
};

