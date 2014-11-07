/*************************************
 * MinionRadioHandler.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#ifndef MINIONRADIOHANDLER_H
#define MINIONRADIOHANDLER_H


#include "MinionRadio.h"


/**
 * This class is a base class for creating a minion.
 */
class MinionRadioHandler {

public:

    MinionRadioHandler() : minionType(0), minionId(0), radio(NULL) { randomSeed(analogRead(0)); }
    
    virtual ~MinionRadioHandler() 	{ }

    WORD getMinionType() 			{ return minionType; }

    BYTE getMinionId() 				{ return minionId; }
    MinionRadio* getRadio() 		{ return radio; }
	
    virtual int setup(MinionRadio* radio, WORD minionType, BYTE minionId=0);
	
	/**
	 * This is the "main loop" for monitoring the radio.
	 */
    virtual void handle();

    /** 
     * Specific event handler methods are called when a particular message type is received. 
     * They often provide some baseline functionality but you can overload these as needed, 
	 * just remember to call the base method.
     */
    virtual void newMinionRequest(MinionRadioMessage& msg);
    virtual void updateMinionIdRequest(MinionRadioMessage& msg);
    virtual void infoRequest(MinionRadioMessage& msg);
    virtual void turnOffRequest(MinionRadioMessage& msg);
    virtual void turnOnRequest(MinionRadioMessage& msg);
    virtual void statusRequest(MinionRadioMessage& msg);
    virtual void scheduleOffTimeRequest(MinionRadioMessage& msg);
    virtual void scheduleOnTimeRequest(MinionRadioMessage& msg);
    virtual void clearScheduledTimesRequest(MinionRadioMessage& msg);
    virtual void pingRequest(MinionRadioMessage& msg);
    virtual void pongResponse(MinionRadioMessage& msg);
    virtual void resendLastRequest(MinionRadioMessage& msg);
    virtual void otherMessage(MinionRadioMessage& msg);
    
    int send(MinionRadioMessage& msg);
    int send(BYTE messageType, MinionMessageData data)

private:

    WORD minionType;
    BYTE minionId;
    MinionRadio* radio;
};

#endif // end of include guard: MINIONRADIOHANDLER_H
