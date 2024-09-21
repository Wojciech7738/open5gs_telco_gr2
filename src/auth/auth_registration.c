#include "nas-path.h"
#include "ogs-log.h"

// Function to send Registration Accept message to UE
void send_registration_accept(amf_ue_t *amf_ue) {
    // Step 1: Send Registration Accept message using nas_5gs_send_registration_accept
    if (nas_5gs_send_registration_accept(amf_ue) != 0) {
        ogs_log_err("Failed to send Registration Accept message.");
    } else {
        ogs_log_info("Successfully sent Registration Accept message.");
    }
}

// Function to send Registration Reject message to UE
void send_registration_reject(ran_ue_t *ran_ue, amf_ue_t *amf_ue, ogs_nas_5gmm_cause_t gmm_cause) {
    // Step 1: Send Registration Reject message using nas_5gs_send_registration_reject
    if (nas_5gs_send_registration_reject(ran_ue, amf_ue, gmm_cause) != 0) {
        ogs_log_err("Failed to send Registration Reject message.");
    } else {
        ogs_log_info("Successfully sent Registration Reject message.");
    }
}