/*************************************
 * MinionRadioMessage.h
 * Author: Ron Smith
 * Created: 10/19/2014
 * Copyright 2014, That Aint Working
 *************************************/


union MinionMessageData {
    long d;
    word w[2];
    byte b[4];
};


struct MinionRadioMessage {
    byte messageType;       // 1-100 universal messages, 101-255 minion type specific messages. Never 0.
    byte minionId;          // 1 master, 2-250 assigned, 251-255 temp IDs.
    word minionType;        // 1-65535 maps to a custom controller/driver on the master.
    MinionMessageData data; // structure and content depends on messageType and minionType.
    word year;              // 4-digit year
    byte month;             // 1-12
    byte day;               // 1-31
    byte hour;              // 0-23
    byte minute;            // 0-59
    byte second;            // 0-59
    byte checksum;          // 0-255
 };

