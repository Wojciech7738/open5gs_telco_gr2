#include "core/abts.h"
#include "RRC/RRC_handler.h"
#include "RRCSetupComplete-IEs.h"
#include "RRC/ber_encode.h"


static void isUEIdleState_test(abts_case *tc, void *data){
    InitialUE_Identity_t ue;
    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
   
    bit_string.size = 5;
    bit_string.bits_unused = 1;
    ue.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    ue.choice.ng_5G_S_TMSI_Part1 = bit_string;
    
    ABTS_INT_EQUAL(tc,isUEIdleState(&ue),0);
    free(bit_string.buf);
}

static void rrcEstablishConnection_test(abts_case *tc, void *data){
    InitialUE_Identity_t ue;
    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
    bit_string.size = 5;
    bit_string.bits_unused = 1;
    ue.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    ue.choice.ng_5G_S_TMSI_Part1 = bit_string;
    
    ABTS_INT_EQUAL(tc,rrcEstablishConnection(&ue),0);
    free(bit_string.buf);
}

static void sendtoUE_test(abts_case *tc, void *data){

    uint8_t* buffer = malloc(sizeof(uint8_t)*5);
    InitialUE_Identity_t ue;
    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
    bit_string.size = 5;
    bit_string.bits_unused = 1;
    ue.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    ue.choice.ng_5G_S_TMSI_Part1 = bit_string;

    ABTS_INT_EQUAL(tc,sendtoUE(buffer,&ue),0);

    free(buffer);
    free(bit_string.buf);
}

static void per_encode_RRCReject_test(abts_case *tc, void *data){
    RejectWaitTime_t rw = 1;
    RRCReject_t rrcReject;
    rrcReject.criticalExtensions.present = RRCReject__criticalExtensions_PR_rrcReject;
    rrcReject.criticalExtensions.choice.rrcReject.lateNonCriticalExtension = NULL;
    rrcReject.criticalExtensions.choice.rrcReject.nonCriticalExtension = NULL;
    rrcReject.criticalExtensions.choice.rrcReject.waitTime = &rw;
    uint8_t* buffer = per_encode_RRCReject(&rrcReject);
    ABTS_PTR_NOTNULL(tc,buffer);
    free(buffer);
}

static void per_encode_RRCSetup_test(abts_case *tc, void *data){
    RRCSetup_t rrcSetup;
    RadioBearerConfig_t RB;
    OCTET_STRING_t MasterCellGroup;
    
    RB._asn_ctx.bytes_left = 1;

    MasterCellGroup.buf = malloc(sizeof(uint8_t));
    MasterCellGroup.size = 1;

    rrcSetup.rrc_TransactionIdentifier = 1;
    rrcSetup.criticalExtensions.present = RRCSetup__criticalExtensions_PR_rrcSetup;
    rrcSetup.criticalExtensions.choice.rrcSetup.radioBearerConfig = RB;
    rrcSetup.criticalExtensions.choice.rrcSetup.masterCellGroup = MasterCellGroup;
    rrcSetup.criticalExtensions.choice.rrcSetup.lateNonCriticalExtension = NULL;
    rrcSetup.criticalExtensions.choice.rrcSetup.nonCriticalExtension = NULL;

    uint8_t* buffer = per_encode_RRCSetup(&rrcSetup);
    ABTS_PTR_NOTNULL(tc,buffer);
    free(buffer);
    free(MasterCellGroup.buf);
}


static void ChangeRRCUEState_tets(abts_case *tc, void *data){
    
    struct RRCSetupComplete_IEs__ng_5G_S_TMSI_Value *ng_5g = malloc(sizeof(struct RRCSetupComplete_IEs__ng_5G_S_TMSI_Value));
   
    ng_5g->present = RRCSetupComplete_IEs__ng_5G_S_TMSI_Value_PR_ng_5G_S_TMSI;
    ng_5g->choice.ng_5G_S_TMSI.size = 5;
    ng_5g->choice.ng_5G_S_TMSI.bits_unused = 1;
    ng_5g->choice.ng_5G_S_TMSI.buf = malloc(sizeof(uint8_t)*ng_5g->choice.ng_5G_S_TMSI.size);
 
    int result = ChangeRRCUEState(ng_5g, NR_RRC_CONNECTED);
    ABTS_INT_EQUAL(tc, result, 0);

    free(ng_5g->choice.ng_5G_S_TMSI.buf);
    free(ng_5g);
}

static void updateUEconfig_test(abts_case *tc, void *data){
    RRCSetupComplete_IEs_t* rrc = malloc(sizeof(RRCSetupComplete_IEs_t));
    memset(rrc, 0, sizeof(RRCSetupComplete_IEs_t));
    //fill in if necesary
    ABTS_INT_EQUAL(tc,updateUEconfig(rrc),0);
    free(rrc);
}


static void getTransactionIdentifier_test(abts_case *tc, void *data){
    ABTS_ASSERT(tc,"",getTransactionIdentifier()>=0);
}
static void  getSRB0config_test(abts_case *tc, void *data){
    RadioBearerConfig_t RB = getSRB0config();
    ABTS_ASSERT(tc,"",RB._asn_ctx.bytes_left >=0);
}

static void getMasterCellGroup_test(abts_case *tc, void *data){
    OCTET_STRING_t oc = getMasterCellGroup();
    ABTS_ASSERT(tc,"",oc.size >= 0);
    if(oc.size>0){
        ABTS_PTR_NOTNULL(tc,oc.buf);
    }
}

static void getWaitTime_test(abts_case *tc, void *data){
    RejectWaitTime_t* wt = getWaitTime();
    ABTS_PTR_NOTNULL(tc,wt);
    free(wt);
}

static void handleRRCSetupRequest_test(abts_case *tc, void *data){
    RRCSetupRequest_IEs_t rrc;
    rrc.establishmentCause = 1;
    rrc.ue_Identity.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
    bit_string.size = 5;
    bit_string.bits_unused = 1;
    rrc.ue_Identity.choice.ng_5G_S_TMSI_Part1 = bit_string;
    ABTS_INT_EQUAL(tc,handleRRCSetupRequest(&rrc),0);
    free(bit_string.buf);
  
}

static void handleRRCSetupComplete_test(abts_case *tc, void *data){
    RRCSetupComplete_t rrcSetupComplete;
    rrcSetupComplete.rrc_TransactionIdentifier = 1;
    rrcSetupComplete.criticalExtensions.present = RRCSetupComplete__criticalExtensions_PR_rrcSetupComplete;
    memset(&rrcSetupComplete.criticalExtensions.choice.rrcSetupComplete,0,sizeof(RRCSetupComplete_IEs_t));
    ABTS_INT_EQUAL(tc, handleRRCSetupComplete(&rrcSetupComplete),0);

}


static void ber_decode_RRCSetupRequest_test(abts_case *tc, void *data){
    RRCSetupRequest_IEs_t rrcSetupRequest;
    rrcSetupRequest.establishmentCause = 1;
    rrcSetupRequest.ue_Identity.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1; 

    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
    bit_string.size = 5;
    bit_string.bits_unused = 1;
    rrcSetupRequest.ue_Identity.choice.ng_5G_S_TMSI_Part1 = bit_string;

    int len = 0;
    uint8_t *buffer = ber_encode_RRCSetupRequest(&rrcSetupRequest,&len);
    ABTS_PTR_NOTNULL(tc,buffer);
    

    RRCSetupRequest_t rrc;
    int result = ber_decode_RRCSetupRequest(buffer,&rrc);
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,len,result);

    ABTS_INT_EQUAL(tc,rrc.rrcSetupRequest.ue_Identity.present,InitialUE_Identity_PR_ng_5G_S_TMSI_Part1); 

    ABTS_INT_EQUAL(tc,bit_string.size,rrc.rrcSetupRequest.ue_Identity.choice.ng_5G_S_TMSI_Part1.size); 
    ABTS_INT_EQUAL(tc,bit_string.bits_unused,rrc.rrcSetupRequest.ue_Identity.choice.ng_5G_S_TMSI_Part1.bits_unused); 

    int i = 0;
    for (;i<bit_string.size;i++){
        ABTS_INT_EQUAL(tc,bit_string.buf[i],rrc.rrcSetupRequest.ue_Identity.choice.ng_5G_S_TMSI_Part1.buf[i]);
    }
    ABTS_INT_EQUAL(tc,rrc.rrcSetupRequest.establishmentCause,rrcSetupRequest.establishmentCause);


    free(bit_string.buf);
    free(rrc.rrcSetupRequest.ue_Identity.choice.ng_5G_S_TMSI_Part1.buf);
    free(buffer);
}

static void ber_decode_bit_string_test(abts_case *tc, void *data){
    
    BIT_STRING_t bit_string;
    bit_string.buf = malloc(sizeof(uint8_t)*5);
    bit_string.size = 5;
    bit_string.bits_unused = 1;

    int len = 0;
    uint8_t *buffer = ber_encode_bit_string(&bit_string,&len);
    ABTS_PTR_NOTNULL(tc,buffer);
  
    BIT_STRING_t bit_string2;
    int result = ber_decode_bit_string(buffer,len,&bit_string2);
  
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,result,len);

    ABTS_INT_EQUAL(tc,bit_string.size,bit_string2.size);
    ABTS_INT_EQUAL(tc,bit_string.bits_unused,bit_string2.bits_unused);
    int i = 0;
    for (;i<bit_string.size;i++){
        ABTS_INT_EQUAL(tc,bit_string.buf[i],bit_string2.buf[i]);
    }

    free(buffer);
    free(bit_string.buf);
    free(bit_string2.buf);

}


static void ber_decode_bit_octet_test(abts_case *tc, void *data){
    
    OCTET_STRING_t oc;
    oc.buf = malloc(sizeof(uint8_t)*5);
    oc.size = 5;
   
    int len = 0;
    uint8_t *buffer = ber_encode_bit_octet(&oc,&len);
    ABTS_PTR_NOTNULL(tc,buffer);
  
    OCTET_STRING_t oc2;
    int result = ber_decode_bit_octet(buffer,len,&oc2);
  
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,result,len);

    ABTS_INT_EQUAL(tc,oc.size,oc2.size);
    int i = 0;
    for (;i<oc.size;i++){
        ABTS_INT_EQUAL(tc,oc.buf[i],oc2.buf[i]);
    }
    free(buffer);
    free(oc.buf);
    free(oc2.buf);

}

static void ber_decode_initial_ue_identity_test(abts_case *tc, void *data){
    InitialUE_Identity_t initialUe;
    initialUe.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    initialUe.choice.ng_5G_S_TMSI_Part1.size = 5;
    initialUe.choice.ng_5G_S_TMSI_Part1.bits_unused = 1;
    initialUe.choice.ng_5G_S_TMSI_Part1.buf = malloc(sizeof(uint8_t)*initialUe.choice.ng_5G_S_TMSI_Part1.size);

    int len = 0;
    uint8_t* buffer = ber_encode_initial_ue_identity(&initialUe,&len);
    ABTS_PTR_NOTNULL(tc,buffer);

    InitialUE_Identity_t initialUe2;
    int result = ber_decode_initial_ue_identity(buffer,len,&initialUe2);
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,len,result);
    ABTS_SIZE_EQUAL(tc,sizeof(initialUe),sizeof(initialUe2));
    free(initialUe.choice.ng_5G_S_TMSI_Part1.buf);
    free(initialUe2.choice.ng_5G_S_TMSI_Part1.buf);
    free(buffer);
}


static void ber_decode_RRCSetupRequestIEs_test(abts_case *tc, void *data){
    InitialUE_Identity_t initialUe;
    initialUe.present = InitialUE_Identity_PR_ng_5G_S_TMSI_Part1;
    initialUe.choice.ng_5G_S_TMSI_Part1.size = 5;
    initialUe.choice.ng_5G_S_TMSI_Part1.bits_unused = 1;
    initialUe.choice.ng_5G_S_TMSI_Part1.buf = malloc(sizeof(uint8_t)*initialUe.choice.ng_5G_S_TMSI_Part1.size);

    RRCSetupRequest_IEs_t rrcSetupRequest;
    rrcSetupRequest.establishmentCause = 1;
    rrcSetupRequest.ue_Identity = initialUe;

    int len = 0;

    uint8_t* buffer = ber_encode_RRCSetupRequestIEs(&rrcSetupRequest,&len);
    ABTS_PTR_NOTNULL(tc,buffer);

    RRCSetupRequest_IEs_t rrcSetupRequest2;
    int result = ber_decode_RRCSetupRequestIEs(buffer,len,&rrcSetupRequest2);
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,len,result);
    ABTS_SIZE_EQUAL(tc,sizeof(rrcSetupRequest),sizeof(rrcSetupRequest2));

    free(buffer);
    free(initialUe.choice.ng_5G_S_TMSI_Part1.buf);
    free(rrcSetupRequest2.ue_Identity.choice.ng_5G_S_TMSI_Part1.buf);
}

static void ber_decode_cause_test(abts_case *tc, void *data){
    EstablishmentCause_t est = 1;
    int len = 0;
    uint8_t *buffer = ber_encode_cause(&est,&len);
    ABTS_PTR_NOTNULL(tc,buffer);

    EstablishmentCause_t est2;
    int result = ber_decode_cause(buffer,len,&est2);
    ABTS_INT_NEQUAL(tc,result,-1);
    ABTS_INT_EQUAL(tc,len,result);
    
    ABTS_INT_EQUAL(tc,est2,est);
   

    free(buffer);
}


abts_suite *test_rrc(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, isUEIdleState_test, NULL);
    abts_run_test(suite, rrcEstablishConnection_test, NULL);
    abts_run_test(suite, sendtoUE_test, NULL);
    abts_run_test(suite, per_encode_RRCReject_test, NULL);
    abts_run_test(suite, per_encode_RRCSetup_test, NULL);
    abts_run_test(suite, ChangeRRCUEState_tets, NULL);
    abts_run_test(suite, updateUEconfig_test, NULL);
    abts_run_test(suite, getTransactionIdentifier_test, NULL);
    abts_run_test(suite, getSRB0config_test, NULL);
    abts_run_test(suite, getMasterCellGroup_test, NULL);
    abts_run_test(suite, getWaitTime_test, NULL);
    abts_run_test(suite, handleRRCSetupRequest_test, NULL);
    abts_run_test(suite, handleRRCSetupComplete_test, NULL);
  
    return suite;
}

abts_suite *test_rrc_encoding(abts_suite *suite)
{
    suite = ADD_SUITE(suite)
    abts_run_test(suite, ber_decode_bit_string_test, NULL);
    abts_run_test(suite, ber_decode_initial_ue_identity_test, NULL);
    abts_run_test(suite, ber_decode_cause_test, NULL);
    abts_run_test(suite, ber_decode_RRCSetupRequestIEs_test, NULL);
    abts_run_test(suite, ber_decode_RRCSetupRequest_test, NULL);
    abts_run_test(suite, ber_decode_bit_octet_test, NULL);
    return suite;
}
