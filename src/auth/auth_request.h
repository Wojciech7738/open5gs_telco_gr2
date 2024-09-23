#ifndef AUTH_REQUEST_H
#define AUTH_REQUEST_H

#include "amf/nas-path.h"
#include "core/ogs-log.h"
#include "amf/event.h"
#include "RRC_estabilisment/DedicatedNAS-Message.h"

void send_authentication_request(amf_ue_t *amf_ue, struct AuthenticationRequest *auth_req);

#endif