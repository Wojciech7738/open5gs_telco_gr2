#include "nas-path.h"
#include "ogs-log.h"

// Function to handle receiving AuthenticationResponse from RLC/MAC and send to AMF
void handle_receive_authentication_response(amf_ue_t *amf_ue, uint8_t *mac_message, int message_length) {
    // Step 1: Reassemble the message if it's fragmented (RLC)
    uint8_t *rlc_reassembled_message;
    int rlc_reassembled_length;

    rlc_reassembled_message = rlc_reassemble(mac_message, message_length, &rlc_reassembled_length);
    if (!rlc_reassembled_message) {
        ogs_log_err("Failed to reassemble RLC message.");
        return;
    }

    // Step 2: Check if the message is a NAS message
    if (is_nas_message(rlc_reassembled_message)) {
        DedicatedNAS_Message_t nas_message;
        nas_message.buf = rlc_reassembled_message;
        nas_message.size = rlc_reassembled_length;

        // Step 3: Unpack the NAS message into AuthenticationResponse
        struct AuthenticationResponse auth_res;
        if (unpack_authentication_response(&nas_message, &auth_res) == 0) {
            ogs_log_info("Authentication Response unpacked successfully.");

            // Step 4: Process Authentication Response
            // Send it to the AMF for further processing using nas_5gs_send_to_gnb
            ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(nas_message.buf, nas_message.size);
            if (!pkbuf) {
                ogs_log_err("Failed to allocate packet buffer for Authentication Response.");
                return;
            }

            if (nas_5gs_send_to_gnb(amf_ue, pkbuf) != 0) {
                ogs_log_err("Failed to send Authentication Response to gNB.");
            }

            ogs_pkbuf_free(pkbuf);
        } else {
            ogs_log_err("Failed to unpack Authentication Response.");
        }
    }
}
