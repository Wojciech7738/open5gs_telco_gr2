#ifndef MAC_BUFFER_H
#define MAC_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "core/ogs-core.h"

ogs_pkbuf_t* mac_buffer_tx_alloc(size_t size);
ogs_pkbuf_t* mac_buffer_rx_alloc(size_t size);
ogs_pkbuf_t* mac_buffer_tx_get_ptr(void);
ogs_pkbuf_t* mac_buffer_rx_get_ptr(void);
void mac_buffer_rx_free(void);
void mac_buffer_tx_free(void);

#ifdef __cplusplus
}
#endif

#endif /* MAC_BUFFER_H */