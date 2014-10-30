/*************************************
 * MinionRadio.cpp
 * Author: Ron Smith
 * Created: 10/12/2014
 * Copyright 2014, That Aint Working
 *************************************/

#include "MinionRadio.h"
#include <Time.h>


/**
 *
 */
MinionRadio::MinionRadio(int sendPin=-1, int recvPin=-1, unsigned long zeroPulse=4, unsigned long onePulse=8, unsigned long leadPulse=12, bool isMaster=false) :
    sendPin(sendPin), 
	recvPin(recvPin),
	zeroPulse(zeroPulse), 
	onePulse(onePulse), 
	leadPulse(leadPulse), 
	master(isMaster), 
	enabled(false),
{ }

/**
 *
 */
MinionRadio::~MinionRadio() { 
	// nothing to see here
}

/** 
 * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions) 
 */
int MinionRadio::enable() {
	if (sendPin < 0 || recvPin < 0 || zeroPulse < 2 || onePulse < 2 || zeroPulse == onePulse || leadPulse <= zeroPulse || leadPulse <= onePulse) 
		return INVALID_CONFIG;
	pinMode(recvPin, INPUT);
	pinMode(sendPin, OUTPUT);
	digitalWrite(sendPin, LOW);
    enabled = true;
    return OK;
}

/** 
 * 
 */
void MinionRadio::disable() {
	enable = false;
}

/**
 * Send message using the specified values.
 * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
 */      
void MinionRadio::send(byte messageType, byte minionId, word minionType, MinionMessageData data) {
	if (!enabled) return;
	MinionRadioMessage msg;
    msg.messageType = messageType;
    msg.minionId 	= minionId;
    msg.minionType	= minionType;
    msg.data		= data;
    return send(msg);
}

/**
 * Send message using a partial message structure. Only the messageType, minionId, minionType 
 * and data are required. The rest will be overwritten by the send method anyway.
 * Returns 0 on success otherwise an error code (since arduino doesn't support exceptions)
 */      
void MinionRadio::send(MinionRadioMessage& msg) {
	if (!enabled) return;
	msg.year 	= year();
	msg.month	= month();
	mgs.day		= day();
	msg.hour	= hour()
	msg.minute	= minute();
	msg.second 	= second();
	msg.checksum = calcChecksum(msg);
	sendLeadIn();
	byte* bytes = &msg
	for (int by = 0; v < sizeof(msg); by++) {
		for (int bt = 0; bt < 8; bt++) {
			sendPulse(bitRead(bytes[by], bt) ? onePulse : zeroPulse);
		}
	}
	sendLeadOut();
}

/**
 *
 */
void MinionRadio::sendLeadIn() {
	int x;
	sendPulse(zeroPulse + onePulse);
	for (x = 0; x < 3; x++) {
		sendPulse(zeroPulse);
	}
	for (x = 0; x < 3; x++) {
		sendPulse(onePulse);
	}
	sendPulse(zeroPulse + onePulse);
}

/**
 *
 */
void MinionRadio::sendLeadOut() {
	for (int x = 0; x < 2; x++) {
		sendPulse(zeroPulse + onePulse);
	}
}

/**
 *
 */
void MinionRadio::sendPulse(unsigned long duration) {
	digitalWrite(sendPin, HIGH);
	delayMicroseconds(duration);
	digitalWrite(sendPin, LOW);
}

/** 
 * Returns NULL if no message or error reading message, 
 * otherwise the returned data structure MUST BE DELETED BY THE CALLER.
 */
MinionRadioMessage* MinionRadio::receive() {
	if (!enabled) return;
	unsigned int pulse;
	
	// LEAD-IN HEADER
	// When we first detect a message, we assume it is in the lead-in header but we don't know
	// much of the header pulse we might have missed so we ignore it's width and move on to the
	// calibration phase.
	pulse = waitForPulse(gapPulse);
	if (!pulse) 
		return NULL;
	
	// ZERO CALIBRATION
	// We expect to receive three zero pulses
	for (int x = 0; x < 3; x++) {
		pulse = waitForPulse();
		if (pulse < zeroPulse - 1 || pulse > zeroPulse + 1)
			return NULL;
	}
	
	// ONE CALIBRATION
	// We expect to receive three one pulses
	for (int x = 0; x < 3; x++) {
		pulse = waitForPulse();
		if (pulse < onePulse - 1 || pulse > onePulse + 1)
			return NULL;
	}
	
	// LEAD-IN TRAILER
	// The lead-in trailer should be zeeroPulse + onePulse
	pulse = waitForPulse();
	if (pulse < (zeroPulse + onePulse - 1) || pulse > (zeroPulse + onePulse + 1))
		return NULL;
	
	// MESSAGE
	// Finally get to read the message.
	MinionRadioMessage* msg = new MinionRadioMessage;
	byte* bytes = msg;
	for (int byteCount = 0; byteCount < sizeof(MinionRadioMessage); byteCount++) {
		for (int b = 0; b < 8; b++) {
			pulse = waitForPulse();
			if (pulse < zeroPulse - 1 || pulse > zeroPulse + 1) {
				bitClear(bytes[byteCount], b);
			} else if (pulse < onePulse - 1 || pulse > onePulse + 1) {
				bitSet(bytes[byteCount], b)
			} else {
				delete msg;
				return NULL;
			}
		}
	}
	
	// LEAD-OUT
	// Make sure we get this message termination sequence as a validation that we read the message properly.
	for (int x = 0; x < 2; x++) {
		pulse = waitForPulse();
		if (pulse < (zeroPulse + onePulse - 1) || pulse > (zeroPulse + onePulse + 1)) {
			delete msg;
			return NULL;
		}
	}
	
	return msg;
}

/**
 *
 */
unsigned long MinionRadio::waitForPulse(unsigned long waitTime=0) {
	return pulseIn(recvPin, HIGH, waitTime);
}
