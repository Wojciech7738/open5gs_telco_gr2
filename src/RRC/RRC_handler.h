#ifndef RRC_HANDLER_H
#define RRC_HANDLER_H


#include "MessageType.h"
#include "ber_decode.h"
#include "core/ogs-core.h"

#define NR_RRC_IDLE 0
#define NR_RRC_CONNECTED 1
#define NR_RRC_INACTIVE 2

int handle_RRC(ogs_pkbuf_t* pkbuf);
int handleRRCSetupRequest(RRCSetupRequest_t* rrcSetupRequest);
int sendRRCSetup(InitialUE_Identity_t* UEid);
int sendRRCReject(InitialUE_Identity_t* UEid);
int handleRRCSetupComplete(RRCSetupComplete_t* RRCMessage);
int sendNASmessage(OCTET_STRING_t* NAS);
int ChangeRRCUEState(struct RRCSetupComplete_IEs__ng_5G_S_TMSI_Value *ng_5G_S_TMSI_Value, int state);
RadioBearerConfig_t getSRB0config(void);
OCTET_STRING_t getMasterCellGroup(void);
int isUEIdleState(InitialUE_Identity_t* ue);
int rrcEstablishConnection(InitialUE_Identity_t* ue);
RRC_TransactionIdentifier_t getTransactionIdentifier(void);
uint8_t* per_encode_RRCSetup(RRCSetup_t* rrcSetup); // Accept the structure as argument
uint8_t* per_encode_RRCReject(RRCReject_t* rrcReject); // Accept the structure as argument
int sendtoUE(uint8_t* buffer, InitialUE_Identity_t* UEid); // Include parameters
RejectWaitTime_t* getWaitTime(void);
int updateUEconfig(RRCSetupComplete_IEs_t* rrc);


#endif