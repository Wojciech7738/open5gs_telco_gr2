#include "decoder.h"

int msg_header_decode(message_t* message, ogs_pkbuf_t *pkbuf)
{
    int size = sizeof(msg_header_t);

    if (ogs_pkbuf_pull(pkbuf, size) == NULL) {
       ogs_error("ogs_pkbuf_pull() failed [size:%d]", (int)size);
       return OGS_ERROR;
    }

    memcpy(&message->header, pkbuf->data - size, size);

    return size;
}

int pdu_header_decode(pdu_header_t* pdu_header, ogs_pkbuf_t *pkbuf)
{
    int size = sizeof(pdu_header_t);

    if (ogs_pkbuf_pull(pkbuf, size) == NULL) {
        ogs_error("ogs_pkbuf_pull() failed [size:%d]", (int)size);
        return OGS_ERROR;
    }

    memcpy(pdu_header, pkbuf->data - size, size);

    return size;
}

int prach_msg_decode(prach_pdu_t* prach_pdu, ogs_pkbuf_t *pkbuf)
{
    int size = sizeof(pdu_t) - sizeof(pdu_header_t);

    if (ogs_pkbuf_pull(pkbuf, size) == NULL) {
       ogs_error("ogs_pkbuf_pull() failed [size:%d]", (int)size);
       return OGS_ERROR;
    }

    memcpy(prach_pdu, pkbuf->data - size, size);
    
    return size;
}

int pusch_msg_decode(pusch_pdu_t* pusch_pdu, ogs_pkbuf_t *pkbuf)
{
    int size = sizeof(pdu_t) - sizeof(pdu_header_t);

    if (ogs_pkbuf_pull(pkbuf, size) == NULL) {
       ogs_error("ogs_pkbuf_pull() failed [size:%d]", (int)size);
       return OGS_ERROR;
    }

    memcpy(pusch_pdu, pkbuf->data - size, size);
    
    return size;
}