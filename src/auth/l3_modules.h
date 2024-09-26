#ifndef L3_MODULES_H
#define L3_MODULES_H

#include <stdint.h>
#include <pthread.h>
#include <sys/shm.h>
#include <string.h>
#include <ogs-core.h>
#include "DedicatedNAS-Message.h"

#define SHM_KEY 0x1234
#define SHM_SIZE 1024

#define UDM_SHARED_MEM 10
#define PCF_SHARED_MEM 20
#define NSSAF_SHARED_MEM 30
#define AMF_SHARED_MEM 40 
#define UE_SHARED_MEM 50
#define SMF_SHARED_MEM 60

pthread_mutex_t shared_memory_lock = PTHREAD_MUTEX_INITIALIZER;

int send_message_to_L3(ogs_pkbuf_t* message, const int module_number);
int receive_message_from_L3(ogs_pkbuf_t* message, const int module_number);

#endif