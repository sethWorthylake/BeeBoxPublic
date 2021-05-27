//Seth Worthylake
#include <TimeInterrupt.h>
#include "Bluetooth_Control.h"
#include "Data.h"
#include "Sensor_Control.h"
#include "SDModule.h"
#include <stdlib.h>
#include <avr/interrupt.h> // interrupt vectors & misc
#include <avr/sleep.h>                  
#include <avr/io.h>
        
#define SD_pin 53
#define blueTxD_pin 18
#define blueRxD_pin 19
#define DemoBuild 0     // control variable if we are demmoing

const int testTime = 10;    //10 seconds 
const int Oneminute = 60;
const int Onehour = 1800;   // Number of seconds in an hour

int timeToWait = (DemoBuild == 1) ? Oneminute : Onehour;

const int interruptPin = 2; //Push button that will cause an iSnterupt
volatile int awakeState = 0; //When coming out of awake state we determine if we awoke because of button or timer2
unsigned int count = 0;   //used to keep count of how many interrupts were fired
unsigned int Seconds = 0; //keeps track of how many seconds have passed

SDModule SD_test(SD_pin);   //Global SD module
Bluetooth_Control Bluetooth_test(SD_test,blueTxD_pin,blueRxD_pin);	//Global Bluetooth Module
Sensor_Control Sensor_test;   // Global Sensor Control


//Timer2 Overflow Interrupt Vector,
ISR(TIMER2_OVF_vect) {  //is called every 2 ms
  count++;               //Increments the interrupt counter
  
  if(count > 499){
    count = 0;           //Resets the interrupt counter
    Seconds++;          //Increment the number of seconds a second 
    //Serial.println("Here");
    //Serial.flush();
  }

  if(Seconds > timeToWait - 1)  // 60 Seconds
  {
     Seconds = 0;
     awakeState = 1;
     detachInterrupt(digitalPinToInterrupt(interruptPin)); 
     TCCR2B = 0x00; // need to disable the timer interupt
     sleep_disable();
  }

  TCNT2 = 130;           //Reset Timer to 130 out of 255
  TIFR2 = 0x00;          //Timer2 INT Flag Reg: Clear Timer Overflow Flag
};

//This puts the syste into power saver mode. Then waits untill its awkoen by either timer2 or the button on pin2
void sleepNow()
{
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sleep_enable();
  
  attachInterrupt(digitalPinToInterrupt(interruptPin),WakeFromButton,LOW);
  TCCR2B = 0x05;

  while(awakeState == 0)  // Watch Dog timer will cause the CPU to come out of sleep mode. So we wait until this global is set 
  {
    sleep_cpu(); //sleep_mode(); //actually asleep
  }
  sleep_disable();  // make sure to turn off sleep mode
}

void WakeFromButton()
{
  sleep_disable();
  awakeState = 2; // set the awake state
  detachInterrupt(digitalPinToInterrupt(interruptPin)); //disable the push button interupt 
  TCCR2B = 0x00; // need to disable the timer interupt
}

void setup()
{
    Serial.begin(9600);   // Start Serial 
    Serial.println("Entering Setup");
    if(DemoBuild)
      Serial.println("In DemoBuild");
    else
      Serial.println("Not in DemoBuild");
      
    Serial.flush();

    pinMode(interruptPin, INPUT_PULLUP);  // Pushbutton on pin 2
    pinMode(8,OUTPUT);    //The red and green led
    pinMode(9,OUTPUT);    //The red and green led

    Sensor_test.setup();  
    Bluetooth_test.Setup();
    //Serial.println("Test1");
    //Serial.flush();
    Bluetooth_test.turnOn();
    //Serial.println("Test2");
    //Serial.flush();
    if(!SD_test.setup())
      Serial.println("SD NOT CORRECT"); //If we boot into this state very dangerous
    //Serial.println("Test3");
    //Serial.flush();
  
    //Setup Timer2 to fire every 2ms
    TCCR2B = 0x00;        //Disbale Timer2 while we set it up                 //DISABLE
    TCNT2  = 130;         //Reset Timer Count to 130 out of 255
    TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
    TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
    //TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128      // ENABLE
    Serial.println("END Setup");
    Serial.flush();
    //Serial.println("END Setu2p");
}

void loop()
{    
  RTC_DS3231 RealTimeClock; // Real time clock that keeps track of how long we will be in sleep mode
  RealTimeClock.begin();    
  
	Serial.println("Entering While Loop ");
  while(1)
  {
    #if DemoBuild == 1
      char buf1[] = "hh:mm:ss";
      char buf2[] = "hh:mm:ss";   //output buffers for the real time clocks
      DateTime Now = RealTimeClock.now();
      Serial.println("Entering Low Power Mode");
      Serial.flush();
    #endif
    
    sleepNow();   //Sleep in this function. Till timer2 ISR happens or button 2 is pressed 
    
    #if DemoBuild == 1
      DateTime Then = RealTimeClock.now();
      Serial.write("Entered Low Power at Time : ");
      Serial.println(Now.toString(buf1));
      Serial.write("Excited Low Power at Time : ");
      Serial.println(Then.toString(buf2));      // Output how long it was asleep
    #endif

    if(awakeState == 1)
    {
      if(DemoBuild == 1)
      {
        Serial.println("Awake Because of Timer: Reading Data and Writing To SD Card");
      }
      digitalWrite(8,1);
      Data temp(Sensor_test.Collect_Data());      // Read the sensors 
      SD_test.write(temp);  //Maybe print out data
      #if DemoBuild == 1
        Serial.println("--DATE---TIME--iTemp---oTemp---Hum-----Weight");
        Serial.println(temp.toString());
        Serial.flush();
      #endif
      
      digitalWrite(8,0);  //turn LED OFF
    }
    else if(awakeState == 2)
    {
      digitalWrite(9,1);  // turn the green LED ON
      #if DemoBuild == 1
        Serial.println("Awake Because of Button : Connecting to Bluetooth");
        Serial.flush();
      #endif
      
      int passed = Bluetooth_test.readyToSend();
      if(passed == 0)
        Serial.println("Bluetooth Failed To Send");       
      else
        Serial.println("Bluetooth Sent");       

      Serial.flush();
      digitalWrite(9,0);  // turn the green LED Off
    }
    else
    {
      Serial.println("Awake State 0 An error has occured");   // This state should not be reachable
      Serial.flush();
    }
    awakeState = 0;
    Serial.println("**********************************");
    Serial.flush();
    }
}
