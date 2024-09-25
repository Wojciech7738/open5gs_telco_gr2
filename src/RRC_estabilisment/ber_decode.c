#include "ber_decode.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>

MessageData_t* ber_decode(uint8_t *buffer){
    uint8_t tag = buffer[0];

    switch (tag)
    {
    case RRC_SETUP_REQUEST_TAG:
        return ber_decode_RRCSetupRequest_Message(buffer);
        break;
    
    default:
        return NULL;
        break;
    };

}

MessageData_t* ber_decode_RRCSetupRequest_Message(uint8_t *buffer){
    MessageData_t* MessageData = malloc(sizeof(MessageData_t));
    memset(MessageData, 0, sizeof(MessageData_t));

    MessageData->present = MESSAGE_TYPE_RRC_SETUP_REQUEST;
    int len = ber_decode_RRCSetupRequest(buffer, &MessageData->choice.RRCSetupRequest);
 
    if(len==-1){
        return NULL;
    }

    return MessageData;

}
int ber_decode_RRCSetupRequest(const uint8_t* encoded_data, RRCSetupRequest_t* RRCSetupRequest) {
    
    if (encoded_data[0] != RRC_SETUP_REQUEST_TAG) {
        return -1; 
    }
    int data_length = encoded_data[1];

    int len = ber_decode_RRCSetupRequestIEs(encoded_data + 2, data_length, &RRCSetupRequest->rrcSetupRequest);

    
    if(len != data_length)
        return -1;
    
    if(len == -1)
        return len;
        
    return len+2; //tag+size
}


int ber_decode_RRCSetupRequestIEs(const uint8_t* encoded_data, int length, RRCSetupRequest_IEs_t* rrcSetupRequest_IEs){
    int len = 0;
    int len2 = 0;

    if (length < 2) {
        
        return -1;
    }
    if (encoded_data[0] != RRC_SETUP_REQUEST_IEs_TAG) {
        return -1; 
    }

    int data_length = encoded_data[1];
    if (data_length != length - 2) {
        return -1; 
    }
    len = ber_decode_initial_ue_identity(encoded_data+2, data_length, &rrcSetupRequest_IEs->ue_Identity);

    if(len==-1)
        return -1;

    const uint8_t* remaining_data = encoded_data + 2 + len; //dlaczego +1;
    int remaining_length = data_length - len;

    
    len2 = ber_decode_cause(remaining_data,remaining_length,&rrcSetupRequest_IEs->establishmentCause);

   
    if(len2==-1)
        return -1;

    return len + len2 + 2 ; //tag+size

}

int ber_decode_initial_ue_identity(const uint8_t* encoded_data, int length, InitialUE_Identity_t* initialUE_Identity){
     if (length < 2) {
        
        return -1;
    }
    if (encoded_data[0] != RANDOM_VALUE_TAG && encoded_data[0] != NG_5G_S_TMSI_Part1_TAG) {
        return -1; 
    }

    int len = encoded_data[1];
    if(len>length){
        return -1;
    }


    switch (encoded_data[0])
    {
    case RANDOM_VALUE_TAG:
        initialUE_Identity->present = InitialUE_Identity_PR_randomValue;
        len = ber_decode_bit_string(encoded_data+2,length,&initialUE_Identity->choice.randomValue);
        if(len==-1)
            return len;
        break;
    case NG_5G_S_TMSI_Part1_TAG:
        initialUE_Identity->present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
        len = ber_decode_bit_string(encoded_data+2,length,&initialUE_Identity->choice.ng_5G_S_TMSI_Part1);
        if(len==-1)
            return len;
        break;
    default:
        return -1;
        break;
    }

    return len + 2; //tag+size

}



int ber_decode_bit_string(const uint8_t* encoded_data, int length, BIT_STRING_t *bit_string){
    if (length < 2) {
        
        return -1;
    }
    if (encoded_data[0] != BIT_STRING_TAG) {
        return -1; 
    }

    bit_string->size = encoded_data[1];
    bit_string->bits_unused = encoded_data[2];
    bit_string->buf = malloc(sizeof(uint8_t)*bit_string->size);

    memcpy(bit_string->buf, encoded_data + 3, bit_string->size);

    return encoded_data[1] + 3; //tag+size+unused
}

int ber_decode_bit_octet(const uint8_t* encoded_data, int length, OCTET_STRING_t *oc){
    if (length < 2) {
        
        return -1;
    }
    if (encoded_data[0] != OCTET_STRING_TAG) {
        return -1; 
    }
    oc->size = encoded_data[1];
    oc->buf = malloc(sizeof(uint8_t)*oc->size);
    memcpy(oc->buf, encoded_data + 2, oc->size);
    
    return encoded_data[1] + 2;
}

int ber_decode_cause(const uint8_t* encoded_data, int length, EstablishmentCause_t* est){
    OCTET_STRING_t oc;
    
    int len = ber_decode_bit_octet(encoded_data,length,&oc);

    if(len==-1){
        return len;
    }

    memcpy(est,oc.buf,oc.size); //todo
    free(oc.buf);

    return len;
}