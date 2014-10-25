/*************************************
 * MinionRadio.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#ifndef MINIONRADIO_H
#define MINIONRADIO_H


#include "MinionRadioMessage.h"


class MinionRadio {
   
    public:
   
        MinionRadio(int sendPin=-1, int recvPin=-1, unsigned long zeroPulse=4, unsigned long onePulse=8, unsigned long leadPulse=12, bool isMaster=false);
        ~MinionRadio();
      
        int getSendPin()           			{ return sendPin; }
        void setSendPin(int sp)    			{ if (!enabled) sendPin = sp; }
      
        int getRecvPin()           			{ return recvPin; }
        void setRecvPin(int rp)    			{ if (!enabled) recvPin = rp; }
		
        int getZeroPulse()        			{ return zeroPulse; }
        void setZeroPulse(int p)  			{ if (!enabled) zeroPulse = p; }
				
        int getOnePulse()        			{ return onePulse; }
        void setOnePulse(int p)  			{ if (!enabled) onePulse = p; }
            
        int getLeadPulse()        			{ return leadPulse; }
        void setLeadPulse(int p)  			{ if (!enabled) leadPulse = p; }
            
        bool isEnabled()                    { return enabled; }
        bool isMaster()                     { return master; }
      
        int enable();	// Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
        void disable();
      
        /**
         * Send message using the specified values.
         * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
         */      
        int send(byte messageType, byte minionId, word minionType, MinionMessageData data);

		/**
		 * Send message using a partial message structure. Only the messageType, minionId, minionType 
		 * and data are required. The rest will be overwritten by the send method anyway.
		 * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
		 */      
		int send(MinionRadioMessage& msg);

        /** 
         * Returns NULL if no message or error reading message, otherwise 
		 * the returned data structure MUST BE DELETED BY THE CALLER.
         */
        MinionRadioMessage* receive();
      
        /** Error Codes */
        static const int OK              =  0;  // success, not really an "error code" but, whatever
        static const int ALREADY_ENABLED = -1;  // tried to enable when already enabled
        static const int ENABLE_FAILED   = -2;  // couldn't set pin mode or interrupt handler
        static const int NOT_ENABLED     = -3;  // tried to send/receive before enable
        static const int INVALID_CONFIG  = -4;  // can't enable without sendPin, recvInt, shortPulse, and longPulse being set

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

		void sendLeadIn();
		void sendLeadOut();
		void sendPulse(unsigned long duration);
		unsigned long waitForPulse(unsigned long waitTime=0); // waitTime=0 means it doesn't time out
		
        int sendPin;				// pin for transmitting data
		int recvPin;				// pin for receiving data (should equate to the recvInt)
		
		unsigned long zeroPulse;	// duration of digital HIGH that will represent a zero bit
		unsigned long onePulse;		// duration of digital HIGH that will represent a one bit
		unsigned long headerPulse;	// duration of digital HIGH used for the lead-in/lead-out signal
				
        bool enabled;				// is the radio enabled?
        bool master;				// is this a master instead of a minion?
};



#endif /* end of include guard: MINIONRADIO_H */

