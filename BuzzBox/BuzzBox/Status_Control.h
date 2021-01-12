#pragma once

struct Status {
	int flag;
};

class Status_Control
{
private:
	Status m_status_flags;

public:
	Status_Control();
	~Status_Control();
	Status Status_Report();

private:
	void Check_Status();
};

