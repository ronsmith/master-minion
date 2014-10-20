/*************************************
 * MinionRadio.cpp
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"
#include <Time.h>

// Number of seconds to wait for next word in message. 
#define PULSE_INTERVAL 3;

/** 
* Returns 0 on success otherwise an error code (since arduino doesn't support exceptions) 
*/
int MinionRadio::enable() {
    
}

void MinionRadio::disable() {

}

/**
* Send message using a partial message structure. Only the messageType, minionId, minionType 
* and data are required. The rest will be overwritten by the send method anyway.
* Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
*/      
int MinionRadio::send(MinionRadioMessage& message) {

}

/**
* Send message using the specified values.
* Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
*/      
int MinionRadio::send(byte messageType, byte minionId, word minionType, MinionMessageData data) {

}

/** 
* Returns NULL if no message, otherwise the returned data structure be deleted by the caller
*/
MinionRadioMessage* MinionRadio::receive() {

}

