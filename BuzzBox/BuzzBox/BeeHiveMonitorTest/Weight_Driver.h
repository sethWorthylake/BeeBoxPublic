/*
*	Author: Killian Laws
*	Date: 02/13/2021
*
*
*
*
*/

#pragma once
#include "HX711_ADC.h"

//Pin Allocation: Permanent
//		Test for calibration factor using calibration program. 
//		Update calibration once installed on desired base.
const float calibration_factor = -19.96; //**CHANGE THIS: -7050.0*** 

//NOTE ON CALLIBRATION FACTOR:
//		This factor has changed many times since I attached our
//		module to the board, ranging from 160-250. If output looks
//		absurd, start by changing this value. Even if output is great
//		this value MUST be changed after installation. No way around it.


class Weight_Driver
{
	public:
		Weight_Driver(int dout,int clk);
		~Weight_Driver();
		float GetWeight();
		void WeightSetup();
	
	private:
		HX711_ADC weightModule;
		float m_weight;
		int m_dout;
		int m_clk;
		
		
};
