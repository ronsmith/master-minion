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
   
        MinionRadio(int sendPin=-1, int recvPin=-1, LONG zeroPulse=4, LONG onePulse=8, LONG leadPulse=12, bool isMaster=false);
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

        bool isMaster()                     { return master; }
		void setMaster(bool m)				{ if (!enabled) master = m; }
		
        int enable();	// Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
        void disable();
        bool isEnabled()                    { return enabled; }
      
        /**
         * Send message using the specified values.
         * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
         */      
        int send(BYTE messageType, BYTE minionId, WORD minionType, MinionRadioMessageData data);

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
      
        enum ErrorCode {
			OK =  0,  			// Success! Not really an "error code", but whatever
			ALREADY_ENABLED,  	// Tried to enable when already enabled
			ENABLE_FAILED,  	// Couldn't set pin mode or interrupt handler
			NOT_ENABLED,  		// Tried to send/receive before enable
			INVALID_CONFIG  	// Can't enable without sendPin, recvInt, shortPulse, and longPulse being set
		};

    private:

		void sendLeadIn();
		void sendLeadOut();
		void sendPulse(LONG duration);
		LONG waitForPulse(LONG waitTime=0); // waitTime=0 means it doesn't time out
		
        int sendPin;				// pin for transmitting data
		int recvPin;				// pin for receiving data (should equate to the recvInt)
		
		LONG zeroPulse;	// duration of digital HIGH that will represent a zero bit
        LONG onePulse;		// duration of digital HIGH that will represent a one bit
        LONG headerPulse;	// duration of digital HIGH used for the lead-in/lead-out signal
				
        bool enabled;				// is the radio enabled?
        bool master;				// is this a master instead of a minion?
};



#endif // end of include guard: MINIONRADIO_H

