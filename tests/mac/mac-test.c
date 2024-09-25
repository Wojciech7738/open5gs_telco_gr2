#include "core/abts.h"
#include "ogs-core.h"
#include "mac_messages.h"
#include "mac_buffer.h"
#include "pdu_handler.h"

static message_t* message_sent_from_phy = NULL;
static message_t* message_received_in_mac = NULL;

/* HELP FUNCTION'S FOR SIMULATE MSG FROM PHY */
static void alloc_buffers(void);
static void alloc_messages(void);
static void set_message_sent_from_phy(void);
static void fill_rx_buffer(void);
/* TESTS */
static void test_mac_message_get_uplink_msg(abts_case *tc, void *data);
static void test_mac_message_get_next_pdu_from_msg(abts_case *tc, void *data);
static void test_pdu_handler_handle_uplink_pdu(abts_case *tc, void *data);

static void set_message_sent_from_phy(void)
{
    message_sent_from_phy->header.no_of_pdus = 2;
    message_sent_from_phy->header.size = (uint16_t)(sizeof(pdu_t) * 2 + sizeof(msg_header_t));

    message_sent_from_phy->pdu[0].header.ul_transport_channel = PRACH;
    message_sent_from_phy->pdu[0].pusch.subheader.l8bit.r = 0;
    message_sent_from_phy->pdu[0].pusch.subheader.l8bit.f = 0;
    message_sent_from_phy->pdu[0].pusch.subheader.l8bit.lcid = 12;
    message_sent_from_phy->pdu[0].pusch.subheader.l8bit.l = 4;
    message_sent_from_phy->pdu[0].prach.first_OFDM_symbol_idx = 1;
    message_sent_from_phy->pdu[0].prach.first_slot_symbol_idx = 2;
    message_sent_from_phy->pdu[0].prach.PRACH_occasion_in_freq_domain_idx = 3;
    message_sent_from_phy->pdu[0].prach.UL_carrier_type = 4;

    message_sent_from_phy->pdu[1].header.ul_transport_channel = PUSCH;
    message_sent_from_phy->pdu[1].pusch.subheader.l8bit.r = 0;
    message_sent_from_phy->pdu[1].pusch.subheader.l8bit.f = 0;
    message_sent_from_phy->pdu[1].pusch.subheader.l8bit.lcid = 12;
    message_sent_from_phy->pdu[1].pusch.subheader.l8bit.l = 6;

    message_sent_from_phy->pdu[1].pusch.data[0] = 0xAA;
    message_sent_from_phy->pdu[1].pusch.data[1] = 0xAA;
    message_sent_from_phy->pdu[1].pusch.data[2] = 0xAA;
    message_sent_from_phy->pdu[1].pusch.data[3] = 0xAA;
    message_sent_from_phy->pdu[1].pusch.data[4] = 0xAA;
    message_sent_from_phy->pdu[1].pusch.data[5] = 0xAA;
}

static void alloc_buffers(void)
{
    int size = (MAX_PDUS_QUANTITY * sizeof(pdu_t)) + sizeof(msg_header_t);

    ogs_assert(mac_buffer_rx_alloc(size));

    ogs_assert(mac_buffer_tx_alloc(size));
}


static void fill_rx_buffer(void)
{
    int size = message_sent_from_phy->header.size;
    ogs_assert(size);

    ogs_pkbuf_t* rx_buffer = mac_buffer_rx_get_ptr();

    ogs_pkbuf_put(rx_buffer, size);
    ogs_assert(ogs_pkbuf_pull(rx_buffer, size));

    memcpy(rx_buffer->data - size, message_sent_from_phy, size);

    ogs_assert(ogs_pkbuf_push(rx_buffer, size));
    rx_buffer->len = size;
}


static void alloc_messages(void)
{
    message_sent_from_phy = (message_t*)ogs_malloc(sizeof(message_t));
    ogs_assert(message_sent_from_phy);

    message_received_in_mac = (message_t*)ogs_malloc(sizeof(message_t));
    ogs_assert(message_received_in_mac);
}

static void init_data(void)
{
    alloc_buffers();
    alloc_messages();
    set_message_sent_from_phy();
    fill_rx_buffer();
}

static void deint_data(void)
{
    ogs_free(message_received_in_mac);
    ogs_free(message_sent_from_phy);
    mac_buffer_rx_free();
    mac_buffer_tx_free();
}

static void test_mac_message_get_uplink_msg(abts_case *tc, void *data)
{
    init_data();

    int no_of_decoded_bytes = 0;

    ogs_pkbuf_t* buffer = mac_buffer_rx_get_ptr();

    no_of_decoded_bytes = mac_message_get_uplink_msg(message_received_in_mac, buffer);

    ABTS_INT_EQUAL(tc, message_received_in_mac->header.size, no_of_decoded_bytes);

    uint8_t* bytes_sent_ptr = (uint8_t*)message_sent_from_phy;
    uint8_t* bytes_received_ptr = (uint8_t*)message_received_in_mac;

    for (int i = 0; i < message_received_in_mac->header.size; i++)
    {
        ABTS_INT_EQUAL(tc, *bytes_sent_ptr, *bytes_received_ptr);

        bytes_sent_ptr++;
        bytes_received_ptr++;
    }

    deint_data();
}

static void test_mac_message_get_next_pdu_from_msg(abts_case *tc, void *data)
{
    init_data();

    int no_of_decoded_bytes = 0;

    ogs_pkbuf_t* buffer = mac_buffer_rx_get_ptr();

    no_of_decoded_bytes = mac_message_get_uplink_msg(message_received_in_mac, buffer);

    if (no_of_decoded_bytes != message_received_in_mac->header.size)
    {
        ogs_error("mac_message_get_uplink_msg() failed!");
        return;
    }

    pdu_t* ul_pdu_to_handle = mac_message_get_next_pdu_from_msg(message_received_in_mac);
    ABTS_PTR_NOTNULL(tc, ul_pdu_to_handle);

    ul_pdu_to_handle = mac_message_get_next_pdu_from_msg(message_received_in_mac);
    ABTS_PTR_NOTNULL(tc, ul_pdu_to_handle);

    ul_pdu_to_handle = mac_message_get_next_pdu_from_msg(message_received_in_mac);
    ABTS_PTR_EQUAL(tc, ul_pdu_to_handle, NULL);

    deint_data();
}

static void test_pdu_handler_handle_uplink_pdu(abts_case *tc, void *data)
{
    init_data();

    int no_of_decoded_bytes = 0;

    ogs_pkbuf_t* buffer = mac_buffer_rx_get_ptr();

    no_of_decoded_bytes = mac_message_get_uplink_msg(message_received_in_mac, buffer);
    ogs_assert(no_of_decoded_bytes == message_received_in_mac->header.size);

    pdu_t* ul_pdu_to_handle = mac_message_get_next_pdu_from_msg(message_received_in_mac);
    ABTS_PTR_NOTNULL(tc, ul_pdu_to_handle);

    handle_uplink_pdu(ul_pdu_to_handle);

    ogs_pkbuf_t* mac_tx_buffer = mac_buffer_tx_get_ptr();

    mac_message_set_msg_to_send(mac_tx_buffer);

    message_t* message = (message_t*)(mac_tx_buffer->head);
    ABTS_INT_EQUAL(tc, message->pdu[0].dci_data_format_1_0_RA_RNTI.dci_id, 1);
    ABTS_INT_EQUAL(tc, message->pdu[0].dci_data_format_1_0_RA_RNTI.mod_cod_scheme, 16);
    
    ABTS_INT_EQUAL(tc, message->pdu[1].rar.bi, 2);
    ABTS_INT_EQUAL(tc, message->pdu[1].rar.ul_grant, 900);
    
    deint_data();
}


abts_suite *test_mac(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, test_mac_message_get_uplink_msg, NULL);
    abts_run_test(suite, test_mac_message_get_next_pdu_from_msg, NULL);
    abts_run_test(suite, test_pdu_handler_handle_uplink_pdu, NULL);

    return suite;
}
