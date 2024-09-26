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

#define VALIDATE_MODULE_NUMBER(module_number) \
	switch (module_number) \
	{ \
		case UDM_SHARED_MEM: \
		case PCF_SHARED_MEM: \
		case NSSAF_SHARED_MEM: \
		case AMF_SHARED_MEM: \
		case UE_SHARED_MEM: \
		case SMF_SHARED_MEM: \
			break; \
		default: \
			return OGS_ERROR; \
	}


int send_message_to_L3(ogs_pkbuf_t* message, const int module_number);
int receive_message_from_L3(ogs_pkbuf_t* message, const int module_number);

#endif