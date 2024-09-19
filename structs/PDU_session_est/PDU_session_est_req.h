#ifndef PDU_SESSION_ESTABLISHMENT_REQ_H
#define PDU_SESSION_ESTABLISHMENT_REQ_H

#include <stdint.h>

struct PDU_SESSION_ESTABLISHMENT_REQUEST{
    uint8_t EPS;
    uint8_t pduSessionID;
    uint8_t PTI;
    uint8_t MessageType;  //PDU SESSION EST REQ MESSASGE IDENTITY
    uint16_t IntegrityProtectionMAXDataRate;
    //optional
    uint8_t pduSessionType;
    uint8_t SSCMode;
    struct Capability5GSM capability5GSM;
    uint32_t MAXnumiOfSupportedPacketFilters :24;
    uint32_t AlwaysOnPDUSessionRequest: 8;
    //todo
};

struct Capability5GSM{
    uint8_t IEI;
    uint8_t lenght;
    uint8_t *buffor;
    uint8_t part;
};
#endif //PDU_SESSION_ESTABLISHMENT_REQ_H