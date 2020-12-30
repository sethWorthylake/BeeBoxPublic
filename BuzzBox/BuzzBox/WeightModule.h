/******************************************************************************************
*	Author: Killian Laws
*	Date: 12/17/2020
*	Edited: 12/29/2020
*
*	Title: Weight Module Header
*
*	Description: Pulls converted weight measurement from HX711, attached to full bridge.
*
********************************************************************************************/
#ifndef WEIGHTMODULE_H_
#define WEIGHTMODULE_H_



class WeightModule
{

public:
	WeightModule();
	WeightModule(int clk_port, int data_port);
	void SetPortClock(int port_num);
	void SetPortData(int port_num);
	void Reset();
	void Measure();
	float Get_Data();

private:
	//variables
	float m_weight;

	//methods
	void SetRate();
	void Reset();
	void StartClock();
	bool Ready();
};

#endif // !_WEIGHTMODULE_

