#ifndef AUTH_RESPONSE_H
#define AUTH_RESPONSE_H

#include <ogs-core.h>
#include "l3_modules.h"
#include <string.h>
#include "DedicatedNAS-Message.h"
#include "common.h"

int send_authorization_response(uint8_t* nas_message, int nas_message_len);

#endif