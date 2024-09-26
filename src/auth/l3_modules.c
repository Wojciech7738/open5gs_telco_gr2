#include "l3_modules.h"

int send_message_to_L3(ogs_pkbuf_t* message, int module_number) {
	int shm_id = shmget(SHM_KEY + module_number, SHM_SIZE, 0666 | IPC_CREAT);
	if (shm_id == -1) {
		ogs_error("shmget faileď");
		return OGS_ERROR;
	}

	ogs_pkbuf_t* shared_data = (ogs_pkbuf_t*)shmat(shm_id, NULL, 0);
	if (shared_data == (void*)-1) {
		ogs_error("shmat faileď");
		return OGS_ERROR;
	}

    memcpy(shared_data, message, sizeof(ogs_pkbuf_t));
	
	if (shmdt(shared_data) == -1) {
		ogs_error("shmdt faileď");
		return OGS_ERROR;
	}
	return OGS_OK;
}


int receive_message_from_L3(ogs_pkbuf_t* message, int module_number) {
    int shm_id = shmget(SHM_KEY + module_number, SHM_SIZE, 0666 | IPC_CREAT);
	if (shm_id == -1) {
		ogs_error("shmget faileď");
		return OGS_ERROR;
	}

	ogs_pkbuf_t* shared_data = (ogs_pkbuf_t*)shmat(shm_id, NULL, 0);
	if (shared_data == (void*)-1) {
		ogs_error("shmat faileď");
		return OGS_ERROR;
	}

    memcpy(message, shared_data, sizeof(ogs_pkbuf_t));
	
	if (shmdt(shared_data) == -1) {
		ogs_error("shmdt faileď");
		return OGS_ERROR;
	}
	return OGS_OK;
}