#ifndef L3_MODULES_H
#define L3_MODULES_H

#include <stdint.h>
#include <pthread.h>
#include <sys/shm.h>
#include "core/ogs-pkbuf.h"
#include "core/ogs-errno.h"

#define SHM_KEY 0x1234
#define SHM_SIZE 1024

#define UDM_SHARED_MEM 10
#define PCF_SHARED_MEM 20
#define NSSAF_SHARED_MEM 30
#define AMF_SHARED_MEM 40 
#define UE_SHARED_MEM 50
#define SMF_SHARED_MEM 60

pthread_mutex_t shared_memory_lock = PTHREAD_MUTEX_INITIALIZER;


// // Shared memory for UDM (Unified Data Management)
// typedef struct {
//     uint8_t udm_status;            // UDM status (0 = idle, 1 = processing)
//     uint8_t subscription_data[256]; // Subscription profile data for UE
//     uint8_t authentication_vector[16]; // Authentication vector sent to AMF
// } udm_shared_memory_t;

// // Shared memory for PCF (Policy Control Function)
// typedef struct {
//     uint8_t pcf_status;            // PCF status (0 = idle, 1 = processing)
//     uint8_t policy_rules[128];     // Policy rules to be applied to a session
// } pcf_shared_memory_t;

// // Shared memory for NSSAAF (Network Slice-Specific Authentication and Authorization Function)
// typedef struct {
//     uint8_t nssaf_status;          // NSSAAF status (0 = idle, 1 = processing)
//     uint8_t slice_auth_data[128];  // Data related to slice-specific authentication
// } nssaf_shared_memory_t;

// // Shared memory for AMF module
// typedef struct {
//     uint8_t auth_vector[16];      // Authentication Vector (RAND, AUTN, etc.)
//     uint8_t kasme[32];            // KASME for NAS security
//     uint8_t amf_status;           // AMF status (0 = idle, 1 = processing)
// } amf_shared_memory_t;

// // Shared memory for UE module
// typedef struct {
//     uint8_t ue_status;            // UE status (0 = idle, 1 = authenticated)
//     uint8_t ue_response[16];      // Authentication Response (RES)
//     uint8_t ue_kasme[32];         // KASME derived by UE
// } ue_shared_memory_t;

// // Shared memory for SMF (optional) - could store session-related data
// typedef struct {
//     uint8_t smf_status;           // SMF status (0 = idle, 1 = active)
//     uint8_t session_id[8];        // Session Identifier
// } smf_shared_memory_t;

// Global instances of the shared memory blocks
// udm_shared_memory_t udm_shared_mem;
// pcf_shared_memory_t pcf_shared_mem;
// nssaf_shared_memory_t nssaf_shared_mem;
// amf_shared_memory_t amf_shared_mem;
// ue_shared_memory_t ue_shared_mem;
// smf_shared_memory_t smf_shared_mem;


void send_message_to_L3(ogs_pkbuf_t* message, const int module_number);
void receive_message_from_L3(ogs_pkbuf_t* message, const int module_number);


#endif