#include "Arduino.h"
#include "Dobot.h"
#include "SoftwareSerial.h"
//#include "blockMap.h"
#include "irSensor.h"
#include "counter.h"

// Globals:
SoftwareSerial mySerial(2,3);  // Rx, Tx
byte incomingByte;  // To collect the response from Dobot

Dobot::Dobot() {
}

Counter counter = Counter();

void Dobot::init() {

  // Init serial comms to Dobot
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, OUTPUT);
  mySerial.begin(115200);  // Dobot baud rate

  // Execute safe procedure
  Serial.println("Dobot initialising!");
  Dobot::makeSafe();
}

// Loads a block into a storage bay based on block type passed in as an argument. Moves block from import bay
void Dobot::load() {

  uint8_t blockType = irSensor::blockDetector();
  if (blockType < 100) {
    Serial.println("Loading...");
    if (blockType == 0) {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.whiteValue); // bay 0
      Dobot::suckStop();
      counter.whiteValue++;
    } else if (blockType == 10) {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.redValue); // bay 1
      Dobot::suckStop();
      counter.redValue++;
    } else {
      Dobot::move(30, 1); // import bay
      Dobot::suckStart();
      Dobot::move(blockType, counter.blackValue); // bay 2
      Dobot::suckStop();
      counter.blackValue++;
    }
    Dobot::move(30, 0);
    Serial.println("Loading complete!");
  } else {
    Serial.println("Zzzzzz...");
  }
}

// Unloads a block from a storage bay specified in the argument. Moves the block to the export bay
void Dobot::unload(uint8_t storageBay) {
  if (storageBay < 4) {
    Serial.println("Unloading...");
    if (storageBay == 0) {
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.whiteValue--;
    } else if (storageBay == 1) {
      Dobot::move(10, counter.redValue);
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.redValue--;
    } else if (storageBay == 2) {
      Dobot::move(20, counter.blackValue);
      Dobot::suckStart();
      Dobot::move(30, 2); // export bay
      Dobot::suckStop();
      counter.blackValue--;
    }
    Dobot::move(30, 0);
    Serial.println("Unloading complete!");
  } else {
    Serial.println("Invalid storage bay selected! Choose bay 0, 1, or 2.");
  }
}

//moves to positions of home, load, unload and 3 storage bays for visual checks by user.
void Dobot::makeSafe(){

  for(int i=0;i<3;i++){ 
    Dobot::move(30,i);
  }
  for(int i=0;i<30;i++){ 
    Dobot::move(i,0);
    i+=9;
  }
  Dobot::move(30,0);
}

//move dobot arm to position specified in map by using blockType as multiple of 10 and counter for last block placed.
void Dobot::move(uint8_t blockType, uint8_t counter){

  for(int i=0;i<23;i++){
    int byteToSend = Dobot::getLocation(blockType, counter, i);
    mySerial.write(byteToSend);
  }
}

//starts pump for suction
void Dobot::suckStart(){
  int suckStartPayload[]{170,170,4,62,3,1,1,189};
  for(int i=0; i<23; i++){
    mySerial.write(suckStartPayload[i]);
  }
}

//stops pump for suction
void Dobot::suckStop(){
  int suckStopPayload[]{170,170,4,62,3,1,0,190};
  for(int i=0;i<23;i++){
    mySerial.write(suckStopPayload[i]);
  }
}

uint8_t Dobot::getLocation(uint8_t blockType, uint8_t counterValue, uint8_t loopIndex){

    uint8_t bMap[33][23]{
    //block type 0 (white)
    {170,170,19,84,3,0,0,0,25,67,0,0,24,67,0,0,79,194,0,0,0,0,225},
    {170,170,19,84,3,0,0,0,43,67,0,0,38,67,0,0,79,194,0,0,0,0,193},
    {170,170,19,84,3,0,0,0,64,67,0,0,53,67,0,0,79,194,0,0,0,0,157},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,79,194,0,0,0,0,122},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,79,194,0,0,0,0,86},
    {170,170,19,84,3,0,0,0,106,67,0,0,82,67,0,0,210,193,0,0,0,0,212},
    {170,170,19,84,3,0,0,0,85,67,0,0,67,67,0,0,210,193,0,0,0,0,248},
    {170,170,19,84,3,0,0,0,68,67,0,0,52,67,0,0,210,193,0,0,0,0,24},
    {170,170,19,84,3,0,0,0,48,67,0,0,38,67,0,0,210,193,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,31,67,0,0,25,67,0,0,210,193,0,0,0,0,88},
    
    //block type 1 (red)
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,79,194,0,0,0,0,8},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,79,194,0,0,0,0,18},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,79,194,0,0,0,0,199},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,79,194,0,0,0,0,39},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,79,194,0,0,0,0,177},
    {170,170,19,84,3,0,0,0,55,67,0,0,85,193,0,0,210,194,0,0,0,0,133},
    {170,170,19,84,3,0,0,0,78,67,0,0,246,255,0,0,210,194,0,0,0,0,143},
    {170,170,19,84,3,0,0,0,103,67,0,0,102,193,0,0,210,194,0,0,0,0,68},
    {170,170,19,84,3,0,0,0,67,185,0,0,193,180,0,0,210,194,0,0,0,0,164},
    {170,170,19,84,3,0,0,0,137,67,0,0,90,193,0,0,210,194,0,0,0,0,46},

    //block type 2(black)
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,79,194,0,0,0,0,172},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,79,194,0,0,0,0,130},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,79,194,0,0,0,0,95},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,79,194,0,0,0,0,58},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,79,194,0,0,0,0,32},
    {170,170,19,84,3,0,0,0,166,66,0,0,65,195,0,0,210,194,0,0,0,0,41},
    {170,170,19,84,3,0,0,0,185,66,0,0,88,195,0,0,210,194,0,0,0,0,255},
    {170,170,19,84,3,0,0,0,198,66,0,0,110,195,0,0,210,194,0,0,0,0,158},
    {170,170,19,84,3,0,0,0,215,66,0,0,130,195,0,0,210,194,0,0,0,0,183},
    {170,170,19,84,3,0,0,0,229,66,0,0,142,195,0,0,210,194,0,0,0,0,157},

    {170,170,19,84,3,0,0,0,52,67,0,0,0,0,0,0,0,0,0,0,0,50}, //home
    {170,170,19,84,3,0,0,0,255,65,0,0,125,67,0,0,79,194,0,0,0,0,152},  //import bay
    {170,170,19,84,3,0,0,0,8,66,0,0,149,195,0,0,81,194,0,0,0,0,244}// export bay
    };

    return bMap[blockType + counterValue][loopIndex];
}

//void Dobot::commandFrame(byte comFrame[]){
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
