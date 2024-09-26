#ifndef AUTHORIZATION_MESSAGES_H
#define AUTHORIZATION_MESSAGES_H

#include <inttypes.h>

struct AuthorizationResponse {
    char IMSI[16];               // International Mobile Subscriber Identity of the UE
    uint8_t AuthorizationStatus; // Status of the authorization (e.g., Authorized, Denied)
    char AllowedServices[64];    // List of allowed services the UE can access
    char AllowedSlices[64];      // List of network slices (S-NSSAI) the UE is authorized to use
    uint8_t QoS_Granted;         // Granted Quality of Service
    uint8_t SessionID;           // Session identifier to match with the request
};

struct AuthorizationRequest {
    char IMSI[16];               // International Mobile Subscriber Identity of the UE
    char S_NSSAI[16];            // Single-Network Slice Selection Assistance Information (if network slicing is involved)
    char ServiceType[32];        // The type of service or resource requested
    uint8_t QoS_Requirements;    // Quality of Service requirements requested by the UE
    uint8_t SessionID;           // Session identifier
};

struct PolicyControlRequest {
    char IMSI[16];               // International Mobile Subscriber Identity
    char RequestedServices[64];  // List of requested services by the UE
    char S_NSSAI[16];            // Network slice being requested (if applicable)
    uint8_t QoS_Requirements;    // Quality of Service requested
    uint8_t SessionID;           // Session identifier
};

struct PolicyControlResponse {
    char IMSI[16];               // International Mobile Subscriber Identity
    uint8_t AuthorizationStatus; // Authorization result (Authorized/Denied)
    char GrantedPolicies[64];    // List of granted policies for the UE
    uint8_t QoS_Granted;         // Quality of Service granted for the session
    char TrafficSteeringPolicy[64]; // Policy for traffic routing or steering
    uint8_t SessionID;           // Session identifier to match with the request
};

struct SliceAuthorizationRequest {
    char IMSI[16];               // International Mobile Subscriber Identity
    char S_NSSAI[16];            // Single-Network Slice Selection Assistance Information
    uint8_t QoS_Requirements;    // Quality of Service requested for the slice
    uint8_t SessionID;           // Session identifier
};

struct SliceAuthorizationResponse {
    char IMSI[16];               // International Mobile Subscriber Identity
    uint8_t SliceAuthorizationStatus; // Authorization result (Authorized/Denied for the specific slice)
    uint8_t QoS_Granted;         // Granted Quality of Service for the requested slice
    uint8_t SessionID;           // Session identifier to match with the request
};


#endif