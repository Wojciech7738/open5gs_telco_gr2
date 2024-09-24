#ifndef MAC_MESSAGES_H
#define MAC_MESSAGES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"
#include "message.h"

#define MAX_MAC_PDUS_QUANTITY 16

int mac_message_get_uplink_msg(message_t* message, ogs_pkbuf_t *pkbuf);
int mac_message_handle_msg(message_t* message);
pdu_t* mac_message_get_next_pdu_from_msg(message_t* message);
int mac_message_set_msg_to_send(ogs_pkbuf_t* pkbuf);

#ifdef __cplusplus
}
#endif

#endif /* MESSAGES_H */