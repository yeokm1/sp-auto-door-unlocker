#include <MicroView.h>
#include "SharpIR.h"

#define DISTANCE_IR_THRESHOLD 60 //cm
#define DISTANCE_US_THRESHOLD 20 //cm

#define TIMES_TO_PASS_BEFORE_ENGAGE 5

#define PIN_IR_SENSOR A2
#define PIN_BUTTON_CONTROL A0

#define PIN_US_TRIG 2
#define PIN_US_ECHO 3

#define MIN_ENGAGE_TIME 200

#define DELAY_BEFORE_START 2 //Wait x seconds for sensor to settle down
#define INTERVAL_ANIM_CHANGE 300

#define model 1080 //1080 for GP2Y0A21Y
SharpIR * sharpIR;

bool currentAnimState = false;
unsigned long previousAnimChangeTime;

bool currentlyEngaged = false;
unsigned long timeLastEngaged;

int timesPassedThreshold = 0;

void setup(){

  pinMode(OUTPUT, PIN_BUTTON_CONTROL);
  //Immediately turn off signal to remote as the default is high
  engageRemote(false);

  Serial.begin(9600);

  pinMode(INPUT, PIN_IR_SENSOR);
  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);

  sharpIR = new SharpIR(PIN_IR_SENSOR, model);
  
  uView.begin();    // begin of MicroView
  uView.clear(ALL); // erase hardware memory inside the OLED controller
  uView.clear(PAGE);  // erase the memory buffer, when next uView.display() is called, the OLED will be cleared.

  previousAnimChangeTime = millis();
  timeLastEngaged = millis();

  unsigned long startMillis = millis();

  for(int i = DELAY_BEFORE_START; i > 0; i--){
    uView.clear(PAGE);
    uView.setCursor(0, 0);

    //Large Font for seconds
    uView.setFontType(1);
    uView.print(i);
    uView.println("s");

    //Smaller font for others
    uView.setFontType(0);
    uView.print("for \nsensors tostabilise"); //No space between "to" and "stabilise" as they are on separate lines
    uView.display();
    delay(1000);
  }

  Serial.println("Setup complete");
}


void loop(){


  int usDistance = getUSDistance();
  int irDistance = sharpIR->distance();

//  Serial.print(usDistance);
//  Serial.print(" ");
//  Serial.println(irDistance);

  uView.setCursor(0,0);

  if(irDistance <= DISTANCE_IR_THRESHOLD && usDistance <= DISTANCE_US_THRESHOLD){

    timesPassedThreshold++;

    if(timesPassedThreshold > TIMES_TO_PASS_BEFORE_ENGAGE){
      //To prevent unlimited increment
      timesPassedThreshold = TIMES_TO_PASS_BEFORE_ENGAGE;
      
      currentlyEngaged = true;
      timeLastEngaged = millis();
      engageRemote(true);
      drawChangingCircle();
    }
    

  } else {

    timesPassedThreshold = 0;
    unsigned long currentTime = millis();

    //Continue to engage button for the minimum time
    if((currentTime - timeLastEngaged) < MIN_ENGAGE_TIME){
      engageRemote(true);
      drawChangingCircle();
      
    } else{
    
     engageRemote(false);
     
     if(irDistance <= DISTANCE_IR_THRESHOLD){
      drawBlinkingLeftArrow();
     } else if(usDistance <= DISTANCE_US_THRESHOLD){
      drawBlinkingDownArrow();
     } else {
      engageRemote(false);
      drawStaticX();
     }
   }

  }

  uView.display();
    
}

void drawBlinkingLeftArrow(){

  unsigned long currentMillis = millis();

  if (currentMillis - previousAnimChangeTime >= INTERVAL_ANIM_CHANGE) {
    uView.clear(PAGE);
    
    previousAnimChangeTime = currentMillis;

    if (currentAnimState) {
      currentAnimState = false;
    } else {
      currentAnimState = true;
      
      uView.line(32,9,54,37);
      uView.line(32,10,54,38);
      uView.line(32,11,54,39);

      uView.line(32,9,10,37); 
      uView.line(32,10,10,38);   
      uView.line(32,11,10,39); 

      uView.line(10,37,54,37);
      uView.line(10,38,54,38);
      uView.line(10,39,54,39);


    }
  }
  
}

void drawBlinkingDownArrow(){


  unsigned long currentMillis = millis();

  if (currentMillis - previousAnimChangeTime >= INTERVAL_ANIM_CHANGE) {
    uView.clear(PAGE);
    
    previousAnimChangeTime = currentMillis;

    if (currentAnimState) {
      currentAnimState = false;
    } else {
      currentAnimState = true;

      uView.line(10,23,54,9); 
      uView.line(10,24,54,10); 
      uView.line(10,25,54,11); 

      uView.line(10,23,54,37);  
      uView.line(10,24,54,38);   
      uView.line(10,25,54,39);  

      uView.line(53,10,53,38); 
      uView.line(54,10,54,38); 
      uView.line(55,10,55,38); 

    }
  }


 
  
}

void drawChangingCircle(){

  unsigned long currentMillis = millis();

  if (currentMillis - previousAnimChangeTime >= INTERVAL_ANIM_CHANGE) {
    uView.clear(PAGE);
    
    previousAnimChangeTime = currentMillis;

    if (currentAnimState) {
      currentAnimState = false;
      uView.circle(32,24,20);
      Serial.println("empty circle");
    } else {
      currentAnimState = true;
      uView.circleFill(32, 24, 15);
    }
  }
}

void drawStaticX(){
  uView.clear(PAGE);

  //3 lines for each part of the X to make it thicker
  uView.line(10,9,54,37);
  uView.line(10,10,54,38);
  uView.line(10,11,54,39);

  uView.line(54,9,10,37); 
  uView.line(54,10,10,38);
  uView.line(54,11,10,39);
  
}


void engageRemote(bool newState){

  //State is inverted due to the way the circuitry works
  if(newState){
    digitalWrite(PIN_BUTTON_CONTROL, LOW);
  } else {
    digitalWrite(PIN_BUTTON_CONTROL, HIGH);
  }
}

int getUSDistance(){

  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_US_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_US_TRIG, LOW);

  long duration = pulseIn(PIN_US_ECHO, HIGH);
 
  int distCM = (duration/2) / 29.1;

  delay(10);

  return distCM;
}

