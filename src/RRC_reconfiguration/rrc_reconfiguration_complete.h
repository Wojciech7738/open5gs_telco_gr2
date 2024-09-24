#ifndef RRC_RECONFIGURATION_COMPLETE_H
#define RRC_RECONFIGURATION_COMPLETE_H

#include "general.h"
enum RECONFIGURATION_COMPLETE_ANSWER {
    SUCCESS,
    FAIL
};

typedef struct rrc_reconfiguration_reject  {} rrc_reconfiguration_reject;

typedef struct {
    
}rrc_reconfiguration_v1530_ies;

typedef struct {
    unsigned char late_non_critical_extension[OCTET_STRING];
    rrc_reconfiguration_v1530_ies non_critical_extension;
}rrc_reconfiguration_complete_ies;


typedef struct rrc_reconfiguration_complete{
    enum RECONFIGURATION_COMPLETE_ANSWER answer;
    int rrc_transaction_identifier; // 0..3 M
    rrc_reconfiguration_complete_ies rrc_reconfiguration_complete; // M
}rrc_reconfiguration_complete;

typedef struct rrc_reconfiguration_answer {
    enum RECONFIGURATION_COMPLETE_ANSWER answer;
    union {
        struct rrc_reconfiguration_complete rrc_reconfiguration_complete;
        struct rrc_reconfiguration_reject rrc_reconfiguration_reject;
    } choice;
} rrc_reconfiguration_answer;






#endif