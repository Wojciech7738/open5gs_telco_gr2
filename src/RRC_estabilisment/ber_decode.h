#ifndef BER_DECODE_H;
#define BER_DECODE_H

#include "RRCSetupRequest.h"
#include "tag.h"
#include "MessageType.h"

MessageData_t* ber_decode(uint8_t *buffer);


#endif