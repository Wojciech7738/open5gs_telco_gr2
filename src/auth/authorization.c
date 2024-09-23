#include "authorization.h"

// Function to send authorization request to PCF
void send_authorization_request_to_pcf(amf_ue_t *amf_ue) {
    ogs_log_info("Sending authorization request to PCF for UE: %s", amf_ue->supi);

    // Example authorization request: create a packet with policy data
    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(NULL, 0); // Placeholder for real policy data
    if (!pkbuf) {
        ogs_log_err("Failed to allocate packet buffer for Authorization Request.");
        return;
    }

    // Send the Authorization Request to PCF using send_to_pcf
    if (send_to_pcf(amf_ue, pkbuf) != 0) {
        ogs_log_err("Failed to send Authorization Request to PCF.");
    } else {
        ogs_log_info("Authorization Request successfully sent to PCF.");
    }

    ogs_pkbuf_free(pkbuf);
}

// Function to send slice authorization request to NSSF
void send_slice_authorization_request_to_nssf(amf_ue_t *amf_ue, const char *slice_id) {
    ogs_log_info("Sending slice authorization request to NSSF for UE: %s and slice: %s", amf_ue->supi, slice_id);

    // Example network slice request: create a packet with slice data
    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(NULL, 0); // Placeholder for real slice data
    if (!pkbuf) {
        ogs_log_err("Failed to allocate packet buffer for Slice Authorization Request.");
        return;
    }

    // Send the Slice Authorization Request to NSSF using send_to_nssf
    if (send_to_nssf(amf_ue, pkbuf, slice_id) != 0) {
        ogs_log_err("Failed to send Slice Authorization Request to NSSF.");
    } else {
        ogs_log_info("Slice Authorization Request successfully sent to NSSF.");
    }

    ogs_pkbuf_free(pkbuf);
}

// Function to handle slice authorization response from NSSF
void handle_slice_authorization_response_from_nssf(amf_ue_t *amf_ue, ogs_pkbuf_t *response) {
    ogs_log_info("Processing slice authorization response for UE: %s", amf_ue->supi);

    // Step 1: Process the NSSF response and extract slice access data
    if (process_nssf_response(response) != 0) {
        ogs_log_err("Failed to process NSSF response.");
        return;
    }

    // Step 2: Apply slice access policies for UE
    if (apply_slice_policy_to_ue(amf_ue) != 0) {
        ogs_log_err("Failed to apply slice policy to UE.");
        return;
    }
    ogs_log_info("Slice authorization successfully processed for UE: %s", amf_ue->supi);
}

