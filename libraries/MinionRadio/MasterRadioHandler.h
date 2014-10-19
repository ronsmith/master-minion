/*************************************
 * MasterRadioHandler.h
 * Author: Ron Smith
 * Created: 10/19/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"


/**
 * This class is a base class for creating a minion.
 */
class MasterRadioHandler {

public:

    MasterRadioHandler() { }
    virtual ~MasterRadioHandler() { }
    
    MinionRadio& getRadio() { return radio; }

    virtual int setup(unsigned int sendPin, unsigned int recvInt, word typ, byte id=0);
    virtual void handle();

    /** 
     * Specific event handler methods are called when a particular message type is received. 
     * Overload these as needed.
     */
    virtual void newMinionResponse(MinionRadioMessage& msg);
    virtual void infoResponse(MinionRadioMessage& msg);
    virtual void statusResponse(MinionRadioMessage& msg);
    virtual void pingRequest(MinionRadioMessage& msg);
    virtual void pongResponse(MinionRadioMessage& msg;)
    virtual void resendLastRequest(MinionRadioMessage& msg);
    virtual void ackResponse(MinionRadioMessage& msg);
    virtual void otherMessageType
    
    int send(MinionRadioMessage& msg);
    int send(byte messageType, byte minionId, word minionType, MinionMessageData data)

private:

    MinionRadio radio;
};



