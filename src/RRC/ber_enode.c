#include "ber_encode.h"

uint8_t* ber_encode_RRCSetupRequest(RRCSetupRequest_t* RRCSetupRequest,int *encoded_len){
    int len = 0;
    uint8_t* encoded_data = ber_encode_RRCSetupRequestIEs(&RRCSetupRequest->rrcSetupRequest, &len);
     if (!encoded_data) {
        return NULL;
    }
    uint8_t *final_data = (uint8_t *)malloc(len+2);
     if (!final_data) {
        return NULL;
    }
    final_data[0] = RRC_SETUP_REQUEST_TAG; 
    final_data[1] = len;  
    memcpy(final_data + 2, encoded_data, len);
    free(encoded_data);
    *encoded_len = len+2;
    return final_data;

}

uint8_t* ber_encode_RRCSetupRequestIEs(RRCSetupRequest_IEs_t* RRCSetupRequest_IEs, int *encoded_len){
    uint8_t *encoded_data0 = NULL;
    uint8_t *encoded_data1 = NULL;
    int len0 = 0;
    int len1 = 0;
    int total_len = 0;

    encoded_data0 = ber_encode_initial_ue_identity(&RRCSetupRequest_IEs->ue_Identity, &len0);
    if (!encoded_data0) {
        return NULL;
    }
    total_len += len0;
    
    encoded_data1 = ber_encode_cause(&RRCSetupRequest_IEs->establishmentCause, &len1);
    
    if (!encoded_data1) {
        free(encoded_data0); 
        return NULL;
    }
    total_len += len1 ;

    uint8_t *final_data = (uint8_t *)malloc(total_len+2);
    if(final_data){
        final_data[0] = RRC_SETUP_REQUEST_IEs_TAG;
        final_data[1] = total_len; //buffer size
        memcpy(final_data + 2, encoded_data0, len0);
        memcpy(final_data + len0 + 2, encoded_data1, len1);
        free(encoded_data0);
        free(encoded_data1);
        *encoded_len = total_len+2;
        return final_data;
    }
   return NULL;
   

}

uint8_t* ber_encode_bit_string(BIT_STRING_t *bit_string, int *encoded_len) {
    int total_len = bit_string->size + 3;  //type+lenght+size+unused
    uint8_t *encoded_data = (uint8_t*) malloc(total_len);

    if (!encoded_data) {
        return NULL;
    }

    encoded_data[0] = BIT_STRING_TAG;
    encoded_data[1] = bit_string->size; 
    encoded_data[2] = bit_string->bits_unused;

    memcpy(encoded_data + 3, bit_string->buf, bit_string->size);

    *encoded_len = total_len;
    return encoded_data;
}


uint8_t* ber_encode_bit_octet(OCTET_STRING_t *octet_string, int *encoded_len) {
    int total_len = 2 + octet_string->size;  //type+lenght+size+unused
    uint8_t *encoded_data = (uint8_t*) malloc(total_len);

    if (!encoded_data) {
        return NULL;
    }

    encoded_data[0] = OCTET_STRING_TAG;
    encoded_data[1] = octet_string->size;
    memcpy(encoded_data + 2, octet_string->buf, octet_string->size);

    *encoded_len = total_len;
    return encoded_data;
}

uint8_t* ber_encode_initial_ue_identity(InitialUE_Identity_t *identity, int *encoded_len) {
    uint8_t *encoded_data = NULL;
    int len = 0;
    int total_len = 0;

    switch (identity->present) {
        case InitialUE_Identity_PR_ng_5G_S_TMSI_Part1:
            
            encoded_data = ber_encode_bit_string(&identity->choice.ng_5G_S_TMSI_Part1, &len);
            if (encoded_data) {
                total_len = len + 2; 
                uint8_t *final_data = (uint8_t *)malloc(total_len);
                if (final_data) {
                    final_data[0] = NG_5G_S_TMSI_Part1_TAG; 
                    final_data[1] = len;   
                    memcpy(final_data + 2, encoded_data, len);
                    free(encoded_data);
                    *encoded_len = total_len;
                    return final_data;
                }
                free(encoded_data);
            }
            break;

        case InitialUE_Identity_PR_randomValue:
            
            encoded_data = ber_encode_bit_string(&identity->choice.randomValue, &len);
            if (encoded_data) {
                total_len = len + 2;
                uint8_t *final_data = (uint8_t *)malloc(total_len);
                if (final_data) {
                    final_data[0] = RANDOM_VALUE_TAG;// Tag for randomValue
                    final_data[1] = len;   // Length of the encoded BIT STRING
                    memcpy(final_data + 2, encoded_data, len);
                    free(encoded_data);
                    *encoded_len = total_len;
                    return final_data;
                }
                free(encoded_data);
            }
            break;

        case InitialUE_Identity_PR_NOTHING:
            // No components present, return NULL
            *encoded_len = 0;
            return NULL;

        default:
            // Unknown type
            *encoded_len = 0;
            return NULL;
    }

    *encoded_len = 0;
    return NULL;
}


uint8_t *ber_encode_cause(EstablishmentCause_t* cause, int* len){
    OCTET_STRING_t oc;
    oc.size = sizeof(EstablishmentCause_t);
    oc.buf = malloc(oc.size);
    memcpy(oc.buf,cause,oc.size);

    uint8_t* buffer = ber_encode_bit_octet(&oc,len);

    free(oc.buf);
    return buffer;

}