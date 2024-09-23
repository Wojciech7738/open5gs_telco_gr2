#ifndef AUTH_SECURITY_H
#define AUTH_SECURITY_H

#include "amf/nas-path.h"
#include "core/ogs-log.h"
#include "amf/event.h"

void send_security_mode_command(amf_ue_t *amf_ue);
void send_identity_request(amf_ue_t *amf_ue);

#endif