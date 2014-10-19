/*************************************
 * PumpMinion.cpp
 * Author: Ron Smith
 * Created: 10/10/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadioHandler.h"

#define RELAY_PIN 8
#define SEND_PIN  12
#define RECV_INT  0   // interrupt 0 is pin 2

class PumpMinionHandler : public MinionRadioHandler {
   public:
      virtual int setup(unsigned int relayPin, unsigned int sendPin, unsigned int recvInt, byte id=0) {
         Serial.println("Setup: pump minion handler.");
         this->relayPin = relayPin;
         pinMode(relayPin, OUTPUT);
         digitalWrite(RELAY_PIN, LOW);
         return MenuRadioHandler::setup(sendPin, recvPin, id);
      }
      
      virtual int handle() {
         return MenuRadioHandler::handle();
      }
      
      virtual void turnOffRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::turnOffRequest(msg);
         digitalWrite(relayPin, LOW);
      }
      
      virtual void turnOnRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::turnOnRequest(msg);
         digitalWrite(relayPin, HIGH);
      }
      
      virtual void currentStateRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::currentStateRequest(msg);
         send(MinionRadio::CURR_STATE_RESP, digitalRead(relayPin));
      }
      
      virtual void scheduleOffTimeRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::scheduleOffTimeRequest(msg);
         // TODO
      }
      
      virtual void scheduleOnTimeRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::scheduleOnTimeRequest(msg);
         // TODO
      }
      
      virtual void clearScheduledTimesRequest(MinionRadioMessage& msg) {
         MenuRadioHandler::clearScheduledTimesRequest(msg);
         // TODO  
      }
      
   private:
      int relayPin;
};

PumpMinionHandler handler;

void setup() {
   Serial.begin(9600);
   handler.setup(RELAY_PIN, SEND_PIN, RECV_INT);
   Serial.println("Setup complete.");
}

void loop() {
   handler.handle();
}


