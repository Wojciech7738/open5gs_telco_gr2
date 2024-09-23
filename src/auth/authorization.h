#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include "common.h"

void send_authorization_request_to_pcf(amf_ue_t *amf_ue);
void send_slice_authorization_request_to_nssf(amf_ue_t *amf_ue, const char *slice_id);
void handle_slice_authorization_response_from_nssf(amf_ue_t *amf_ue, ogs_pkbuf_t *response);

#endif
