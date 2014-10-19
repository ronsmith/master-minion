/*************************************
 * MinionRadioHandler.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"


/**
 * This class is a base class for creating a minion.
 */
class MinionRadioHandler {

public:

    MinionRadioHandler(word typ=0, byte id=0) : minionType(typ), minionId(id) { }
    
    virtual ~MinionRadioHandler() { }
    
    word getMinionType() { return minionType; }
    void setMinionType(word typ) { minionType = typ; }

    byte getMinionId() { return minionId; }
    void setMinionId(byte id) { minionId = id; }

    MinionRadio& getRadio() { return radio; }

    virtual int setup(unsigned int sendPin, unsigned int recvInt, word typ, byte id=0);
    virtual void handle();

    /** 
     * Specific event handler methods are called when a particular message type is received. 
     * Overload these as needed.
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
    virtual void pongResponse(MinionRadioMessage& msg;)
    virtual void resendLastRequest(MinionRadioMessage& msg);
    virtual void otherMessageType
    
    int send(MinionRadioMessage& msg);
    int send(byte messageType, MinionMessageData data)

protected:

    byte getTempMinionId();
    void delayRandomInterval(unsigned int minInterval=1, unsigned int maxInterval=1000);

private:

    word minionType;
    byte minionId;
    MinionRadio radio;
};



