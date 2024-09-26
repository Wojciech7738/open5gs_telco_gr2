#ifndef AUTH_DEREGISTRATION_H
#define AUTH_DEREGISTRATION_H

#include "amf/nas-path.h"
#include "core/ogs-log.h"
#include "deregistration_reason.h"
#include "amf/event.h"
#include "nas/5gs/types.h"

void send_deregistration_request(amf_ue_t *amf_ue, OpenAPI_deregistration_reason_e dereg_reason, ogs_nas_5gmm_cause_t gmm_cause);

#endif