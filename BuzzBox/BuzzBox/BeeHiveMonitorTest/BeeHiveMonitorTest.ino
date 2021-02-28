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
const int Oneminute = 30;
const int Onehour = 1800;
const int interruptPin = 2;
volatile int awakeState = 0;
unsigned int toggle = 0;  //used to keep the state of the LED
unsigned int toggle2 = 0; 
unsigned int count = 0;   //used to keep count of how many interrupts were fired
unsigned int Seconds = 0;

SDModule SD_test(SD_pin);   //Global SD module
Bluetooth_Control Bluetooth_test(SD_test,blueTxD_pin,blueRxD_pin);	//Global Bluetooth Module
Sensor_Control Sensor_test;   // Global Sensor Control


//Timer2 Overflow Interrupt Vector, called every 1ms
ISR(TIMER2_OVF_vect) {
  count++;               //Increments the interrupt counter
  if(count > 999){
    count = 0;           //Resets the interrupt counter
    Seconds++;          //Its a second
  }

  if(Seconds > Oneminute - 1)  // 60 Seconds
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

void sleepNow()
{
	set_sleep_mode(SLEEP_MODE_PWR_SAVE);
	sleep_enable();
  
  attachInterrupt(digitalPinToInterrupt(interruptPin),WakeFromButton,LOW);
  TCCR2B = 0x05;

  while(awakeState == 0)
  {
    sleep_cpu(); //sleep_mode(); //actually asleep
  }
  sleep_disable();
}

void WakeFromButton()
{
  sleep_disable();
  awakeState = 2;
  detachInterrupt(digitalPinToInterrupt(interruptPin)); 
  TCCR2B = 0x00; // need to disable the timer interupt
}

void setup()
{
    Serial.begin(9600);
    pinMode(interruptPin, INPUT_PULLUP);
    pinMode(8,OUTPUT);
    pinMode(9,OUTPUT);
    Sensor_test.setup();
    Bluetooth_test.Setup();
    Bluetooth_test.turnOn();
    if(!SD_test.setup())
      Serial.println("SD NOT CORRECT"); 

  
    //Setup Timer2 to fire every 1ms
    TCCR2B = 0x00;        //Disbale Timer2 while we set it up                 //DISABLE
    TCNT2  = 130;         //Reset Timer Count to 130 out of 255
    TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
    TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
    TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
    //TCCR2B = 0x05;        //Timer2 Control Reg B: Timer Prescaler set to 128      // ENABLE
    Serial.println("END Setup");
}

void loop()
{    
	//if(SD_test.write(Sensor_test.Collect_Data()))
	//	Serial.println("Sd Confirmed Send");

  RTC_DS3231 RealTimeClock;
  RealTimeClock.begin();
  
	Serial.println("Entering While Loop ");
  while(1)
  {
  char buf1[] = "hh:mm:ss";
  char buf2[] = "hh:mm:ss";
  DateTime Now = RealTimeClock.now();
  Serial.println("Entering Low Power Mode");
  Serial.flush();
  sleepNow();
  DateTime Then = RealTimeClock.now();
  Serial.write("Entered Low Power at Time : ");
  Serial.println(Now.toString(buf1));
  Serial.write("Excited Low Power at Time : ");
  Serial.println(Then.toString(buf2));
  if(awakeState == 1)
  {
      toggle = !toggle;
      digitalWrite(8,toggle);
      Serial.println("Awake Because of Timer: Reading Data and Writing To SD Card");
      
      Data temp(Sensor_test.Collect_Data());
      SD_test.write(temp);  //Maybe print out data
      Serial.println(temp.toString());
      Serial.flush();
  }
  else if(awakeState == 2)
  {
    toggle2 = !toggle2;
    digitalWrite(9,toggle2);
    Serial.println("Awake Because of Button : Connecting to Bluetooth");
    Serial.flush();

    int passed = Bluetooth_test.readyToSend();
    if(passed == 0)
      Serial.println("Bluetooth Failed To Send");       
    else
      Serial.println("Bluetooth Sent");       

    Serial.flush();
  }
  else
  {
    Serial.println("Awake State 0 An error has occured");
    Serial.flush();
  }
  awakeState = 0;
  Serial.println("**********************************");
  Serial.flush();
  }

     
 //
 //  Serial.println("Sd Confirmed Send");
}
