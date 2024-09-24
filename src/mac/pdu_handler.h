#ifndef PDU_HANDLER_H
#define PDU_HANDLER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"
#include "message.h"

int handle_uplink_pdu(pdu_t* pdu);

#ifdef __cplusplus
}
#endif

#endif /* PDU_HANDLER_H */