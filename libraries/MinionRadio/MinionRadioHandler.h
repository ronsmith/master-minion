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

    MinionRadioHandler() : minionType(0), minionId(0), radio(NULL) { }
    
    virtual ~MinionRadioHandler() 	{ }
    
    word getMinionType() 			{ return minionType; }
    byte getMinionId() 				{ return minionId; }
    MinionRadio* getRadio() 		{ return radio; }
	
    virtual int setup(word minionType, byte minionId, MinionRadio* radio);
	
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
    int send(byte messageType, MinionMessageData data)

protected:

    byte getTempMinionId();
    void delayRandomInterval(unsigned int minInterval=1, unsigned int maxInterval=1000);

private:

    word minionType;
    byte minionId;
    MinionRadio* radio;
};

#endif // end of include guard: MINIONRADIOHANDLER_H
