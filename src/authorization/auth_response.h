#ifndef AUTH_RESPONSE_H
#define AUTH_RESPONSE_H

#include "amf/nas-path.h"
#include "core/ogs-log.h"
#include "core/ogs-pkbuf.h"
#include "amf/event.h"
#include "RRC_estabilisment/DedicatedNAS-Message.h"
#include "auth_decode.h"
#include "l3_modules.h"

size_t get_message_length(uint8_t* message);
void receive_NAS_message(uint8_t* nas_message);
void send_NAS_message(uint8_t* nas_message, int nas_message_len);


#endif