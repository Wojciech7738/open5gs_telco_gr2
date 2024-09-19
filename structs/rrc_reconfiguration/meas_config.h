#ifndef MEAS_CONFIG_H
#define MEAS_CONFIG_H

#include "general.h"

typedef int meas_object_id, meas_id, report_config_id, report_config_id; 

struct meas_config{
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
};

struct meas_id_to_add_mod{
    meas_id _meas_id;
    meas_object_id _meas_object_id;
    report_config_id _report_config_id;
};
struct meas_object_to_add_mod{
    meas_object_id _meas_object_id;
    meas_object _meas_object;
};

struct s_measure_config{
    int ssb_rsrp; //0..127
    int csi_rsrp; //0..127
};

//TODO
struct meas_object{
};

struct quantity_config{
};

struct meas_gap_config{
};

struct meas_gap_sharing_config{
};
#endif