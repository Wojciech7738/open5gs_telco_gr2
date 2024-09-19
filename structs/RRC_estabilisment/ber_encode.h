#ifndef BER_ENCODE_H
#define BER_ENCODE_H

#include <stdint.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "RRCSetupRequest.h"

#include "tag.h"

uint8_t* ber_encode_RRCSetupRequest(RRCSetupRequest_t* RRCSetupRequest,int *encoded_len);
/*
uint8_t* ber_encode_RRCSetupRequestIEs(RRCSetupRequest_IEs_t* RRCSetupRequest_IEs, int *encoded_len);
uint8_t* ber_encode_bit_octet(OCTET_STRING_t *octet_string, int *encoded_len);
uint8_t* ber_encode_bit_string(BIT_STRING_t *bit_string, int *encoded_len);
uint8_t* ber_encode_initial_ue_identity(InitialUE_Identity_t *identity, int *encoded_len);
*/

#endif