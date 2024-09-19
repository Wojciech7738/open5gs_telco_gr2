#ifndef PDU_SESSION_EST_REJECT_H
#define PDU_SESSION_EST_REJECT_H

#include <stdint.h>

struct PDU_SESSION_EST_REJECT{
    uint8_t EPS;
    uint8_t pduSessionID;
    uint8_t PTI;
    uint8_t MessageType; 
    uint8_t cause5GSM;
};

#endif //PDU_SESSION_EST_REJECT_H