#include "Status_Control.h"

Status_Control::Status_Control()
{
}

Status_Control::~Status_Control()
{
}

Status Status_Control::Status_Report()
{
	Check_Status();
	return m_status_flags;
}

void Status_Control::Check_Status()
{
}
