#ifndef COMMON_H
#define COMMON_H

#include "amf/nas-path.h"
#include "amf/event.h"
#include "core/ogs-pkbuf.h"
#include "core/ogs-sbi.h"
#include "core/ogs-log.h"

// Function declarations
int send_to_pcf(amf_ue_t *amf_ue, ogs_pkbuf_t *pkbuf);
int send_to_nssf(amf_ue_t *amf_ue, ogs_pkbuf_t *pkbuf, const char *slice_id);
int apply_slice_policy_to_ue(amf_ue_t *amf_ue, int flag);
int process_nssf_response(ogs_pkbuf_t *response);

#endif
