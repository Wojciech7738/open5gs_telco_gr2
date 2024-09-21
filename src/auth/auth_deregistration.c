#include "nas-path.h"
#include "ogs-log.h"

// Function to send De-registration Request to UE
void send_deregistration_request(amf_ue_t *amf_ue, OpenAPI_deregistration_reason_e dereg_reason, ogs_nas_5gmm_cause_t gmm_cause) {
    // Step 1: Send De-registration Request using nas_5gs_send_de_registration_request
    if (nas_5gs_send_de_registration_request(amf_ue, dereg_reason, gmm_cause) != 0) {
        ogs_log_err("Failed to send De-registration Request.");
    } else {
        ogs_log_info("Successfully sent De-registration Request.");
    }
}
