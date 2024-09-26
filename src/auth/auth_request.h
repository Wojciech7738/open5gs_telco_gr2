#ifndef AUTH_REQUEST_H
#define AUTH_REQUEST_H

#include <ogs-core.h>
#include <string.h>
#include "l3_modules.h"
#include "DedicatedNAS-Message.h"
#include "common.h"

int receive_authorization_request(uint8_t* nas_message);

#endif