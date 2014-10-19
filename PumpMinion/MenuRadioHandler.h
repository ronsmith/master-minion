/*************************************
 * MinionRadioHandler.h
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"

struct MinionRadioMessage {
    MinionRadioMessage() { }
    MinionRadioMessage(Word24* req) : 
        minionId(req[0].b[1]),
        msgTyp(req[0].b[2]),
        date(req[1].w),
        year(req[1].b[0]),
        month(req[1].b[1]),
        year(req[1].b[2]),
        time(req[2].w),
        hour(req[2].b[0]),
        minute(req[2].b[1]),
        second(req[2].b[2]),
        extra(req[3].w),
        ex0(req[3].b[0]),
        ex1(req[3].b[1]),
        ex2(req[3].b[2])
    { }

    byte minionId;
    byte msgType;
    word24 date;
    byte year;
    byte month;
    byte day;
    word24 time;
    byte hour;
    byte minute;
    byte second;
    word24 extra;
    byte ex0;
    byte ex1;
    byte ex2;
    word minionType;
    byte crc8;
 };

class MinionRadioHandler {

public:

    MenuRadioHandler() : minionId(0) { }
    
    virtual ~MenuRadioHandler() { }

    byte getMinionId() { return minionId; }
    void setMinionId(byte id) { minionId = id; }
    
    word getMinionType() { return minionType; }
    void setMinionType(word mt) { minionType = mt; }

    MinionRadio& getRadio() { return radio; }

    virtual int setup(unsigned int sendPin, unsigned int recvInt, char id=0);
    virtual void handle();

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

protected:

    int send(byte msgType, byte ex0, byte ex1, byte ex2) { 
        return send(minionId, msgType, ex0, ex1, ex2); 
    }
    
    int send(byte msgType, word24 extraData) { 
        return send(minionId, msgType, extraData); 
    }

    int send(byte id, byte msgType, byte ex0, byte ex1, byte ex2);
    int send(byte id, byte msgType, word24 extraData);

    byte getTempMinionId();
    void delayRandomInterval(unsigned int minInterval=1, unsigned int maxInterval=1000);

private:

    MinionRadio radio;
    byte minionId;
    word minionType;
};



