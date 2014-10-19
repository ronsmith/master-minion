/*************************************
 * MinionRadio.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"
#include <Time.h>

// Number of seconds to wait for next word in message. 
#define RECV_NEXT_TIMEOUT 2

/**
 * Enable the radio. It will be able to transmit and receive data.
 */
int MinionRadio::enable() {
   if (isEnabled()) return ALREADY_ENABLED;
   if (!sendPin || !recvInt) return NOT_CONFIGURED;
   handler = h;
   rcsw = new RCSwitch();
   rcsw->enableReceive(recvInt);
   rcsw->enableTransmit(sendPin);
   rcsw->setProtocol(2);
   rcsw->setRepeatTransmit(3);
   return OK;
}

/**
 * Disable the radio. It will no longer transmit or receive data.
 */
void MinionRadio::disable() {
   if (isEnabled()) {
      rcsw->disableReceive();
      rcsw->disableTransmit();
      delete rcsw;
      rcsw = NULL;
   }
}

/**
 * Send a 4-word message with the specified data.
 */
int MinionRadio::send(byte id, byte msgType, word24 extraData, word minionType) {
   if (!isEnabled()) return NOT_ENABLED;
   
   byte crc8 = calcCRC8()//TODO calculate and send CRC-8
   sendWord(MESSAGE_START, id, msgType);
   sendWord(year(), month(), day());
   sendWord(hour(). minute(), second());
   sendWord(extraData);
   return OK;
}

/**
 * Send a 4-word message with the specified data.
 */
int MinionRadio::send(byte id, byte msgType, byte ex0, byte ex1, byte ex2, word minionType) {
   Word24 w24;
   w24.b[0] = ex0;
   w24.b[1] = ex1;
   w24.b[2] = ex2;
   return send(id, msgType, w24.w, minionType);
}

/**
 * Try to receive an incoming message. 
 * Returns a pointer to a new 4-Word24 array or NULL if no message is available.
 * If this radio is not the Master, the clock is synced with the timestamp in the message.
 * NOTE: the caller must delete the returned array!!!
 */
Word24* MinionRadio::receive() {
   if (rcsw->available()) {
      Word24 w24;
      w24.w = receiveWord();
      if (w24.b[0] == MESSAGE_START) {
         Word24* req = new Word24[5];
         req[0] = w24;
         req[1].w = receiveNext(req[0].w);
         if (req[1].w == 0) {
            delete req;
            return NULL;
         }
         req[2].w = receiveNext(req[1].w);
         if (req[2].w == 0) {
            delete req;
            return NULL;
         }
         req[3].w = receiveNext(req[2].w);
         if (req[3].w == 0) {
            delete req;
            return NULL;
         }
         req[4].w = receiveNext(req[3].w);
         
         //TODO: check CRC-8 and request retransmit if needed
         
         syncClock(req[1], req2[1]);
         
         return req;
      }
   }
   return NULL;
}

/**
 *
 */
void MinionRadio::syncClock(Word24& d, Word24& t) {
   if (isMaster) return;
   //TODO
}

/**
 * Receive the next word. The method returns true if successful or false if no word was received within
 * the RECV_NEXT_TIMEOUT limit. The value received is returned in the nval paramter.
 *
 * NOTE: The RCSwitch protocol transmits each word multiple times in an attempt to overcome any 
         interference. receiveNext() tries to find the next word by ignoring any values that match 
         the current value. This works most of the time but it is possible for the same value to be 
         transmitted in consecutive words on rare occasion. I'm just going to consider this an 
         acceptable loss for now and move on but I may want to revisit this issue at some point.
 */
bool MinionRadio::receiveNext(word24 pval, word24& nval) {
   time_t time_limit = now() + RECV_NEXT_TIMEOUT
   while (now() < time_limit) {
      if (rcsw->available()) {
         word24 v = receiveWord();
         if (v == pval) continue;
         nval = v;
         return true;
      }
   }
   return false;
}

/**
 * Send a word specified by three byte  values
 * NOTE: because RCSwitch does not send zero, 1 is added to the specified value which 
 *       must be subtraced by the receiver.
 */
void MinionRadio::sendWord(byte b0, byte b1, byte b2) {
   Word24 w24;
   w24.b[0] = b0;
   w24.b[1] = b1;
   w24.b[2] = b2;
   sendWord(w24.w);
}

/**
 * Send a word value.
 * NOTE: because RCSwitch does not send zero, 1 is added to the specified value which 
 *       must be subtraced by the receiver.
 */
void MinionRadio::sendWord(word24 w) {
   if (w >= 0xFFFFFF) {
      Serial.print("MinionRadio::sendWord(w): ");
      Serial.print(w);
      Serial.print(" equals or exceeds max 24-bit value of 16777215.");
      return;
   }
   rcsw->send(w+1, 24);
}

/**
 * Receive a word value.
 * NOTE: because RCSwitch does not send zero, 1 is subtracted from the received value which was added 
 *       by the sender.
 */
word24 MinionRadio::receiveWord() {
   w = rcsw->getReceivedValue() - 1;
   
}


