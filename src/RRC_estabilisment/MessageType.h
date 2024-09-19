#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

#include "RRCReject.h"
#include "RRCSetup.h"
#include "RRCSetupComplete.h"
#include "RRCSetupRequest.h"

typedef enum MessageType_PR_e {
    MESSAGE_TYPE_UNKNOWN,
    MESSAGE_TYPE_RRC_SETUP_REQUEST,
    MESSAGE_TYPE_RRC_SETUP,
    MESSAGE_TYPE_RRC_SETUP_COMPLETE,
    MESSAGE_TYPE_RRC_REJECT
} MessageType_PR;

typedef struct MessageData_s {
    MessageType_PR present;
    union {
        RRCSetupRequest_t RRCSetupRequest;
        RRCSetup_t RRCSetup;
        RRCSetupComplete_t RRCSetupComplete;
        RRCReject_t RRCReject;
    } choice;
} MessageData_t;

#endif