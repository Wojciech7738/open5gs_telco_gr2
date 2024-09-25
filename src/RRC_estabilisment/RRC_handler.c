


#include "RRC_handler.h"
#include "RRCSetup.h"
#include "RRCReject.h"
#include "RRCSetupComplete.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

//powinno być na wątkach
int handle_RRC(ogs_pkbuf_t* pkbuf){
    MessageData_t* RRCMessage;
    RRCMessage = ber_decode(pkbuf->data);

    switch (RRCMessage->present)
    {
    case MESSAGE_TYPE_RRC_SETUP_REQUEST:
        return handleRRCSetupRequest(&RRCMessage->choice.RRCSetupRequest);
        break;
    case MESSAGE_TYPE_RRC_SETUP_COMPLETE:
        return handleRRCSetupComplete(&RRCMessage->choice.RRCSetupComplete);
        break;
    default:
        //uknown or invalid message
        break;
    }
    return 0;
}

int handleRRCSetupRequest(RRCSetupRequest_t* rrcSetupRequest){
    ogs_assert(rrcSetupRequest);
    InitialUE_Identity_t* UEid = &rrcSetupRequest->rrcSetupRequest.ue_Identity;
    ogs_assert(UEid);
    if(isUEIdleState(UEid)){

        if(!rrcEstablishConnection(UEid))
            return sendRRCReject(UEid);  //create and send RRCSetup
        else
            return sendRRCSetup(UEid);  //create and sedn RRCReject
    }       
    return 0; 
};


int sendRRCSetup(InitialUE_Identity_t* UEid){
    ogs_assert(UEid);
    RRCSetup_t rrcSetup;
    rrcSetup.rrc_TransactionIdentifier = getTransactionIdentifier();
    rrcSetup.criticalExtensions.present = RRCSetup__criticalExtensions_PR_rrcSetup;
    rrcSetup.criticalExtensions.choice.rrcSetup.radioBearerConfig = getSRB0config();
    rrcSetup.criticalExtensions.choice.rrcSetup.masterCellGroup = getMasterCellGroup();
    rrcSetup.criticalExtensions.choice.rrcSetup.lateNonCriticalExtension = NULL;
    rrcSetup.criticalExtensions.choice.rrcSetup.nonCriticalExtension = NULL;
    uint8_t* buffer = per_encode_RRCSetup(&rrcSetup);
    ogs_assert(buffer);
    int returnCode = sendtoUE(buffer,UEid);
    free(buffer);
    return returnCode;
    
}

int sendRRCReject(InitialUE_Identity_t* UEid){
    ogs_assert(UEid);
    RRCReject_t rrcReject;
    rrcReject.criticalExtensions.present = RRCReject__criticalExtensions_PR_rrcReject;
    rrcReject.criticalExtensions.choice.rrcReject.lateNonCriticalExtension = NULL;
    rrcReject.criticalExtensions.choice.rrcReject.nonCriticalExtension = NULL;
    rrcReject.criticalExtensions.choice.rrcReject.waitTime = getWaitTime();
    uint8_t* buffer = per_encode_RRCReject(&rrcReject);
    ogs_assert(buffer);
    int returnCode = sendtoUE(buffer,UEid);
    free(rrcReject.criticalExtensions.choice.rrcReject.waitTime);
    free(buffer);
    return returnCode;
    
}

int handleRRCSetupComplete(RRCSetupComplete_t* rrcSetupComplete){
    ogs_assert(rrcSetupComplete);
    RRCSetupComplete_IEs_t* rrc = &rrcSetupComplete->criticalExtensions.choice.rrcSetupComplete;
    updateUEconfig(rrc);
    ChangeRRCUEState(rrc->ng_5G_S_TMSI_Value, NR_RRC_CONNECTED);
    sendNASmessage(&rrc->dedicatedNAS_Message); 
    return 0;
}

int sendNASmessage(OCTET_STRING_t* NAS){
    ogs_assert(NAS);
    return 0;
}

int ChangeRRCUEState(RRCSetupComplete_IEs__ng_5G_S_TMSI_Value_t* ng_5G_S_TMSI_Value, int state){
 
    ogs_assert(ng_5G_S_TMSI_Value);
    return 0;
}

OCTET_STRING_t getMasterCellGroup(void){
    OCTET_STRING_t oc;
    oc.size = 0;
    oc.buf = NULL;
    return oc;
}

int isUEIdleState(InitialUE_Identity_t* ue){
    ogs_assert(ue);
    return 0;
}

int rrcEstablishConnection(InitialUE_Identity_t* ue){
    ogs_assert(ue);
    return 0;
}

RRC_TransactionIdentifier_t getTransactionIdentifier(void){
    return 0;
}

uint8_t* per_encode_RRCSetup(RRCSetup_t* rrcSetup){
    ogs_assert(rrcSetup);
    uint8_t* buffer = malloc(sizeof(uint8_t));
    //encoding 
    return buffer;
}

uint8_t* per_encode_RRCReject(RRCReject_t* rrcReject){
    ogs_assert(rrcReject);
    uint8_t* buffer = malloc(sizeof(uint8_t));
    //encoding
    return buffer;
}


int sendtoUE(uint8_t* buffer, InitialUE_Identity_t* ue){
    ogs_assert(ue);
    ogs_assert(buffer);

    //send function
    
    return 0;
}

RejectWaitTime_t* getWaitTime(void){
    RejectWaitTime_t* wt = malloc(sizeof(RejectWaitTime_t));
    return wt;
}

int updateUEconfig(RRCSetupComplete_IEs_t* rrc){
    return 0;
}

RadioBearerConfig_t getSRB0config(void){
    RadioBearerConfig_t RBconfig;
    RBconfig._asn_ctx.bytes_left = 1;
    return RBconfig;
}