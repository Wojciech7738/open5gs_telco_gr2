#include "handler.h"
#include <stdio.h>

int send_messege_to_ue(void *msg, struct connected_ue *ue) {
    //printf("Sending message to UE\n");
    return 0;
}

int rrc_reconfiguration_handler(struct rrc_reconfiguration *rrc_reconfiguration, struct connected_ue *ue) {
    if(ue->state != CONNECTED){
        //printf("UE is in wrong state\n");
        return -1;
    }

    void *rec_msg = rrc_reconfiguration;
    if(send_messege_to_ue(rec_msg, ue) != 0){
        //printf("Error sending message to UE\n");
        return -2;
    }

    return 0;
}

int rrc_reconfiguration_answer_handler(void *msg) {
    rrc_reconfiguration_answer *rec_answer = (rrc_reconfiguration_answer *)msg;
    if(rec_answer->answer == SUCCESS){
        //printf("RRC reconfiguration success\n");
        return 0;
    } else {
        //printf("RRC reconfiguration failed\n");
        return -1;
    }
}