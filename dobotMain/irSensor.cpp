#include "Arduino.h"
#include "irSensor.h"

irSensor::irSensor(){
  uint16_t whiteLowerBound = 400;
  uint16_t whiteUpperBound = 499;
  uint16_t redLowerBound = 500;
  uint16_t redUpperBound = 599;
  uint16_t blackLowerBound = 850;
  uint16_t blackUpperBound = 949;
  }

//void irSensor::BlockTypeCalibrator(){
//  String readMsg;
//  Serial.println("Please place block and type colour and enter when ready");
//  while(readMsg == ""){
//    readMsg = Serial.readString();
//    readMsg = readMsg.toLowerCase();
//  }
//  if(readMsg == "white"){
//  uint16_t sensorValue = readSensor();
//  whiteLowerBound = sensorValue - 10;
//  whiteUpperBound = sensorValue + 10;
//  }
//  
//  else if(readMsg == "red"){
//  uint16_t sensorValue = readSensor();
//  redLowerBound = sensorValue - 10;
//  redUpperBound = sensorValue + 10;
//  }
//  
//  else if(readMsg == "black"){
//  uint16_t sensorValue = readSensor();
//  blackLowerBound = sensorValue - 10;
//  blackUpperBound = sensorValue + 10;
//  }
//
//  //TODO check if ranges crossover
//}

bool irSensor::blockPresent(){
    uint16_t sensorValue = readSensor();
    if(sensorValue<910){
        return true;
    }
    else{
        return false;
    }
}

uint16_t irSensor::readSensor(){
  uint32_t avgSensorValue = 0;
  for (int i =0; i< 101; i++){
    avgSensorValue += analogRead(A0);
  }
  return((avgSensorValue/100));
}

//blockTypeCheck returns a numeric value in multiples of 10 as a maximum of 10 blocks for each type can be placed.
//number is used within blockMap to return position element.
uint16_t irSensor::blockTypeDetector(){

    uint16_t avgSensorValue = irSensor::readSensor();
//    Serial.println(avgSensorValue);

    if((whiteLowerBound < avgSensorValue) && (avgSensorValue < whiteUpperBound)){
        Serial.println("White block detected! Starting loading sequence...");
        return 0;
    }

    else if ((redLowerBound < avgSensorValue) && (avgSensorValue < redUpperBound)){
        Serial.println("Red block detected! Starting loading sequence...");
        return 10;
    }

    else if((blackLowerBound < avgSensorValue) && (avgSensorValue < blackUpperBound)){
        Serial.println("Black block detected! Starting loading sequence...");
        return 20;
    }

    else{
        Serial.println("Invalid block detected!");
        return 100;
    }
}
