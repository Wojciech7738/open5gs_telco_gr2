#ifndef PDU_SESSION_EST_ACCEPT_H
#define PDU_SESSION_EST_ACCEPT_H

#include <stdint.h>

struct PDU_SESSION_EST_ACCEPT{
    uint8_t EPS;
    uint8_t pduSessionID;
    uint8_t PTI;
    uint8_t MessageType; //PDU_SESSION_EST_ACCEPT
    uint8_t pduSessionType: 4;
    uint8_t SSCMode: 4;
    struct QosRules qosRules;
    uint64_t SessionAMBR: 56; //7octets
    //optional
    uint16_t cause5GSM;

};

struct QosRules{
    uint16_t length;  //2 octets
    uint8_t *buffor;
    uint8_t part;
}; 

#endif //PDU_SESSION_EST_ACCEPT_H