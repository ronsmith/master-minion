/*************************************
 * MinionRadio.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include <RCSwitch.h>

#define word24 unsigned long
#define word16 word
      
union Word24 {
   word24 w:24;
   byte b[3];
   
};


class MinionRadio {
   
   public:
   
      MinionRadio(unsigned int sendPin=0, unsigned int recvInt=0, bool isMaster=false) : rcsw(NULL), sendPin(sendPin), recvInt(recvInt), masterFlag(isMaster) { }
      ~MinionRadio() { if (rcsw) delete rcsw; }
      
      unsigned int getSendPin() { return sendPin; }
      void setSendPin(unsigned int sp) { sendPin = sp; }
      
      unsigned int getRecvInt() { return recvInt; }
      void setRecvInt(unsigned int ri) { recvInt = ri; }
            
      // returns 0 on success otherwise an error code
      int enable();      
      
      void disable();
      
      bool isEnabled() { return (rcsw != NULL); }
      
      bool isMaster() { return masterFlag; }
      
      // send message
      // returns 0 on success otherwise an error code      
      int send(byte id, byte msgType, word24 extraData=0, word minionType);

      // send message
      // returns 0 on success otherwise an error code      
      int send(byte id, byte msgType, byte ex0, byte ex1, byte ex2, word minionType);

      // returns NULL if no message, otherwise an array of 4 Word24 unions which must be deleted by the caller
      Word24* receive();
      
      // Error Codes
      static const int OK              =  0;  // success, not really an "error code" but, whatever
      static const int ALREADY_ENABLED = -1;  // tried to enable when already enabled
      static const int ENABLE_FAILED   = -2;  // usually an error creating RCSwitch
      static const int NOT_ENABLED     = -3;  // tried to send/receive before enable
      static const int NOT_CONFIGURED  = -4;  // can't enable without sendPin and recvInt being set
      
      // Message Type Codes
      //   Codes above 99 are used for special messages for specific minion types.
      //   Codes 99 and below are reserved for specific universal message types.
      static const byte NEW_MINION_REQ     = 0x10;
      static const byte NEW_MINION_RESP    = 0x11;
      static const byte UPD_MINION_ID_REQ  = 0x12;
      static const byte INFO_REQ           = 0x15;
      static const byte TURN_OFF_REQ       = 0x20;
      static const byte TURN_ON_REQ        = 0x21;
      static const byte STATUS_REQ         = 0x25;
      static const byte STATUS_RESP        = 0x26;
      static const byte SET_OFF_TIME_REQ   = 0x30;
      static const byte SET_ON_TIME_REQ    = 0x31;
      static const byte CLR_SCHED_TIME_REQ = 0x35;
      static const byte PING_REQ           = 0x90;
      static const byte PONG_RESP          = 0x91;
      static const byte ACK_RESP           = 0x99;
      
      // every message startes with this signature byte
      static const byte MESSAGE_START      = 0x66;
      
      // special Minion ID reserved for broadcast messages
      static const byte BROADCAST_ID       = 0x00;
      
   private:
   
      word24 receiveNext(word24 curval);
      
      void sendWord(byte b0, byte b1, byte b2);
      void sendWord(word24 w);
      word24 receiveWord();
      byte calcCRC8(word24 w0, word24 w1, word24 w2)
      
      RCSwitch* rcsw;
      
      unsigned int sendPin;
      unsigned int recvInt;
      bool masterFlag;
};

