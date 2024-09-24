#include "mac_buffer.h"

static ogs_pkbuf_t* mac_buffer_tx = NULL;
static ogs_pkbuf_t* mac_buffer_rx = NULL;

ogs_pkbuf_t* mac_buffer_tx_alloc(size_t size)
{
    mac_buffer_tx = ogs_pkbuf_alloc(NULL, size);
    ogs_assert(mac_buffer_tx);

    return mac_buffer_tx;
}

ogs_pkbuf_t* mac_buffer_rx_alloc(size_t size)
{
    mac_buffer_rx = ogs_pkbuf_alloc(NULL, size);
    ogs_assert(mac_buffer_rx);
    
    return mac_buffer_rx;
}

ogs_pkbuf_t* mac_buffer_tx_get_ptr(void)
{
    return mac_buffer_tx;
}

ogs_pkbuf_t* mac_buffer_rx_get_ptr(void)
{
    return mac_buffer_rx;
}

void mac_buffer_rx_free(void)
{
    ogs_pkbuf_free(mac_buffer_rx);
}

void mac_buffer_tx_free(void)
{
    ogs_pkbuf_free(mac_buffer_tx);
}