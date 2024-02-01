#include "Dobot.h"
#include "irSensor.h"

Dobot dobot = Dobot();
irSensor sensor = irSensor();

char readMsg;

void setup(){
  //dobot.init();
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  sensor.blockTypeDetector();

  
//  if (Serial.available()){
//    readMsg = Serial.read();     
//    if (dobot.blockPresent()){
//      dobot.load(dobot.blockTypeDetector());
//      delay(5000);
//    }
//    else if(Serial.read()=="block"){
//      dobot.load(dobot.blockTypeDetector());
//      delay(5000);
//    }
//    else if(readMsg==0|| readMsg==1||readMsg==2){
//      dobot.unload(readMsg);
//    }
//    else{
//      Serial.println("Zzzzzz...");
//    }
//  }
}
