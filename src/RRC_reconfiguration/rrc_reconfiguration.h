#ifndef RRC_RECONFIGURATION_H
#define RRC_RECONFIGURATION_H

#include "general.h"
#include "radio_bearer_config.h"
#include "meas_config.h"
#include <stdbool.h>

// otherconfigc & noncritical extensionS will be added later

typedef struct {
}other_config;

typedef struct {
}rrceconfiguration_v1540_ies;

typedef struct {
    bool key_set_change_indicator;
    int next_hop_chaining_count; // 0..7
    unsigned char nas_Container[OCTET_STRING];
}master_key_update;

typedef struct {
    unsigned char master_cell_group[OCTET_STRING];
    ENUMERATED fullConfig; 
    master_key_update _master_key_update;
    unsigned char dedicated_sib1_delivery[OCTET_STRING];
    unsigned char dedicated_system_information_delivery[OCTET_STRING];
    other_config _other_config;
    rrceconfiguration_v1540_ies non_critical_extension; 
}rrceconfiguration_v1530_ies;

typedef struct {
    radio_bearer_config _radio_bearer_config; 
    unsigned char secondary_cell_group[OCTET_STRING];
    meas_config _meas_config;  
    unsigned char late_non_critical_extension[OCTET_STRING];
    rrceconfiguration_v1530_ies non_critical_extension;
}rrc_reconfiguration_ies ;

struct rrc_reconfiguration {
    int rrc_transaction_identifier; // 0..3 M
    rrc_reconfiguration_ies rrc_reconfiguration; // M
};







#endif