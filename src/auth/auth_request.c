#include "auth_request.h"

int receive_authorization_request(uint8_t* nas_message) {
    int size = 0;
    DedicatedNAS_Message_t* dedicated_nas_message = (DedicatedNAS_Message_t*)malloc(sizeof(DedicatedNAS_Message_t));
    if (dedicated_nas_message == NULL) {
        printf("Memory allocation failed for NAS message.\n");
        return OGS_ERROR;
    }
    dedicated_nas_message->size = get_message_length(nas_message);
    dedicated_nas_message->buf = (uint8_t*)malloc(dedicated_nas_message->size * sizeof(uint8_t));
    if (dedicated_nas_message->buf == NULL) {
        printf("Memory allocation failed for message content.\n");
        free(dedicated_nas_message->buf);
        free(dedicated_nas_message);
        return OGS_ERROR;
    }

    memcpy(dedicated_nas_message->buf, nas_message, sizeof(nas_message));
    
    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(NULL, dedicated_nas_message->size);
    if (!pkbuf) {
        printf("Failed to allocate packet buffer for Authentication Response.");
        return OGS_ERROR;
    }
    ogs_pkbuf_put(pkbuf, dedicated_nas_message->size);
    size = sizeof(uint8_t) * dedicated_nas_message->size;
    ogs_assert(ogs_pkbuf_pull(pkbuf, size));
    memcpy(pkbuf->data - size, dedicated_nas_message->buf, size);

    int result = send_message_to_L3(pkbuf, AMF_SHARED_MEM);
    ogs_pkbuf_free(pkbuf);
    free(dedicated_nas_message->buf);
    free(dedicated_nas_message);
    return result;
}