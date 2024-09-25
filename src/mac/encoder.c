#include "message.h"
#include "encoder.h"

int encode_msg(ogs_pkbuf_t* pkbuf, pdu_t* pdu, int size)
{
    ogs_assert(pkbuf);
    ogs_assert(pdu);

    if (pkbuf->data == pkbuf->head) {
        //its first message, so we need to reserve bytes for msg_header
        ogs_pkbuf_reserve(pkbuf, sizeof(msg_header_t));
    }

    ogs_pkbuf_put(pkbuf, size);
    ogs_assert(ogs_pkbuf_pull(pkbuf, size));

    memcpy(pkbuf->data - size, pdu, size);

    return OGS_OK;
}