/*
*  Author: Killian Laws
* Date: 02/13/2021
*
* Modified Heavily By Seth Worthylake
*
*
*/

#include "Weight_Driver.h"
#include <EEPROM.h>


//NOTE: Calibration factor must be set up for kilograms
Weight_Driver::Weight_Driver(int dout, int clk) : m_weight(0.0),m_dout(dout),m_clk(clk),weightModule(),calibration_factor(0)
{
  weightModule.begin(dout, clk);
  //weightModule.set_scale();
  //weightModule.read_average();
}

Weight_Driver::~Weight_Driver()
{
  
}

void Weight_Driver::WeightSetup()
{
  
  EEPROM.get(0,calibration_factor );  //reads the EEPROM for the Calibration factor
  
  //if(calibration_factor == 0)
  //  Serial.println("ITS ZERO");
  //else
  //  Serial.println(calibration_factor,5);   //take out
  
  weightModule.set_scale(calibration_factor);            //Sets the calibration factor
}

float Weight_Driver::GetWeight()
{
  m_weight = weightModule.get_units(10) - baseWeight;
  if(m_weight < 0)
      m_weight = 0;
    
  return m_weight;
}
