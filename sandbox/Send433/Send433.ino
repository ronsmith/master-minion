#include <RCSwitch.h>

RCSwitch sw;

#define SEND_PIN 10 


union Word24 {
   unsigned int w:24;
   unsigned char b[3];
}; 


void setup() {
   sw.enableTransmit(SEND_PIN);
   sw.setProtocol(2);
   Serial.begin(9600);
}

void loop() {
//   sw.send(5393, 24);
//   delay(1000);  
//   sw.send(5396, 24);
//   delay(1000);  

   Word24 w24;
   
   w24.b[0] = 10;
   w24.b[1] = 12;
   w24.b[2] = 14;
   sw.send(w24.w, 24);
   delay(1000);
   
   w24.b[0] = 255;
   w24.b[1] = 255;
   w24.b[2] = 255;
   sw.send(w24.w, 24);
   delay(1000);


//   sw.send("010101010101010101010101");
//   delay(1);  
}


