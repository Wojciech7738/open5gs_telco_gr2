#include "mac_messages.h"
#include "decoder.h"

static int no_of_handled_pdus = 0;

int mac_message_get_uplink_msg(message_t* message, ogs_pkbuf_t *pkbuf)
{
    int size = 0;
    int decoded = 0;

    ogs_assert(message);
    ogs_assert(pkbuf);
    ogs_assert(pkbuf->data);

    size = msg_header_decode(message, pkbuf);
    if (size < 0) {
        ogs_error("msg_header_decode() failed");
        return size;
    }

    decoded += size;

    /* message_t FRAME -> [msg_header_t [pdu_header_t, pdu_t]] */

    for(int pdu_idx = 0; pdu_idx < message->header.no_of_pdus; pdu_idx++)
    {
        size = pdu_header_decode(&message->pdu[pdu_idx].header, pkbuf);
        if (size < 0) {
            ogs_error("pdu_header_decode() failed");
            return size;
        }
        decoded += size;

        switch (message->pdu[pdu_idx].header.ul_transport_channel)
        {
        case PRACH:
            size = prach_msg_decode(&message->pdu[pdu_idx].prach, pkbuf);
            if (size < 0) {
                ogs_error("handle_prach_msg() failed");
                return size;
            }
            decoded += size;
            break;
        case PUSCH:
            size = pusch_msg_decode(&message->pdu[pdu_idx].pusch, pkbuf);
            if (size < 0) {
                ogs_error("pusch_msg_decode() failed");
                return size;
            }
            decoded += size;
            break;
        case PUCCH:
            //TODO
            // size = pucch_msg_decode(&message, pkbuf);
            // if (size < 0) {
            //     ogs_error("pucch_msg_decode() failed");
            //     return size;
            // }
            // decoded += size;
            break;
        default:
            break;
        } 
    }

    return decoded;
}

pdu_t* mac_message_get_next_pdu_from_msg(message_t* message)
{
    if (no_of_handled_pdus < message->header.no_of_pdus)
    {
        no_of_handled_pdus++;
        return message->pdu;
    }
    else
    {
        no_of_handled_pdus = 0;
        return NULL;
    }
}

int mac_message_set_msg_to_send(ogs_pkbuf_t* pkbuf)
{
    msg_header_t msg_header = {0};
    int no_of_pdus = (pkbuf->data - pkbuf->head) / sizeof(pdu_t);
    
    msg_header.no_of_pdus = no_of_pdus;
    msg_header.size = (uint16_t)(sizeof(pdu_t) * no_of_pdus) + sizeof(msg_header_t);
    
    memcpy(pkbuf->head, &msg_header, sizeof(msg_header_t));

    return OGS_OK;
}

