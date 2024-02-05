#include "Arduino.h"
#include "IrSensor.h"

IrSensor::IrSensor(){}

bool IrSensor::BlockPresent(){
    uint16_t sensorValue = ReadSensor();
    if(sensorValue<290){
        return true;
    }
    else{
        return false;
    }
}

uint16_t IrSensor::ReadSensor(){
  uint16_t avgSensorValue = 0;
  for (int i =0; i< 51; i++){
    avgSensorValue += analogRead(A0);
  }
  return((avgSensorValue/50));
}

//blockTypeCheck returns a numeric value in multiples of 10 as a maximum of 10 blocks for each type can be placed.
//number is used within blockMap to return position element.
uint16_t IrSensor::BlockTypeDetector(){

    uint16_t avgSensorValue = IrSensor::ReadSensor();

    if((135 < avgSensorValue) && (avgSensorValue < 155)){
        Serial.println("White block detected! Starting loading sequence...");
        return 0;
    }

    else if ((165 < avgSensorValue) && (avgSensorValue < 185)){
        Serial.println("Red block detected! Starting loading sequence...");
        return 10;
    }

    else if((260 < avgSensorValue) && (avgSensorValue < 270)){
        Serial.println("Black block detected! Starting loading sequence...");
        return 20;
    }

    else{
        Serial.println("Invalid block detected!");
        return 100;
    }
}
