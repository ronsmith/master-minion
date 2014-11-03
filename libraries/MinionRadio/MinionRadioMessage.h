/*************************************
 * MinionRadioMessage.h
 * Author: Ron Smith
 * Created: 10/19/2014
 * Copyright 2014, That Aint Working
 *************************************/

#ifndef MINIONRADIOMESSAGE_H
#define MINIONRADIOMESSAGE_H

union MinionRadioMessageData {
    long d;
    word w[2];
    byte b[4];
};


enum MinionRadioMessageType : byte {
	//Codes 1-100 reserved for universal message types.
	NEW_MINION_REQ     = 10,
	NEW_MINION_RESP    = 11,
	UPD_MINION_ID_REQ  = 12,
	INFO_REQ           = 15,
	TURN_OFF_REQ       = 20,
	TURN_ON_REQ        = 21,
	STATUS_REQ         = 25,
	STATUS_RESP        = 26,
	SET_OFF_TIME_REQ   = 30,
	SET_ON_TIME_REQ    = 31,
	CLR_SCHED_TIME_REQ = 35,
	PING_REQ           = 90,
	PONG_RESP          = 91,
	REPEAT_LAST        = 95,
	ACK_RESP           = 99,
	MAX_UNIVERSAL_TYPE = 100
	// Codes 101-255 are reserved for message unique to certain minion types.
};

enum MinionId : byte {
    BROADCAST_ID		= 0,	// special Minion ID reserved for broadcast messages
	MASTER_ID			= 1,
	MIN_ASSIGNED_ID		= 2,
	MAX_ASSIGNED_ID		= 250,
	MIN_TEMP_ID			= 251,
	MAX_TEMP_ID			= 255
};

struct MinionRadioMessage {
    byte messageType;       		// can't use the actua enum type because we need to allow for the non-universal messages.
    byte minionId;          		// 1 master, 2-250 assigned, 251-255 temp IDs.
    word minionType;        		// 1-65535 maps to a custom controller/driver on the master.
    MinionRadioMessageData data;   	// structure and content depends on messageType and minionType.
    word year;              		// 4-digit year
    byte month;             		// 1-12
    byte day;               		// 1-31
    byte hour;              		// 0-23
    byte minute;            		// 0-59
    byte second;            		// 0-59
    byte checksum;          		// 0-255
	
	bool isBroadcast() { return (minionID == BROADCAST_ID); }
}; 


#endif /* end of include guard: MINIONRADIOMESSAGE_H */

