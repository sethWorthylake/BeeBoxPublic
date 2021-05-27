/*
*  Author: Killian Laws
* Date: 02/13/2021
*
* Modified Heavily By Seth Worthylake
*
*
*/

#pragma once
#include "HX711.h"

const float baseWeight = 1.463;

class Weight_Driver
{
  public:
    Weight_Driver(int dout,int clk);
    ~Weight_Driver();
    float GetWeight();
    void WeightSetup();
  
  private:
    HX711 weightModule;
    float m_weight;
    int m_dout;
    int m_clk;
    float calibration_factor; //gets from EEPROM
    
    
};
