#include "nas-path.h"
#include "ogs-log.h"

// Function to send Security Mode Command to UE
void send_security_mode_command(amf_ue_t *amf_ue) {
    // Step 1: Send Security Mode Command using nas_5gs_send_security_mode_command
    if (nas_5gs_send_security_mode_command(amf_ue) != 0) {
        ogs_log_err("Failed to send Security Mode Command.");
    } else {
        ogs_log_info("Successfully sent Security Mode Command.");
    }
}


// Function to send Identity Request to UE
void send_identity_request(amf_ue_t *amf_ue) {
    // Step 1: Send Identity Request message using nas_5gs_send_identity_request
    if (nas_5gs_send_identity_request(amf_ue) != 0) {
        ogs_log_err("Failed to send Identity Request message.");
    } else {
        ogs_log_info("Successfully sent Identity Request message.");
    }
}