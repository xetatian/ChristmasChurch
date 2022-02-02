void generateLevels()   //convert boolean values to integers
{
  if (red0){
    red0Level = levelFull;
    } else 
      {
        red0Level = 0;
}
    if (green0){
    green0Level = levelFull;
    } else 
      {
        green0Level = 0;
}
   if (blue0){
    blue0Level = levelFull;
    } else 
      {
        blue0Level = 0;
}
  if (yellow0){
    yellow0Level = levelFull;
    } else 
      {
        yellow0Level = 0;
}
if (red1){
    red1Level = levelFull;
    } else 
      {
        red1Level = 0;
}
    if (green1){
    green1Level = levelFull;
    } else 
      {
        green1Level = 0;
}
   if (blue1){
    blue1Level = levelFull;
    } else 
      {
        blue1Level = 0;
}
  if (yellow1){
    yellow1Level = levelFull;
    } else 
      {
        yellow1Level = 0;
}

   if (fx0){
    fx0Level = levelFull;
    } else 
      {
        fx0Level = 0;
}
    if (fx1){
    fx1Level = levelFull;
    } else 
      {
        fx1Level = 0;
}
   if (fx2){
    fx2Level = levelFull;
    } else 
      {
        fx2Level = 0;
      }
  if (fx3){
    fx3Level = levelFull;
    } else 
      {
        fx3Level = 0;
      }   
}
  
void updateLeds(){    //This function carries out the physical outputting to the TLC led driver
  generateLevels();  
  tlc.setLED(0, red0Level, green0Level, blue0Level);
  tlc.setLED(1, red1Level, green1Level, blue1Level);
  tlc.setLED(2, fx0Level, fx1Level, fx2Level);
  tlc.setLED(3, yellow0Level, yellow1Level, fx3Level);
  tlc.write();    
  //Serial.println(F("Writing to TLC"));
}

 void allColourSet(bool _x){
     red0 = _x;
     green0 = _x;
     blue0 = _x;
     yellow0 = _x;
     red1 = _x;
     green1 = _x;
     blue1 = _x;
     yellow1 = _x;     
 }

 void allLedSet(bool _x){
     red0 = _x;
     green0 = _x;
     blue0 = _x;
     yellow0 = _x;
     red1 = _x;
     green1 = _x;
     blue1 = _x;
     yellow1 = _x;     
     fx0 = _x;    
     fx1 = _x;    
     fx2 = _x;    
     fx3 = _x;    
 }

 void chooseLightshow(char _command){   
  byte staticHoldSelectNo = 0; //Only required when _command is 'h'. Must be called here as it breaks the case statement if called in h ?!?!?!
    switch (_command){     
      case 'n': //null - lights off
        getLightshowDetails(98);     
      break;
      case 's': //static - all lights on
        getLightshowDetails(99);      
      break;
      case 'h': //Hold on a solid colour
       staticHoldSelectNo = getRandomNumber(6);   
        staticHoldSelectNo  = 90 + staticHoldSelectNo; //Offset from 90 - Static hold colours are 90 thru 95
        getLightshowDetails(staticHoldSelectNo);
      break;
      case 'r':  //random chase
        byte nextLightshowSeed;  
        nextLightshowSeed = getRandomNumber(15);
        //nextLightshowSeed = 90;
        getLightshowDetails(nextLightshowSeed);
      break;
    }
    timeAtLastLxStep = millis(); //Start of the first LX step
    //  Serial.println("timeAtLastLxStep");
    //  Serial.println(timeAtLastLxStep);
    calculateLxDelay();
 }

void getLightshowDetails(byte _nextLightshowSeed){
  switch (_nextLightshowSeed){
      case 0:   //rgToby
        currentLightshowChar = 0;
        noOfTotalSteps = 1;
        build = false;
      break;
      case 1: //rbTogy
        currentLightshowChar = 1;
        noOfTotalSteps = 1;
        build = false;
        forward = true;
      break;
      case 2: //ryTogb
        currentLightshowChar = 2;
        noOfTotalSteps = 1;
        build = false;
        forward = true;
      break;
       case 3:  //r0Toy1
        currentLightshowChar = 3;
        noOfTotalSteps = 7;
        build = false;
        forward = true;
      break;
       case 4:  //r0Toy1 build
        currentLightshowChar = 3;
        noOfTotalSteps = 8;
        build = true;
        forward = false;
      break;
       case 5:  //insideOut build
        currentLightshowChar = 4;
        noOfTotalSteps = 4;  //(3 + 1[default] for the blank build step)
        build = true;
        forward = true;
      break;
         case 6:  //Inside out
        currentLightshowChar = 4;
        noOfTotalSteps = 3;  
        build = false;
        forward = true;
      break;
       case 7:  //Outside in build
        currentLightshowChar = 4;
        noOfTotalSteps = 4;  //(3 + 1[default] for the blank build step)
        build = true;
        forward = false;
      break;
        case 8:  //Outside in 
        currentLightshowChar = 4;
        noOfTotalSteps = 3;  //(3 + 1[default] for the blank build step)
        build = false;
        forward = false;
      break;
        case 9:  //groupsOf3
        currentLightshowChar = 5;
        noOfTotalSteps = 2; 
        build = false;
        forward = true;
      break;
        case 10:  //rThruY 
        currentLightshowChar = 6;
        noOfTotalSteps = 7; 
        build = true;
        forward = true;
      break;
       case 11:  //rThruY build reverse
        currentLightshowChar = 6;
        noOfTotalSteps = 7; 
        build = true;
        forward = false;
      break;
         case 12:  //rThruY 
        currentLightshowChar = 6;
        noOfTotalSteps = 7; 
        build = false;
        forward = true;
      break;
       case 13:  //rThruY  reverse 
        currentLightshowChar = 6;
        noOfTotalSteps = 7; 
        build = false;
        forward = false;
      break;
       case 14:  //allRBGY  reds, blues, green, yellows 
        currentLightshowChar = 7; //(3 + 1[default] for the blank build step)
        noOfTotalSteps = 4; 
        build = true;
        forward = true;
      break;
       case 90:   //Hold Static pair of colours
        currentLightshowChar = 90;
        noOfTotalSteps = 0;
       break;
       case 91:   //Hold Static pair of colours
        currentLightshowChar = 91;
        noOfTotalSteps = 0;
       break;
       case 92:   //Hold Static pair of colours
        currentLightshowChar = 92;
        noOfTotalSteps = 0;
       break;
       case 93:   //Hold Static pair of colours
        currentLightshowChar = 93;
        noOfTotalSteps = 0;
       break;
       case 94:   //Hold Static pair of colours
        currentLightshowChar = 94;
        noOfTotalSteps = 0;
       break;
       case 95:   //Hold Static pair of colours
        currentLightshowChar = 95;
        noOfTotalSteps = 0;
       break;
      case 98:
        currentLightshowChar = 98;
        noOfTotalSteps = 0;
      break;
      case 99:
        currentLightshowChar = 99;
        noOfTotalSteps = 0;
      break;
    }
 }

void lightshowManager(){                          
  //Serial.println("Calculating Step Position");
   if (!pauseLightShowManager){
      calculateStepPosition();
      switch (currentLightshowChar){  //Master FX List
        case 0:
          rgToby();
        break;
        case 1:
          rbTogy();
        break;
        case 2:
          ryTobg();
        break;
        case 3:
          r0Toy1();
        break;
        case 4:
          insideOut();
          break;
        case 5:
          groupsOf3();
          break;
        case 6:
          rThruY();
        break;
        case 7:
          allRBGY();
        break;
        case 90:
          holdStaticRB();
        break;
        case 91:
          holdStaticRG();
        break;
        case 92:
          holdStaticRY();
        break;
        case 93:
          holdStaticBG();
        break;
        case 94:
          holdStaticYG();
        break;
        case 95:
          holdStaticBY();
        break;
        case 98:
          allColourSet(false);
        break;         
        case 99:
          allStatic();        
        break;
        }
      updateLeds();  

   } //if !pauselightshowManager
}

void calculateStepPosition(){
  if (timeNow >  timeAtLastLxStep + lxDelay){
    switch(forward){
    case true:     
    stepNo++;
    break;
    case false:
    stepNo--;
    break;
    }
    if (build == false){ //Should the chase clear all channels between steps?
      allColourSet(false);
    }
    timeAtLastLxStep = timeNow;
    if (stepNo > noOfTotalSteps){ //Boundary restrictions
      stepNo = 0;
      allColourSet(false);
      }
    if (stepNo < 0){
        stepNo = noOfTotalSteps;
      }
    }
  }

void calculateLxDelay(){
 
 uint16_t speedSetting = getRandomNumber(3);
  switch (speedSetting){
    case 0:
      lxDelay = 500; //Half a second
    break;
    case 1:
      lxDelay = 750; //1 Second
    break;
    case 2:
      lxDelay = 1000; //2 Seconds
    break;
    default:
     lxDelay = 1000;
    break;
    }
}

void rgStatic(){
  redLeds(1);
  greenLeds(1); 
}

void byStatic(){
  blueLeds(1);
  yellowLeds(1);   
}

void rgToby(){ //Red & Green - Blue & Yellow 
    switch (stepNo){
        case 0:
        redLeds(1);
        greenLeds(1);
        break;
        case 1:
        blueLeds(1);
        yellowLeds(1);
        break;
      }  
}

void rbTogy(){    //Red & Blue - Green & Yellow
    switch (stepNo){
        case 0:
        redLeds(1);
        blueLeds(1);
        break;
        case 1:
        greenLeds(1);
        yellowLeds(1);
        break;
      }  
}

void ryTobg()     {//Red & Yellow - Blue & Yellow 
    switch (stepNo){
        case 0:
        redLeds(1);
        yellowLeds(1);
        break;
        case 1:
        blueLeds(1);
        greenLeds(1);
        break;
      }  
}

void r0Toy1(){
    switch (stepNo){
        case 0:
          red0 = true;
        break;
        case 1:
          green0 = true;
        break;
        case 2:
          blue0 = true;
        break;
        case 3:
          yellow0 = true;
        break;
         case 4:
          red1 = true;
        break;
        case 5:
          green1 = true;
        break;
        case 6:
          blue1 = true;
        break;
        case 7:
          yellow1 = true;
        break;
        default:
          allColourSet(false); //Used during a Build
        break;
      }  
}

void insideOut(){
    switch (stepNo){
        case 0:
          red1 = true;
          yellow0 = true;
        break;
        case 1:
          green1 = true;
          blue0 = true;
        break;
        case 2:
          blue1 = true;
          green0 = true;
        break;
        case 3:
          yellow1 = true;
          red0 = true;
        break;    
        default:
          allColourSet(false); //Used during a Build
        break;
      }  
}

void groupsOf3(){
    switch (stepNo){
        case 0:
          red0 = true;
          yellow0 = true;
          blue1 = true;
        break;
        case 1:
          green0 = true;
          red1 = true;
          yellow1 = true;
        break;
        case 2:
          blue0 = true;
          green1 = true;
        break;
   
        default:
          allColourSet(false); //Used during a Build
        break;
      }  
}

void rThruY(){
     switch (stepNo){
        case 0:
          redLeds(true);
        break;
        case 1:
          greenLeds(true);
        break;
        case 2:
        blueLeds(true);
        break;
        case 3:
        yellowLeds(true);
        break;
        case 4: 
        yellowLeds(false);
        break;
        case 5:
        blueLeds(false);
        break;
        case 6: 
        greenLeds(false);
        break;
        case 7:
        redLeds(false);
        break;
        default:
          allColourSet(false); //Used during a Build
        break;
      }  
  }

void allRBGY(){
     switch (stepNo){
        case 0:
        redLeds(true);
        break;
        case 1: 
         blueLeds(true);
        break;
        case 2: 
          greenLeds(true);
        break;
        case 3: 
          yellowLeds(true);
        break;                                                        
        default:
          allColourSet(false); //Used during a Build
        break;
      }  
  }  

//---------------Static Pairs--------------//  
void holdStaticRB(){
  redLeds(true);
  blueLeds(true);        
}

void holdStaticRG(){
  redLeds(true);
  greenLeds(true);        
}

void holdStaticRY(){
  redLeds(true);
  yellowLeds(true);        
}

void holdStaticBG(){
  greenLeds(true);
  blueLeds(true);        
}

void holdStaticYG(){
  greenLeds(true);
  yellowLeds(true);        
}

void holdStaticBY(){
  yellowLeds(true);
  blueLeds(true);        
}
 //---------------Static Pairs--------------//  

 
  void allStatic(){

  allColourSet(true);
  pauseLightShowManager = true; //Stop writing to TLC for smoother audio
  
  }
  
    
void redLeds(byte _x){
  red0 = _x;
  red1 = _x;
  }

void greenLeds(byte _x){
  green0 = _x;
  green1 = _x;
  }

void blueLeds(byte _x){
  blue0 = _x;
  blue1 = _x;
  }

void yellowLeds(byte _x){
  yellow0 = _x;
  yellow1 = _x;
  }

void chooseFxLightingState(char _command){  //LedFX controller. Needs work!
  switch (_command){
    case 'n': //no lights
      fx0 = false;
      fx1 = false;
      fx2 = false;
      fx3 = false;
    break;
      case 's': //solid
      fx0 = true;
      fx1 = true;
      fx2 = true;
      fx3 = true;
    break;
      case 'i': //internal
      fx0 = false;
      fx1 = false;
      fx2 = true;
      fx3 = true;
    break;
      case 'e': //external
      fx0 = true;
      fx1 = true;
      fx2 = false;
      fx3 = false;
    break;    
    }    
  }


 void tlcFlashOut(){      //Used to check each RGB output during Setup 

    int flashOutDelayTime = 500;

    allColourSet(false);
    fx0 = false;
    fx1 = false;
    fx2 = false;
    fx3 = false;  
    updateLeds();

    red0 = true;
    green0 = true;
    blue0 = true;
    yellow0 = true;
    updateLeds();
    Serial.print(F("RGBY0 - "));
    delay(flashOutDelayTime);
    
    red0 = false;
    green0 = false;
    blue0 = false;
    yellow0 = false;
    red1 = true;
    green1 = true;
    blue1 = true;
    yellow1 = true;
    updateLeds();
    Serial.print(F("RGBY1."));
    delay(flashOutDelayTime);
    
    red1 = false;
    green1 = false;
    blue1 = false;
    yellow1 = false;
    fx0 = true;   
    updateLeds();
    Serial.println(F("FX0 (Sign). "));
    delay(flashOutDelayTime);
    
    fx0 = false;
    fx1 = true;
    updateLeds();
    Serial.print(F("FX1 (Door). "));
    delay(flashOutDelayTime);
    
    fx1 = false;
    fx2 = true;
    updateLeds();
    Serial.print(F("FX2 (Church). "));
    delay(flashOutDelayTime);
    
    fx2 = false;
    fx3 = true;
    updateLeds();
    Serial.print(F("FX4 (Spire). "));
    delay(flashOutDelayTime);
    
    fx0 = false;
    fx1 = false;
    fx2 = false;
    fx3 = false;  
    updateLeds();
    }
