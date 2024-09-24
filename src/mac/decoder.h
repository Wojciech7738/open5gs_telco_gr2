#ifndef DECODER_H
#define DECODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"
#include "message.h"

int msg_header_decode(message_t* message, ogs_pkbuf_t *pkbuf);
int pdu_header_decode(pdu_header_t* pdu_header, ogs_pkbuf_t *pkbuf);
int prach_msg_decode(prach_pdu_t* prach_pdu, ogs_pkbuf_t *pkbuf);
int pusch_msg_decode(pusch_pdu_t* pusch_pdu, ogs_pkbuf_t *pkbuf);

#ifdef __cplusplus
}
#endif

#endif /* DECODER_H */