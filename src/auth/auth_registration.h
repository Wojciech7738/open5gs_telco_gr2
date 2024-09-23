#ifndef AUTH_REGISTRATION_H
#define AUTH_REGISTRATION_H

#include "amf/nas-path.h"
#include "nas/5gs/types.h"
#include "core/ogs-log.h"
#include "amf/event.h"

void send_registration_accept(amf_ue_t *amf_ue);
void send_registration_reject(ran_ue_t *ran_ue, amf_ue_t *amf_ue, ogs_nas_5gmm_cause_t gmm_cause);

#endif