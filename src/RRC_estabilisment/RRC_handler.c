
#define NR_RRC_IDLE 0
#define NR_RRC_CONNECTED 1
#define NR_RRC_INACTIVE 2

#include "RRC_handler.h"
#include "RRCSetupComplete-IEs.h"

int handle_RRC(ogs_pkbuf_t* pkbuf){
    MessageData_t* RRCMessage;
    RRCMessage = ber_decode(pkbuf->data);

    switch (RRCMessage->present)
    {
    case MESSAGE_TYPE_RRC_SETUP_REQUEST:
        handleRRCSetupRequest(RRCMessage);
        break;
    case MESSAGE_TYPE_RRC_SETUP_COMPLETE:
        handleRRCSetupComplete(RRCMessage);
        break;
    default:
        //uknown or invalid message
        break;
    }
}

int handleRRCSetupRequest(MessageData_t* RRCMessage){
    InitialUE_Identity_t* UEid = &RRCMessage->choice.RRCSetupRequest.rrcSetupRequest.ue_Identity;
    if(isUEIdleState(UEid)){

        if(!RRCestablishConnection(UEid))
            sendRRCReject(UEid);  //create and send RRCSetup
        else
            sendRRCSetup(UEid);  //create and sedn RRCReject
    }        
};


int sendRRCSetup(InitialUE_Identity_t* UEid){
    
}

int sendRRCReject(InitialUE_Identity_t* UEid){
    
}

int handleRRCSetupComplete(MessageData_t* RRCMessage){
  
    RRCSetupComplete_IEs_t* rrc = &RRCMessage->choice.RRCSetupComplete.criticalExtensions.choice.rrcSetupComplete;
    ChangeRRCUEState(rrc->ng_5G_S_TMSI_Value, NR_RRC_CONNECTED);
    sendNASmessage(&rrc->dedicatedNAS_Message); 
   
}

int sendNASmessage(OCTET_STRING_t* NAS){

}

ChangeRRCUEState(struct RRCSetupComplete_IEs__ng_5G_S_TMSI_Value* ng, int state){
    
}