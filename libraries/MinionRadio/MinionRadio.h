/*************************************
 * MinionRadio.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadioMessage.h"


class MinionRadio {
   
   public:
   
      MinionRadio(int sendPin=0, int recvInt=0, bool isMaster=false) :
                  sendPin(sendPin), recvInt(recvInt), masterFlag(isMaster) { }
                  
      ~MinionRadio() { }
      
      unsigned int getSendPin()         { return sendPin; }
      void setSendPin(unsigned int sp)  { sendPin = sp; }
      
      unsigned int getRecvInt()         { return recvInt; }
      void setRecvInt(unsigned int ri)  { recvInt = ri; }
            
      /** 
       * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions) 
       */
      int enable();      
      
      void disable();
      
      bool isEnabled()                  { return (rcsw != NULL); }
      
      bool isMaster()                   { return masterFlag; }
      
      /**
       * Send message using a partial message structure. Only the messageType, minionId, minionType 
       * and data are required. The rest will be overwritten by the send method anyway.
       * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
       */      
      int send(MinionRadioMessage& message);

      /**
       * Send message using the specified values.
       * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
       */      
      int send(byte messageType, byte minionId, word minionType, MinionMessageData data);

      /** 
       * Returns NULL if no message, otherwise the returned data structure be deleted by the caller
       */
      MinionRadioMessage* receive();
      
      /** Error Codes */
      static const int OK              =  0;  // success, not really an "error code" but, whatever
      static const int ALREADY_ENABLED = -1;  // tried to enable when already enabled
      static const int ENABLE_FAILED   = -2;  // usually an error creating RCSwitch
      static const int NOT_ENABLED     = -3;  // tried to send/receive before enable
      static const int NOT_CONFIGURED  = -4;  // can't enable without sendPin and recvInt being set
      
      /** 
       * Message Type Codes
       * Codes 1-100 reserved for universal message types.
       * Codes 101-255 are used for message unique to certain minion types.
       */
      static const byte NEW_MINION_REQ     = 10;
      static const byte NEW_MINION_RESP    = 11;
      static const byte UPD_MINION_ID_REQ  = 12;
      static const byte INFO_REQ           = 15;
      static const byte TURN_OFF_REQ       = 20;
      static const byte TURN_ON_REQ        = 21;
      static const byte STATUS_REQ         = 25;
      static const byte STATUS_RESP        = 26;
      static const byte SET_OFF_TIME_REQ   = 30;
      static const byte SET_ON_TIME_REQ    = 31;
      static const byte CLR_SCHED_TIME_REQ = 35;
      static const byte PING_REQ           = 90;
      static const byte PONG_RESP          = 91;
      static const byte REPEAT_LAST        = 95;
      static const byte ACK_RESP           = 99;
      
      /** special Minion ID reserved for broadcast messages */
      static const byte BROADCAST_ID       = 0;
      
   private:
   
      int sendPin;
      int recvInt;
      bool masterFlag;
};

