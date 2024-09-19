#ifndef RRC_HANDLER_H
#define RRC_HANDLER_H

#include "ogs-pkbuf.h"
#include "MessageType.h"
#include "ber_decode.h"

int RRCestablishConection();

int handle_RRC(ogs_pkbuf_t* pkbuf);


#endif