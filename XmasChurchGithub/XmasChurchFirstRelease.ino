//20.11.21

//Known Bugs:
//FX LED logic is a bit random currently. 
//TLC.write causes slight audio distortion. Most noticeable when writing multiple times per second. Predominantly a hardware issue.


#include <Adafruit_TLC59711.h>

#include "Adafruit_TLC59711.h"
#include <SPI.h>

#include "SD.h"
#define SD_ChipSelectPin 3
#include "TMRpcm.h"
#include "SPI.h"

TMRpcm tmrpcm;

// How many boards do you have chained?
#define NUM_TLC59711 1
// SPI Pins for TLC59711
#define data   7
#define clock  6

#define switchStatic 4
#define switchParty 5
#define switchStatusOn 0
#define switchStatusOff 1

#define levelFull 16383
//65535

//---------------------------LED level variables-------------------------------------------//
//Led current On/Off states
bool red0 = false;
bool green0 = false;
bool blue0 = false;
bool yellow0 = false;
bool red1 = false;
bool green1 = false;
bool blue1 = false;
bool yellow1 = false;
bool fx0 = false;       //Sign
bool fx1 = false;       //Door
bool fx2 = false;       //Main
bool fx3 = false;       //Spire

uint16_t red0Level = 0;
uint16_t green0Level = 0;
uint16_t blue0Level = 0;
uint16_t yellow0Level = 0;
uint16_t red1Level = 0;
uint16_t green1Level = 0;
uint16_t blue1Level = 0;
uint16_t yellow1Level = 0;
uint16_t fx0Level = 0;
uint16_t fx1Level = 0;
uint16_t fx2Level = 0;
uint16_t fx3Level = 0;

//---------------------------LX Chase variables-------------------------------------------//
uint16_t lxDelay = 500;                      //Delay between steps of a chase
uint8_t noOfTotalSteps = 0;                 //Total number of steps in a given chase
int8_t stepNo = 0;                          //Current step in a chase
unsigned long timeAtLastLxStep = 0;         //Time that last step began
byte currentLightshowChar = 0;              //LX chase pointer
bool lxCooldown = false;                    //Turn lights on or off during event cooldowns
bool build = false;                         //Indicates whether LX chase is individual or builds
bool forward = true;                        //LX chase direction. Reversed when false
byte randomVsHoldPercentage = 60;          //This percentage decides how likely a random lx chase will happen vs static colours in between choir songs

//---------------------------Event variables-------------------------------------------//
//An event is period of time where sound (tmrpcm) and lights (tlc59711) coordinate together
bool event = false;

unsigned long timeNow = 0;                    //Track current loop time
unsigned long timeAtLastEventStart = 0;       //Track time that last event started
unsigned long timeAtLastEventEnd = 0;         //Track time that last event ended
uint16_t eventInterval = 60000;               //Interval between events
//uint16_t eventDuration = 100;               //Duration of events (not used)
uint16_t eventCooldownDuration = 16;           //Cooldown after event finishes
bool eventCooldown = false;                   //Indicates that a cooldown is needed
bool eventPause = true;                       //Is the event currently in a paused-state?
uint8_t eventsBeforeNextBell = 3;             //Number of events that can happen before the next bell ring
boolean pauseLightShowManager = false;        //Pause for uninterupted music playback

bool switchStaticState;                       //Logs current state of "lights" switch
bool switchStaticFirstActivate = true;        //Tracks if this was switched on current loop()
bool switchPartyState;                        //Logs current state of "party" switch
bool switchPartyFirstActivate = true;         //Tracks if this was switched on current loop()

boolean continuousLxMode = false;             //Is Party Mode activated? Doubling up on variables here but used by event manager
unsigned long timeAtLastPartyLx = 0;         //Track time that last LX chase changed for party mode

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

void initVariables(){
    lxCooldown = false;
    event = false;
    timeAtLastEventStart = timeNow;
    timeAtLastEventEnd = 0;
    eventInterval = 60000;
    eventCooldownDuration = 16;
    eventCooldown = false;
    eventPause = true;
    eventsBeforeNextBell = 3;
    timeAtLastPartyLx = 0;
    tmrpcm.stopPlayback();
  }

void setup() {
  Serial.begin(9600);
  Serial.println(F("Initilising serial connection."));
  pinMode(switchStatic, INPUT_PULLUP);
  pinMode(switchParty, INPUT_PULLUP);
  tmrpcm.speakerPin = 9;
  if (!SD.begin(SD_ChipSelectPin)) {
      Serial.println(F("SD fail"));
      return;
    }
      tmrpcm.setVolume(4);
      Serial.print(F("SD card & speaker test - "));
      tmrpcm.play("b1.wav");
      while (tmrpcm.isPlaying()){
        //Wait until test sound is complete
        }
      Serial.println(F("Complete."));  
  tlc.begin();  //Init LED driver
  tlc.write();
  Serial.print(F("TLC59711 test - "));
  tlcFlashOut();
  Serial.println(F("Complete."));
  Serial.println(F("Checking Inputs."));
  //--------------------------------------Lazy Programming - Initial LX select
   byte randomNumber = getRandomNumber(100);
                  if (randomNumber < randomVsHoldPercentage){
                     chooseLightshow('r');
                  } else {
                     chooseLightshow('h');
                    }
       chooseFxLightingState('n');
//--------------------------------------------------------------------                    
  checkInputs();
  Serial.println(F("System Ready."));
}

void loop() {

 //Serial.println(currentLightshowChar);
// Serial.println(pauseLightShowManager);
 

  timeNow = millis();   //Start each loop by getting the current time
  checkInputs();

       if(event){
        checkEventStatus();  
      } else {
        checkForEvents();
      }     
      lightshowManager();
      

  delay(250); //Used to manually slow down speed of code
}


void checkInputs(){
  switchStaticState = digitalRead(switchStatic);
  switchPartyState = digitalRead(switchParty);

                                                                                //--------------STATIC MODE LOGIC
  if (switchStaticState == switchStatusOn){                           //If On
    if (switchStaticFirstActivate == true){                           //First time?
      //Do Thing once                                                 //Yes, inital press
      allLedSet(true);
      updateLeds();
      pauseLightShowManager = true;  
    }
    switchStaticFirstActivate = false;                                //No longer initial press
  } else if (switchStaticState == switchStatusOff){                   //if set to Off
    if (switchStaticFirstActivate == false){                          //First time?
      pauseLightShowManager = false;                                  //Yes, initial press      
    }
    switchStaticFirstActivate = true;                                 //No longer initial press
  }

                                                                                //--------------STATIC MODE LOGIC

                                                                                //--------------PARTY MODE LOGIC
if (switchPartyState == switchStatusOn){                              //If set to on
    if (switchPartyFirstActivate == true){                            //First time?
         continuousLxMode = true;           //Enable Static LX        //Yes, initial press
         pauseLightShowManager = false;
         initVariables();
      //Do Thing once      
    }
    switchPartyFirstActivate = false; //No longer initial press    
  } else if (switchPartyState == switchStatusOff){                    //If set to off
    if (switchPartyFirstActivate == false){                           //First time?
         continuousLxMode = false;  
                                          //Disable Static LX         //Yes, initial press
          initVariables();
          pauseLightShowManager = false;    
      //Do thing once
      }
    switchPartyFirstActivate = true;                                  //No longer initial press
    }                                                                                //--------------PARTY MODE LOGIC
} 


  
  
