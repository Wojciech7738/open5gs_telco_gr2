#ifndef AUTH_DECODE_H
#define AUTH_DECODE_H

#include "authentication_messages.h"
#include "../RRC_estabilisment/DedicatedNAS-Message.h"

int unpack_authentication_request(DedicatedNAS_Message_t *nas_message, struct AuthenticationRequest *auth_req);
int unpack_authentication_response(DedicatedNAS_Message_t *nas_message, struct AuthenticationResponse *auth_res);

#endif