#ifndef HANDLER_H
#define HANDLER_H

#include "rrc_reconfiguration.h"
#include "connected_ue.h"
#include "rrc_reconfiguration_complete.h"

int send_messege_to_ue(void *msg, struct connected_ue *ue);
int rrc_reconfiguration_handler(struct rrc_reconfiguration *rrc_reconfiguration, struct connected_ue *ue);
int rrc_reconfiguration_answer_handler(void *msg);

#endif