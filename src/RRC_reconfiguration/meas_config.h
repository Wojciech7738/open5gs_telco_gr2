#ifndef MEAS_CONFIG_H
#define MEAS_CONFIG_H

#include "general.h"

typedef int meas_object_id, meas_id, report_config_id, report_config_id; 

//TODO
typedef struct{
}meas_object;

typedef struct{
}quantity_config ;

typedef struct{
}meas_gap_config;

typedef struct{
}meas_gap_sharing_config;

typedef struct{
    meas_id _meas_id;
    meas_object_id _meas_object_id;
    report_config_id _report_config_id;
}meas_id_to_add_mod;
typedef struct {
    meas_object_id _meas_object_id;
    meas_object _meas_object;
}meas_object_to_add_mod ;

typedef struct{
    int ssb_rsrp; //0..127
    int csi_rsrp; //0..127
}s_measure_config;



typedef struct{
    meas_object_id meas_object_to_remove_list[256];
    meas_id meas_object_to_add_mod_list[256];
    report_config_id report_config_to_remove_list[256];
    report_config_id report_config_to_add_mod_list[256];
    meas_id meas_id_to_remove_list[256];
    meas_id meas_id_to_add_mod_list[256];
    s_measure_config _s_measure_config;
    quantity_config _quantity_config;
    meas_gap_config _meas_gap_config;
    meas_gap_sharing_config _meas_gap_sharing_config;
    ENUMERATED inter_frequency_config_nogap_r16;
}meas_config ;


#endif