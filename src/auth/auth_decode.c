#include "authentication_messages.h"
#include "../RRC_estabilisment/DedicatedNAS-Message.h"


// Function to unpack DedicatedNAS_Message_t into AuthenticationRequest
int unpack_authentication_request(DedicatedNAS_Message_t *nas_message, struct AuthenticationRequest *auth_req) {
    if (nas_message->size < sizeof(auth_req->ngKSI) + sizeof(auth_req->ABBA) + sizeof(auth_req->eap_req.eap_code)
                           + sizeof(auth_req->eap_req.identifier) + sizeof(auth_req->eap_req.length)
                           + sizeof(auth_req->eap_req.eap_type) + sizeof(auth_req->eap_req.challenge)) {
        return -1;
    }

    int offset = 0;
    // ngKSI
    memcpy(&auth_req->ngKSI, nas_message->buf + offset, sizeof(auth_req->ngKSI));
    offset += sizeof(auth_req->ngKSI);
    // ABBA
    memcpy(&auth_req->ABBA, nas_message->buf + offset, sizeof(auth_req->ABBA));
    offset += sizeof(auth_req->ABBA);
    // EAP_Request 
    memcpy(&auth_req->eap_req.eap_code, nas_message->buf + offset, sizeof(auth_req->eap_req.eap_code));
    offset += sizeof(auth_req->eap_req.eap_code);
    memcpy(&auth_req->eap_req.identifier, nas_message->buf + offset, sizeof(auth_req->eap_req.identifier));
    offset += sizeof(auth_req->eap_req.identifier);
    memcpy(&auth_req->eap_req.length, nas_message->buf + offset, sizeof(auth_req->eap_req.length));
    offset += sizeof(auth_req->eap_req.length);
    memcpy(&auth_req->eap_req.eap_type, nas_message->buf + offset, sizeof(auth_req->eap_req.eap_type));
    offset += sizeof(auth_req->eap_req.eap_type);
    memcpy(&auth_req->eap_req.challenge, nas_message->buf + offset, sizeof(auth_req->eap_req.challenge));
    offset += sizeof(auth_req->eap_req.challenge);
    return 0;
}

// Function to unpack DedicatedNAS_Message_t into AuthenticationResponse
int unpack_authentication_response(DedicatedNAS_Message_t *nas_message, struct AuthenticationResponse *auth_res) {
    if (nas_message->size < sizeof(auth_res->ngKSI) + sizeof(auth_res->eap_res.eap_code)
                           + sizeof(auth_res->eap_res.identifier) + sizeof(auth_res->eap_res.length)
                           + sizeof(auth_res->eap_res.eap_type) + sizeof(auth_res->eap_res.response)) {
        return -1;
    }

    int offset = 0;
    // ngKSI
    memcpy(&auth_res->ngKSI, nas_message->buf + offset, sizeof(auth_res->ngKSI));
    offset += sizeof(auth_res->ngKSI);
    // EAP_Response
    memcpy(&auth_res->eap_res.eap_code, nas_message->buf + offset, sizeof(auth_res->eap_res.eap_code));
    offset += sizeof(auth_res->eap_res.eap_code);
    memcpy(&auth_res->eap_res.identifier, nas_message->buf + offset, sizeof(auth_res->eap_res.identifier));
    offset += sizeof(auth_res->eap_res.identifier);
    memcpy(&auth_res->eap_res.length, nas_message->buf + offset, sizeof(auth_res->eap_res.length));
    offset += sizeof(auth_res->eap_res.length);
    memcpy(&auth_res->eap_res.eap_type, nas_message->buf + offset, sizeof(auth_res->eap_res.eap_type));
    offset += sizeof(auth_res->eap_res.eap_type);
    memcpy(&auth_res->eap_res.response, nas_message->buf + offset, sizeof(auth_res->eap_res.response));
    offset += sizeof(auth_res->eap_res.response);
    return 0;
}