void checkForEvents(){                                              //Currently no event. Is it time to start one?
  if (timeNow >= timeAtLastEventEnd + eventInterval || switchPartyState == switchStatusOn ){  //If current time > last event + interval  OR Party Mode Activated  
      if (eventPause == true){                                    //pre-pause?
          pauseProcedure();
        } else {   
          event = true;                                          //Time to start a new event   
            timeAtLastEventStart  = timeNow;
             if (eventsBeforeNextBell == 0){
                playBell();
              } else {   
                 byte nextTrackSeed;
                 nextTrackSeed = getRandomNumber(23);   
                 playSound(switchPartyState, nextTrackSeed);
                 eventPause = true;                             //Post-pause required
                 eventCooldownDuration = 8;
                 lxCooldown = false;
                 if (switchPartyState == switchStatusOff){
                    eventsBeforeNextBell--;     
                 }
                 timeAtLastPartyLx = timeNow;     
                 if (continuousLxMode){
                                              //----------------------------------------Decide if LX will be random chase or a static colour
                  byte randomNumber = getRandomNumber(100);
                  if (randomNumber < randomVsHoldPercentage){
                       chooseLightshow('r');
                    } else {
                       chooseLightshow('h');
                    }
                    chooseFxLightingState('n');
                                              //----------------------------------------end random vs static decision
                  } else {      
                 chooseLightshow('s');                  
                  } //else
              }
          }
    }
    else {   
    //Serial.println("Not enough time elapsed.");        //Not enough time has passed to start an event
    } //else 
}     //void checkForEvents
        
 
 
void checkEventStatus(){                        //Event in progress. Is it time to start end?
  //Serial.println(F("Event in Progress"));
  if (tmrpcm.isPlaying()){                      //If current time < event start time + event duration
    // Serial.println("Event in progress.");    //  Event still has time to continue     
     if (continuousLxMode){
        if (timeNow >= timeAtLastPartyLx + 10000){
          chooseLightshow('r');
          chooseFxLightingState('s');
          timeAtLastPartyLx = timeNow;
        }       //if timenow >= timeAtLastPartyLx + 10000
      }       //if continuousLxMode
   } else {   //No sound is playing    
    if (eventPause == true){                    //post-pause?
      if (switchStaticState == switchStatusOff){
        pauseLightShowManager = false;
      }
        pauseProcedure();      
    }
      else {
        event = false;                            //post-pause complete
        eventPause = true;                        //pre-pause required for next event
        timeAtLastEventEnd = timeNow;
        eventCooldownDuration = 8;                //reset cooldown         
        chooseLightshow('r');                     //r for Random
        }
   }
}
 

void pauseProcedure(){
        if (lxCooldown == false){  //Turn off the lights during cooldown
          chooseLightshow('n');   //n for No lights
          chooseFxLightingState('e');
        //  fxLightshow('p');
          lxCooldown = true;
        }
        eventCooldownDuration--;      
        if (eventCooldownDuration == 0) {            
          eventPause = false;
          lxCooldown = false;
        }
}

        

byte getRandomNumber(byte _upperBound){
  byte x;
   // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  randomSeed(analogRead(0));
  x = random(0, _upperBound);
  return x;
  }
