#ifndef AUTH_ENCODE_H
#define AUTH_ENCODE_H

#include "authentication_messages.h"
#include "../RRC_estabilisment/DedicatedNAS-Message.h"

int pack_authentication_response(struct AuthenticationResponse *auth_res, DedicatedNAS_Message_t *nas_message);
int pack_authentication_request(struct AuthenticationRequest *auth_req, DedicatedNAS_Message_t *nas_message);

#endif