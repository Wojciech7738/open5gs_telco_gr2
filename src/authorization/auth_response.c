#include "auth_response.h"


size_t get_message_length(uint8_t* message) {
    size_t length = 0;
    while (message[length] != '\0') {
        length++;
    }
    return length;
}


void receive_NAS_message(uint8_t* nas_message) {
    DedicatedNAS_Message_t* dedicated_nas_message = (DedicatedNAS_Message_t*)malloc(sizeof(DedicatedNAS_Message_t));
    if (dedicated_nas_message == NULL) {
        printf("Memory allocation failed for NAS message.\n");
        return;
    }
    dedicated_nas_message->size = get_message_length(nas_message);
    dedicated_nas_message->buf = (uint8_t*)malloc(dedicated_nas_message->size * sizeof(uint8_t));
    if (dedicated_nas_message->buf == NULL) {
        printf("Memory allocation failed for message content.\n");
        free(dedicated_nas_message->buf);
        free(dedicated_nas_message);
        return;
    }

    memcpy(dedicated_nas_message->buf, nas_message, sizeof(nas_message));

    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(dedicated_nas_message->buf, dedicated_nas_message->size);
    if (!pkbuf) {
        ogs_log_err("Failed to allocate packet buffer for Authentication Response.");
        return;
    }

    send_message_to_L3(pkbuf, AMF_SHARED_MEM);

    ogs_pkbuf_free(pkbuf);
    free(dedicated_nas_message->buf);
    free(dedicated_nas_message);
}


void send_NAS_message(uint8_t* nas_message, int nas_message_len) {
    ogs_pkbuf_t *pkbuf;
    receive_message_from_L3(pkbuf, AMF_SHARED_MEM);

    DedicatedNAS_Message_t* dedicated_nas_message = (DedicatedNAS_Message_t*)malloc(sizeof(DedicatedNAS_Message_t));
    if (dedicated_nas_message == NULL) {
        printf("Memory allocation failed for NAS message.\n");
        return;
    }
    dedicated_nas_message->size = pkbuf->len;
    dedicated_nas_message->buf = (uint8_t*)malloc(dedicated_nas_message->size * sizeof(uint8_t));
    if (dedicated_nas_message->buf == NULL) {
        printf("Memory allocation failed for message content.\n");
        free(dedicated_nas_message->buf);
        free(dedicated_nas_message);
        return;
    }
    memcpy(dedicated_nas_message->buf, pkbuf->data, dedicated_nas_message->size);
    memcpy(nas_message, dedicated_nas_message->buf, dedicated_nas_message->size);

    free(dedicated_nas_message->buf);
    free(dedicated_nas_message);
}

