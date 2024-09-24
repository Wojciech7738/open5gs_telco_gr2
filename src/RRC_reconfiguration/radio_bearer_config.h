#ifndef RADIO_BEARER_CONFIG_H
#define RADIO_BEARER_CONFIG_H

#include "general.h"

typedef int drb_identity; // 1..32
typedef int mrb_identity; // 1..512

//TODO
typedef struct{
}srb_to_add_mod;

typedef struct {

}drb_to_add_mod;

typedef struct{
}security_config;

typedef struct {
}mrb_to_add_mod;

typedef struct{
}srb4_to_add_mod;


typedef struct{
    int srb_to_add_mod_list[256];
    ENUMERATED srb3_to_release;
    drb_to_add_mod drb_to_add_mod_list[256];
    drb_identity rrb_to_release_list[256];
    security_config _security_config;
    int mrb_to_add_mod_list[256];
    mrb_identity mrb_to_release_list[256];
    srb4_to_add_mod srb_to_add_mod;
    ENUMERATED srb4_to_release;
}radio_bearer_config; 





#endif