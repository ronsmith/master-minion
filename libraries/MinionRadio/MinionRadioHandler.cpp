/*************************************
 * MinionRadioHandler.cpp
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadioHandler.h"

/**
 *
 */
int MinionRadioHandler::setup(int sendPin, int recvInt, byte id=0) {
    Serial.println("Setup: minion radio handler.");   
    minionId = id;   
    radio.setSendPin(sendPin);
    radio.setRecvInt(recvInt);
    randomSeed(analogRead(0));
    return radio.enable();
}

/**
 *
 */
void MinionRadioHandler::handle() {
    Word24* req = getRadio().receive();
    if (req != NULL) {
        MinionRadioMessage msg(req);
        if (msg.minionId == minionId || msg.minionId == MinionRadio::BROADCAST_ID) {
            switch (msg.msgType) {
                case MinionRadio::NEW_MINION_REQ:
                    newMinionRequest(msg);
                    break;
                case MinionRadio::UPD_MINION_ID_REQ:
                    updateMinionIdRequest(msg);
                    break;
                case MinionRadio::PING_REQ:
                    pingRequest(msg);
                    break;
                case MinionRadio::INFO_REQ:
                    infoRequest(msg);
                    break;
                case MinionRadio::TURN_OFF_REQ:
                    turnOffRequest(msg);
                    break;
                case MinionRadio::TURN_ON_REQ:
                    turnOnRequest(msg);
                    break;
                case MinionRadio::STATUS_REQ:
                    statusRequest(msg);
                    break;
                case MinionRadio::SET_OFF_TIME_REQ:
                    scheduleOffTimeRequest(msg);
                    break;
                case MinionRadio::SET_ON_TIME_REQ:
                    scheduleOnTimeRequest(msg);
                    break;
                case MinionRadio::CLR_SCHED_TIME_REQ:
                    clearScheduledTimesRequest(msg);
                    break;
                default:
                    Serial.print("Received: unknown message type ");
                    Serial.println((word24)msg.msgType);
                    break;
            }
        }
        delete req;
    }      
}

/**
 *
 */
void MinionRadioHandler::newMinionRequest(MinionRadioMessage& msg) {
    Serial.println("Received: new minion request.");
    if (minionId > 0 && minionId < 201) return;  // we have an assigned minionId so we are not a new minion
    minionId = getTempMinionId();
    delayRandomInterval();
    
}

/**
 *
 */
void MinionRadioHandler::updateMinionIdRequest(MinionRadioMessage& msg) {
    Serial.println("Received: update minion id request.");
    //TODO
}

/**
 *
 */
void MinionRadioHandler::pingRequest(MinionRadioMessage& msg) {
    Serial.println("Received: ping request.");
    //TODO
}

/**
 *
 */
void MinionRadioHandler::infoRequest(MinionRadioMessage& msg) {
    Serial.println("Received: info request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::turnOffRequest(MinionRadioMessage& msg) {
    Serial.println("Received: turn off request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::turnOnRequest(MinionRadioMessage& msg) {
    Serial.println("Received: turn on request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::statusRequest(MinionRadioMessage& msg) {
    Serial.println("Received: status request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::scheduleOffTimeRequest(MinionRadioMessage& msg) {
    Serial.println("Received: schedule off time request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::scheduleOnTimeRequest(MinionRadioMessage& msg) {
    Serial.println("Received: schedule on time request.");
    // subclass should do the rest
}

/**
 *
 */
void MinionRadioHandler::clearScheduledTimesRequest(MinionRadioMessage& msg) {
    Serial.println("Received: clear scheduled times request.");
    // subclass should do the rest
}

/**
 *
 */
byte MinionRadioHandler::getTempMinionId() {
    return (byte)random(201, 255);
}

/**
 *
 */
void MinionRadioHandler::delayRandomInterval(unsigned int minInterval=1, unsigned int maxInterval=1000) {
    return random(minInterval, maxInterval);
}


/**
 *
 */
int MinionRadioHandler::send(byte id, byte msgType, byte ex0, byte ex1, byte ex2) {
    return getRadio().send(id, msgType, ex0, ex1, ex2);
}

/**
 *
 */
int MinionRadioHandler::send(byte id, byte msgType, word24 extraData) {
    return getRadio().send(id, msgType, extraData);
}


