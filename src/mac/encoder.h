#ifndef ENCODER_H
#define ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"
#include "message.h"

int encode_msg(ogs_pkbuf_t* pkbuf, pdu_t* pdu, int size);

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_H */