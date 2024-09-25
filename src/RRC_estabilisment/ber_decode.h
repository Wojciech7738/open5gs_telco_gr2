#ifndef BER_DECODE_H
#define BER_DECODE_H

#include "RRCSetupRequest.h"
#include "tag.h"
#include "MessageType.h"

MessageData_t* ber_decode(uint8_t *buffer);
MessageData_t* ber_decode_RRCSetupRequest_Message(uint8_t *buffer);
int ber_decode_RRCSetupRequest(const uint8_t* encoded_data, RRCSetupRequest_t* RRCSetupRequest);
int ber_decode_RRCSetupRequestIEs(const uint8_t* encoded_data, int length, RRCSetupRequest_IEs_t* rrcSetupRequest_IEs);
int ber_decode_initial_ue_identity(const uint8_t* encoded_data, int length, InitialUE_Identity_t* initialUE_Identity);
int ber_decode_bit_string(const uint8_t* encoded_data, int length, BIT_STRING_t *bit_string);
int ber_decode_bit_octet(const uint8_t* encoded_data, int length, OCTET_STRING_t *oc);
int ber_decode_cause(const uint8_t* encoded_data, int length, EstablishmentCause_t* est);
#endif