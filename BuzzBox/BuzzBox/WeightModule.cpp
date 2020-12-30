/******************************************************************************************
*	Author: Killian Laws
*	Date: 12/17/2020
*	Edited: 12/29/2020
*
*	Title: Weight Module Definitions
*
*	Description: 
*
********************************************************************************************/
#include "WeightModule.h"

//~~~~~~~ PUBLIC METHODS ~~~~~~~~~

//Default ports TBD
WeightModule::WeightModule()
{
	m_weight = 0.0;
	//m_clkprt = 0;
	//m_dataprt = 1;
	//m_baud = ???;
}

WeightModule::~WeightModule()
{}

//Default ports TBD
WeightModule::WeightModule(int clk_port = 0, int data_port = 1, int baud)
{
	m_weight = 0.0;
	//Update with correct port limitations
	/*if (clk_port >= 0 || clk_port < ? ? ? )
	{
		m_clkprt = clk_port;
	}

	if (data_port >= 1 || data_port < ? ? ? )
	{
		m_dataprt = data_port;
	}*/
}

WeightModule::WeightModule(WeightModule && copy) noexcept
{
	m_weight = copy.m_weight;
	m_clkprt = copy.m_clkprt;
	m_dataprt = copy.m_dataprt;
}

void WeightModule::SetPortClock(int port_num)
{
	//Consider enum for limited port declaration
	/*if (port_num >= 0 || port_num < ? ? ? )
	{
		m_clkprt = port_num;
	}*/
}

void WeightModule::SetPortData(int port_num)
{
	//enum? 
	/*if (port_num >= 1 || port_num < ? ? ? )
	{
		m_dataprt = port_num;
	}*/
}

void WeightModule::Reset()
{
	//if system is stalled
	//InternalReset();
}

void WeightModule::Measure()
{
	//STEPS:
	//	1. Verify baud rate
	//	2. Start the clock
}

//~~~~~~~ PRIVATE METHODS ~~~~~~~~~

void WeightModule::InternalReset()
{

}