#include <RCSwitch.h>

#define RELAY_PIN 8
#define SEND_PIN  10
#define RECV_INT  0   // interrupt 0 is pin 2


RCSwitch sw;

void setup() {
   pinMode(RELAY_PIN, OUTPUT);
   digitalWrite(RELAY_PIN, LOW);
   sw.enableReceive(RECV_INT);
   sw.enableTransmit(SEND_PIN);
   Serial.begin(9600);
   Serial.println("setup complete");
}

void loop() {
   if (sw.available()) {
      int value = sw.getReceivedValue();
      Serial.print("Received: value=");
      Serial.println(value);
      switch (value) {
         case 1000:
            digitalWrite(RELAY_PIN, HIGH);
            break;
         case 2000:
            digitalWrite(RELAY_PIN, LOW);
            break;
         default:
            // ignore it
            break;
      }
      sw.resetAvailable();
      delay(1000);
      sw.send(value+1, 24);
   }
}

