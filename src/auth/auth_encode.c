#include "auth_encode.h"

// Function to pack AuthenticationResponse into DedicatedNAS_Message_t
int pack_authentication_response(struct AuthenticationResponse *auth_res, DedicatedNAS_Message_t *nas_message) {
    // Calculate total size (ngKSI + EAP_Response)
    int total_size = sizeof(auth_res->ngKSI) + sizeof(auth_res->eap_res.eap_code)
                    + sizeof(auth_res->eap_res.identifier) + sizeof(auth_res->eap_res.length)
                    + sizeof(auth_res->eap_res.eap_type) + sizeof(auth_res->eap_res.response);
    
    // Allocate buffer
    nas_message->buf = (uint8_t *)malloc(total_size);
    if (!nas_message->buf) {
        return -1;
    }

    nas_message->size = total_size;
    // Serialize data into the buffer
    int offset = 0;
    // ngKSI
    memcpy(nas_message->buf + offset, &auth_res->ngKSI, sizeof(auth_res->ngKSI));
    offset += sizeof(auth_res->ngKSI);
    // EAP_Response
    memcpy(nas_message->buf + offset, &auth_res->eap_res.eap_code, sizeof(auth_res->eap_res.eap_code));
    offset += sizeof(auth_res->eap_res.eap_code);
    memcpy(nas_message->buf + offset, &auth_res->eap_res.identifier, sizeof(auth_res->eap_res.identifier));
    offset += sizeof(auth_res->eap_res.identifier);
    memcpy(nas_message->buf + offset, &auth_res->eap_res.length, sizeof(auth_res->eap_res.length));
    offset += sizeof(auth_res->eap_res.length);
    memcpy(nas_message->buf + offset, &auth_res->eap_res.eap_type, sizeof(auth_res->eap_res.eap_type));
    offset += sizeof(auth_res->eap_res.eap_type);
    memcpy(nas_message->buf + offset, &auth_res->eap_res.response, sizeof(auth_res->eap_res.response));
    offset += sizeof(auth_res->eap_res.response);
    return 0;
}


// Function to pack AuthenticationRequest into DedicatedNAS_Message_t
int pack_authentication_request(struct AuthenticationRequest *auth_req, DedicatedNAS_Message_t *nas_message) {
    // Calculate total size (ngKSI + ABBA + EAP_Request)
    int total_size = sizeof(auth_req->ngKSI) + sizeof(auth_req->ABBA) + sizeof(auth_req->eap_req.eap_code)
                    + sizeof(auth_req->eap_req.identifier) + sizeof(auth_req->eap_req.length)
                    + sizeof(auth_req->eap_req.eap_type) + sizeof(auth_req->eap_req.challenge);
    
    // Allocate buffer
    nas_message->buf = (uint8_t *)malloc(total_size);
    if (!nas_message->buf) {
        return -1;
    }

    nas_message->size = total_size;
    int offset = 0;
    // ngKSI
    memcpy(nas_message->buf + offset, &auth_req->ngKSI, sizeof(auth_req->ngKSI));
    offset += sizeof(auth_req->ngKSI);
    // ABBA
    memcpy(nas_message->buf + offset, &auth_req->ABBA, sizeof(auth_req->ABBA));
    offset += sizeof(auth_req->ABBA);
    // EAP_Request
    memcpy(nas_message->buf + offset, &auth_req->eap_req.eap_code, sizeof(auth_req->eap_req.eap_code));
    offset += sizeof(auth_req->eap_req.eap_code);
    memcpy(nas_message->buf + offset, &auth_req->eap_req.identifier, sizeof(auth_req->eap_req.identifier));
    offset += sizeof(auth_req->eap_req.identifier);
    memcpy(nas_message->buf + offset, &auth_req->eap_req.length, sizeof(auth_req->eap_req.length));
    offset += sizeof(auth_req->eap_req.length);
    memcpy(nas_message->buf + offset, &auth_req->eap_req.eap_type, sizeof(auth_req->eap_req.eap_type));
    offset += sizeof(auth_req->eap_req.eap_type);
    memcpy(nas_message->buf + offset, &auth_req->eap_req.challenge, sizeof(auth_req->eap_req.challenge));
    offset += sizeof(auth_req->eap_req.challenge);
    return 0;
}