#include "core/abts.h"
// #include <ogs-core.h>
#include "auth/auth_request.c"
#include "auth/auth_response.c"
#include "auth/l3_modules.c"
#include "auth/common.c"

static void receive_authorization_request_test(abts_case *tc, void *data) {
    const char *nas_message_hex = 
        "0741020bf600f110000201030003e605"
        "f07000001000050215d011d15200f110"
        "30395c0a003103e5e0349011035758a6"
        "5d0100e0c1";

    uint8_t nas_message[256];
    char hexbuf[OGS_HUGE_LEN];
    ogs_hex_from_string(nas_message_hex, hexbuf, sizeof(hexbuf));
    memcpy(nas_message, hexbuf, strlen(nas_message_hex) / 2);

    int rv = receive_authorization_request(nas_message);
    ABTS_INT_EQUAL(tc, OGS_OK, rv);

}


static void send_authorization_response_test(abts_case *tc, void *data) {
    const char *nas_message_hex = 
        "0741020bf600f110000201030003e605"
        "f07000001000050215d011d15200f110"
        "30395c0a003103e5e0349011035758a6"
        "5d0100e0c1";

    // Convert the hex string to binary form (to match what was sent earlier)
    uint8_t expected_message[256];
    char hexbuf[OGS_HUGE_LEN];
    ogs_hex_from_string(nas_message_hex, hexbuf, sizeof(hexbuf));
    memcpy(expected_message, hexbuf, strlen(nas_message_hex) / 2);

    uint8_t nas_message[256];
    uint8_t *nas_message_ptr = nas_message;
    int rv = send_authorization_response(nas_message_ptr, sizeof(nas_message));

    ABTS_INT_EQUAL(tc, OGS_OK, rv);
    ogs_assert(nas_message_ptr);

    // Compare the received message
    int cmp_result = memcmp(nas_message_ptr, expected_message, sizeof(expected_message));
    ABTS_INT_EQUAL(tc, 0, cmp_result);  // 0 means the memory regions are equal
}

static void send_message_to_L3_test(abts_case *tc, void *data) {
    const char *nas_message_hex = 
        "0741020bf600f110000201030003e605"
        "f07000001000050215d011d15200f110"
        "30395c0a003103e5e0349011035758a6"
        "5d0100e0c1";

    uint8_t nas_message[256];
    uint8_t* nas_message_buf;
    char hexbuf[OGS_HUGE_LEN];
    int nas_message_len = 0;
    ogs_hex_from_string(nas_message_hex, hexbuf, sizeof(hexbuf));
    memcpy(nas_message, hexbuf, strlen(nas_message_hex) / 2);

    nas_message_len = get_message_length(nas_message);
    nas_message_buf = (uint8_t*)malloc(nas_message_len * sizeof(uint8_t));
    memcpy(nas_message_buf, nas_message, nas_message_len);

    ogs_pkbuf_t *pkbuf = ogs_pkbuf_alloc(nas_message, nas_message_len);
    ogs_assert(pkbuf);

    int i;

    for (i = UDM_SHARED_MEM; i < SMF_SHARED_MEM + 10; i = i + 10)
    {
        int result = send_message_to_L3(pkbuf, i);
        ABTS_INT_EQUAL(tc, OGS_OK, result);
    }
    int result = send_message_to_L3(pkbuf, SMF_SHARED_MEM + 1);
    ABTS_INT_EQUAL(tc, OGS_ERROR, result);
    ogs_pkbuf_free(pkbuf);
}


abts_suite *test_auth(abts_suite *suite)
{
    suite = ADD_SUITE(suite)

    abts_run_test(suite, receive_authorization_request_test, NULL);
    abts_run_test(suite, send_authorization_response_test, NULL);
    abts_run_test(suite, send_message_to_L3_test, NULL);

    return suite;
}