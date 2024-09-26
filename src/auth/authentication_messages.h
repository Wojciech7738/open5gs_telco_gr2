#ifndef AUTHENTICATION_MESSAGES_H
#define AUTHENTICATION_MESSAGES_H

#include <inttypes.h>

struct AuthenticationRequest {
    uint8_t ngKSI;              // NAS key set identifier (5G NAS key set)
    char ABBA[16];              // Access Network Identifier (ABBA: Authentication and Authorization Block A)
    struct EAP_Request eap_req; // Encapsulated EAP Request message (carrying authentication challenge)
};

struct EAP_Request {
    uint8_t eap_code;           // EAP Code (e.g., 1 for Request)
    uint8_t identifier;         // Identifier to match with the corresponding Response
    uint16_t length;            // Total length of the EAP message
    uint8_t eap_type;           // EAP Type (e.g., 23 for EAP-AKA)
    uint8_t challenge[32];      // The actual challenge data for authentication
};

struct AuthenticationResponse {
    uint8_t ngKSI;               // NAS key set identifier (5G NAS key set)
    struct EAP_Response eap_res; // Encapsulated EAP Response message (carrying the UE's authentication response)
};

struct EAP_Response {
    uint8_t eap_code;           // EAP Code (e.g., 2 for Response)
    uint8_t identifier;         // Identifier (matches the identifier from EAP_Request)
    uint16_t length;            // Total length of the EAP message
    uint8_t eap_type;           // EAP Type (e.g., 23 for EAP-AKA)
    uint8_t response[32];       // The calculated response from the UE based on the challenge
};

struct EAP_Success {
    uint8_t eap_code;           // EAP Code (e.g., 3 for Success)
    uint8_t identifier;         // Identifier (matches the previous messages)
    uint16_t length;            // Total length of the EAP message
};

struct EAP_Failure {
    uint8_t eap_code;           // EAP Code (e.g., 4 for Failure)
    uint8_t identifier;         // Identifier (matches the previous messages)
    uint16_t length;            // Total length of the EAP message
};

#endif