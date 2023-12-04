#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Arduino.h"
#include "Dobot.h"
#include "SoftwareSerial.h"

//Globals:
SoftwareSerial mySerial = SoftwareSerial(2,3);  //Rx, Tx
byte  getPose[] = {170,170,2,10,0,246};
byte incomingByte; //to collect the response from Dobot
byte message[100];  //longer than the longest possible message
int i;

//Union type makes converting from byte array to float easy:
union coord {
  byte cByte[4];
  float cFloat;
};
coord cart[4];  //position of the arm in cartesian coordinates
coord pol[4];  //position of the arm in polar coordinates


// Empty Constructor
Dobot::Dobot(){
};

void Dobot::begin(){
    Serial.begin(115200);
    pinMode(2,INPUT);
    pinMode(3,OUTPUT);
    mySerial.begin(115200);  //Dobot baud rate
}
//  Print Current Position
void Dobot::printPose(){

for(int i=0;i<6;i++){
  mySerial.write(getPose[i]);
}

//allow time for the Dobot to serial send a response
delay(50);

//Read response back from Dobot:
i=0;
while (mySerial.available() > 0){
  message[i] = mySerial.read();
  i++;
}

//distribute the Dobot position bytes to the appropriate coordinates:
for(i=0;i<=3;i++){
  cart[0].cByte[i] = message[i+5];
  cart[1].cByte[i] = message[i+9];
  cart[2].cByte[i] = message[i+13];
  cart[3].cByte[i] = message[i+17];
  pol[0].cByte[i] = message[i+21];
  pol[1].cByte[i] = message[i+25];
  pol[2].cByte[i] = message[i+29];
  pol[3].cByte[i] = message[i+33];
}

Serial.print("Cartesian: ");
Serial.print(cart[0].cFloat);  //The union type means the float equivalent is available
Serial.print(" ");
Serial.print(cart[1].cFloat);
Serial.print(" ");
Serial.print(cart[2].cFloat);
Serial.print(" ");
Serial.print(cart[3].cFloat);
Serial.print(" Polar: ");
Serial.print(pol[0].cFloat);
Serial.print(" ");
Serial.print(pol[1].cFloat);
Serial.print(" ");
Serial.print(pol[2].cFloat);
Serial.print(" ");
Serial.println(pol[3].cFloat);
delay(1000);
}

void Dobot::commandFrame(byte comFrame[]){

//Start Joint Movement

for(int i=0;i<8;i++){
  mySerial.write(comFrame[i]);
}
delay(50);

//read response and ignore it
while (mySerial.available() > 0){
  message[i] = mySerial.read();
  i++;

}
}