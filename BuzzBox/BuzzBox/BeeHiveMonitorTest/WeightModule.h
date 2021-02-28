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
	//enum for clock & data ports? Maybe in body of program?
	//consider after determining port limitations

public:
	WeightModule(int port);
	~WeightModule();
	WeightModule(int clk_port, int data_port, int baud);
	WeightModule(WeightModule && copy) noexcept;
	void SetPortClock(int port_num);
	void SetPortData(int port_num);
	void Reset();
	void Measure();
	float Get_Data();

private:
	//variables
	float m_weight;
	int m_clkprt;
	int m_dataprt;
	int m_baud;

	//methods
	void SetRate();
	void InternalReset();
	void StartClock();
	bool Ready();
};

#endif // ! WEIGHTMODULE_H_
