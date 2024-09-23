#include "auth_request.h"

// Function to pack and send AuthenticationRequest using nas_5gs_send_authentication_request
void send_authentication_request(amf_ue_t *amf_ue, struct AuthenticationRequest *auth_req) {
    DedicatedNAS_Message_t nas_message;

    // Step 1: Pack the AuthenticationRequest into the NAS message
    if (pack_authentication_request(auth_req, &nas_message) != 0) {
        ogs_log_err("Failed to pack Authentication Request.");
        return;
    }

    // Step 2: Create a packet buffer for NAS message
    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(nas_message.buf, nas_message.size);
    if (!pkbuf) {
        ogs_log_err("Failed to allocate packet buffer for Authentication Request.");
        return;
    }

    // Step 3: Send the Authentication Request to the gNB using nas_5gs_send_to_gnb
    if (nas_5gs_send_to_gnb(amf_ue, pkbuf) != 0) {
        ogs_log_err("Failed to send Authentication Request to gNB.");
    }

    // Clean up
    ogs_pkbuf_free(pkbuf);
    free(nas_message.buf);
}
