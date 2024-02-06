#include "Arduino.h"
#include "Dobot.h"
#include "SoftwareSerial.h"
//#include "blockMap.h"
#include "IrSensor.h"
#include "counter.h"

Dobot::Dobot(uint8_t rx = 2, uint8_t tx = 3, int32_t dobotBaudRate = 115200, int32_t serialBaudRate = 115200) {
  SoftwareSerial mySerial(rx,tx);
  pinMode(rx, INPUT);
  pinMode(tx, OUTPUT);
  
  // Init serial comms to Dobot
  mySerial.begin(115200);   // Dobot baud rate
  Serial.begin(115200);     // Default baud rate for debugging COM

  Counter counter = Counter();
}

void Dobot::Init() {
  // Execute safe procedure
  Serial.println("Dobot initialising! Please wait..");
  Dobot::MakeSafe();
}

// Loads a block into a storage bay based on block type passed in as an argument. Moves block from import bay
void Dobot::Load() {

  uint8_t blockType = IrSensor::BlockTypeDetector();
  if (blockType < 100) {
    Serial.println("Loading...");
    if (blockType == 0) {
      Dobot::Move(30, 1); // import bay
      Dobot::SuckStart();
      Dobot::Move(blockType, counter.whiteValue); // bay 0
      Dobot::SuckStop();
      counter.whiteValue++;
    } else if (blockType == 10) {
      Dobot::Move(30, 1); // import bay
      Dobot::SuckStart();
      Dobot::Move(blockType, counter.redValue); // bay 1
      Dobot::SuckStop();
      counter.redValue++;
    } else {
      Dobot::Move(30, 1); // import bay
      Dobot::SuckStart();
      Dobot::Move(blockType, counter.blackValue); // bay 2
      Dobot::SuckStop();
      counter.blackValue++;
    }
    Dobot::Move(30, 0);
    Serial.println("Loading complete!");
  } else {
    Serial.println("Zzzzzz...");
  }
}

// Unloads a block from a storage bay specified in the argument. Moves the block to the export bay
void Dobot::Unload(int8_t storageBay) {
  if (storageBay != -1) {
    Serial.println("Unloading...");
    if (storageBay == 0) {
      Dobot::Move(10, counter.whiteValue);
      Dobot::SuckStart();
      Dobot::Move(30, 2); // export bay
      Dobot::SuckStop();
      counter.whiteValue--;
    } else if (storageBay == 1) {
      Dobot::Move(10, counter.redValue);
      Dobot::SuckStart();
      Dobot::Move(30, 2); // export bay
      Dobot::SuckStop();
      counter.redValue--;
    } else if (storageBay == 2) {
      Dobot::Move(20, counter.blackValue);
      Dobot::SuckStart();
      Dobot::Move(30, 2); // export bay
      Dobot::SuckStop();
      counter.blackValue--;
    }
    Dobot::Move(30, 0);
    Serial.println("Unloading complete!");
  } else {
    Serial.println("Invalid storage bay selected! Choose bay 0, 1, or 2.");
  }
}

//moves to positions of home, load, unload and 3 storage bays for visual checks by user.
void Dobot::MakeSafe(){

  for(int i=0;i<3;i++){ 
    Dobot::Move(30,i);
  }
  for(int i=0;i<30;i++){ 
    Dobot::Move(i,0);
    i+=9;
  }
  Dobot::Move(30,0);
}

//move dobot arm to position specified in map by using blockType as multiple of 10 and counter for last block placed.
void Dobot::Move(uint8_t blockType, uint8_t counter){

  for(int i=0;i<23;i++){
    int byteToSend = Dobot::GetLocation(blockType, counter, i);
    mySerial.write(byteToSend);
  }
}

//starts pump for suction
void Dobot::SuckStart(){
  int suckStartPayload[]{170,170,4,62,3,1,1,189};
  for(int i=0; i<sizeof(suckStartPayload)/sizeof(suckStartPayload[i]); i++){
    mySerial.write(suckStartPayload[i]);
  }
}

//stops pump for suction
void Dobot::SuckStop(){
  int suckStopPayload[]{170,170,4,62,3,1,0,190};
  for(int i=0;i<sizeof(suckStartPayload)/sizeof(suckStartPayload[i]);i++){
    mySerial.write(suckStopPayload[i]);
  }
}

//byte Dobot::commandFrame(byte comFrame[]){
  //byte incomingByte;
  // To collect the response from Dobot
//  
//for(int i=0;i<(comFrame[2]+4);i++){   //The third comFrame byte gives the number of payload bytes; total number of bytes is 4 more than this
//  mySerial.write(comFrame[i]);
//}
//delay(50);
//
////read response and send it to the serial monitor:
//Serial.print ("Dobot response:  ");
//while (mySerial.available() > 0){
//  int message[0] = mySerial.read();
//  Serial.print(message[0]);
//  Serial.print(' ');
//  }
//  Serial.println();
//}
