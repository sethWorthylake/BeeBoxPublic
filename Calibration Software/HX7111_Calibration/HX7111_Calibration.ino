/*
 * https://circuits4you.com
 * 2016 November 25
 * Load Cell HX711 Module Interface with Arduino to measure weight in Kgs
 Arduino 
 pin 
 2 -> HX711 CLK
 3 -> DOUT
 5V -> VCC
 GND -> GND

 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
*/
#include <EEPROM.h>
#include "HX711.h"  //You must have this library in your arduino library folder

#define DOUT  10
#define CLK  11

bool getFloat( float* f );

HX711 scale;

//Change this calibration factor as per your load cell once it is found you many need to vary it in thousands
float calibration_factor = -2000; //-27221 worked
float known = 0.0;
float red = 1.0;
int lock = 0;


//=============================================================================================
//                         SETUP
//=============================================================================================
void setup() {
  Serial.begin(9600);
  EEPROM.get(0,calibration_factor);
  if(calibration_factor >= 0)
    calibration_factor = -2000;
  Serial.println("HX711 Calibration");
  Serial.print("Last Calibration Factor was ");
  Serial.println(calibration_factor,5);
  Serial.println("Remove all weight from scale, this will be the zero for the system");
  Serial.println("Once All weight has been removed enter the 'x' character");
  char temp = 'o';
  while(temp != 'x')
  {
      temp = Serial.read();
  }
  scale.begin(DOUT, CLK);
  scale.set_scale();
  scale.tare(); //Reset the scale to 0

  Serial.println("Now place an object of known weight ontop the monitor");
  Serial.println("What is the weight of that object in kg. Enter without units EX 1.360");
   bool locked = true;
   while(locked)
   {
      locked = !getFloat(&known);
      if(known == 0)
        locked = true; 
   }
  Serial.println(known,5);
  Serial.println("Now Calibrating");
  
  long zero_factor = scale.read_average(); // used to flush the sensor ? also maybe look into zero_factor

  int count = 0;  
  
  while(known != red && count < 10)
  {
     count++;
     scale.set_scale(calibration_factor); //Adjust to this calibration factor
     red = scale.get_units(10);
     Serial.println(red,5);
     float difference = red / known;
     calibration_factor = calibration_factor * difference;
     
  }
     Serial.print("Reading: ");
     Serial.print(red, 5);
     Serial.println(" kg"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
     Serial.print(calibration_factor,5);
     Serial.println(" calibration_factor");

     EEPROM.put(0,calibration_factor);

}

//=============================================================================================
//                         LOOP
//=============================================================================================
void loop() {

  if(lock == 0)
  {
    Serial.println("System Calibrated");
    lock++;  
  }
  Serial.println(scale.get_units(10),5);
  
}
//=============================================================================================
bool getFloat( float* f )
{
    int f1=0 ;
    int f2=0 ;
    int mul=1 ;
    bool gotdp=false;
    bool gotminus=false ;
    while ( true )
    {
        if ( Serial.available() > 0 )
        {
            int c = Serial.read() ;
            if ( c >='0' && c<='9' )
            {
                  if ( gotdp ) 
                  {
                        f2=(10*f2)+(c-'0');
                        mul*=10 ;
                  }
                  else           f1=(10*f1)+(c-'0');
            }
            else if ( c == '.' )  gotdp=true ;
            else if ( c == '-')   gotminus=true ;
            else if ( c == '\r' || c=='\n' )
             {
                   float res = ( float ) f1 ;
                   if ( f2 != 0 )  res += ((float)f2)/((float)mul) ;
                   if ( gotminus ) res=-res ;
                   *f = res ;
                    return true ;
             }
             else
             { 
                  // ignore anything else
             }
         }

    }

}
