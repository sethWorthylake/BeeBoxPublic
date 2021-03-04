/*
*	Author: Killian Laws
*	Date: 02/13/2021
*
*
*
*
*/

#include "Weight_Driver.h"

//NOTE: Calibration factor must be set up for kilograms
Weight_Driver::Weight_Driver(int dout, int clk) : m_weight(0.0),m_dout(dout),m_clk(clk),weightModule(dout,clk)
{
	//WeightSetup();
}

Weight_Driver::~Weight_Driver()
{
	
}

void Weight_Driver::WeightSetup()
{
	  weightModule.begin();
  unsigned long stabilizingtime = 2000; // preciscion right after power-up can be improved by adding a few seconds of stabilizing time
  weightModule.start(stabilizingtime, true);  // true says to do a tare
  if (weightModule.getTareTimeoutFlag()) 
  {
    Serial.println("Check Weight Pin Connection");
  }
  else  
    weightModule.setCalFactor(calibration_factor);            //Reset weight to 0
}

float Weight_Driver::GetWeight()
{
  while(!weightModule.update());
  //weightModule.update();
  
	m_weight = weightModule.getData();
  if(m_weight < 0)
      m_weight = 0;
    
	return m_weight;
}
