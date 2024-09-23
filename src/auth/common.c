#include "common.h"

// Implementation of send_to_pcf, using ogs_sbi to send to PCF
int send_to_pcf(amf_ue_t *amf_ue, ogs_pkbuf_t *pkbuf) {
    ogs_log_info("Sending Authorization Request to PCF for UE: %s", amf_ue->supi);

    // Example of sending data to PCF using SBI (Service Based Interface)
    ogs_sbi_message_t *sbi_msg = ogs_sbi_message_new();
    ogs_assert(sbi_msg);

    // Prepare SBI message (this depends on the specifics of your PCF request)
    sbi_msg->h.service = "pcf";
    sbi_msg->h.operation = "POST";
    sbi_msg->h.resource = "/npcf/PolicyControlRequest";

    // Assuming pkbuf contains the payload data (e.g., policy request)
    sbi_msg->body = ogs_pkbuf_copy(pkbuf);

    // Send message to PCF
    int ret = ogs_sbi_send(sbi_msg, NULL);
    ogs_sbi_message_free(sbi_msg);

    return ret;
}

// Implementation of send_to_nssf for network slice authorization
int send_to_nssf(amf_ue_t *amf_ue, ogs_pkbuf_t *pkbuf, const char *slice_id) {
    ogs_log_info("Sending Slice Authorization Request to NSSF for UE: %s and slice: %s", amf_ue->supi, slice_id);

    // Example of sending data to NSSF using SBI (Service Based Interface)
    ogs_sbi_message_t *sbi_msg = ogs_sbi_message_new();
    ogs_assert(sbi_msg);

    // Prepare SBI message
    sbi_msg->h.service = "nssf";
    sbi_msg->h.operation = "POST";
    sbi_msg->h.resource = "/nnssf-nsselection/slice-selection";

    // Assuming pkbuf contains the payload data
    sbi_msg->body = ogs_pkbuf_copy(pkbuf);

    // Send message to NSSF
    int ret = ogs_sbi_send(sbi_msg, NULL);
    ogs_sbi_message_free(sbi_msg);

    return ret;
}

// Function to process NSSF response
int process_nssf_response(ogs_pkbuf_t *response) {
    ogs_log_info("Processing NSSF response");

    // Deserialize the response to extract NSSAI (Network Slice Selection Assistance Information)
    ogs_sbi_message_t *nssf_response = ogs_sbi_message_new();
    ogs_assert(nssf_response);

    int ret = ogs_sbi_parse_response(nssf_response, response);
    if (ret != OGS_OK) {
        ogs_log_err("Failed to parse NSSF response");
        ogs_sbi_message_free(nssf_response);
        return OGS_ERROR;
    }

    // Assuming the response contains Allowed NSSAI
    if (!nssf_response->body) {
        ogs_log_err("NSSF response has no body");
        ogs_sbi_message_free(nssf_response);
        return OGS_ERROR;
    }

    ogs_log_info("NSSF response processed successfully");
    ogs_sbi_message_free(nssf_response);
    return OGS_OK;
}


// Function to apply slice policy to UE based on NSSF response
int apply_slice_policy_to_ue(amf_ue_t *amf_ue, int flag) {
    ogs_log_info("Applying slice policy to UE: %s", amf_ue->supi);

    if (!amf_ue) {
        ogs_log_err("AMF UE context is null.");
        return -1;
    }

    // Set the UE to be authorized for a specific slice
    amf_ue->authorized_slice = flag;

    ogs_log_info("Successfully applied network slice policies for UE: %s", amf_ue->supi);

    return 0;
}
