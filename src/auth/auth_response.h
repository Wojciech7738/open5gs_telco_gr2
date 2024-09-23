#ifndef AUTH_RESPONSE_H
#define AUTH_RESPONSE_H

#include "amf/nas-path.h"
#include "core/ogs-log.h"
#include "core/ogs-pkbuf.h"
#include "amf/event.h"
#include "RRC_estabilisment/DedicatedNAS-Message.h"
#include "auth_decode.h"

void handle_receive_authentication_response(amf_ue_t *amf_ue, uint8_t *mac_message, int message_length);

#endif