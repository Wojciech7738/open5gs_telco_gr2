
#include "core/abts.h"
#include "RRC_reconfiguration/handler.h"


static void test_rrc_reconfiguration_handler_passed(abts_case *tc, void *data) {
    struct rrc_reconfiguration rrc_reconfiguration;
    struct connected_ue ue;

    ue.state = CONNECTED;
    int result = rrc_reconfiguration_handler(&rrc_reconfiguration, &ue);
    ABTS_INT_EQUAL(tc, 0, result);
}

static void test_rrc_reconfiguration_handler_fail(abts_case *tc, void *data) {
    struct rrc_reconfiguration rrc_reconfiguration;
    struct connected_ue ue;

    ue.state = IDLE;
    int result = rrc_reconfiguration_handler(&rrc_reconfiguration, &ue);
    ABTS_INT_EQUAL(tc, -1, result);

    ue.state = INACTIVE;
    result = rrc_reconfiguration_handler(&rrc_reconfiguration, &ue);
    ABTS_INT_EQUAL(tc, -1, result);
}

static void test_rrc_reconfiguration_answer_handler_success(abts_case *tc, void *data) {
    struct rrc_reconfiguration_answer rrc_reconfiguration_answer;
    rrc_reconfiguration_answer.answer = SUCCESS;
    int result = rrc_reconfiguration_answer_handler(&rrc_reconfiguration_answer);
    ABTS_INT_EQUAL(tc, 0, result);
}

static void test_rrc_reconfiguration_answer_handler_fail(abts_case *tc, void *data) {
    struct rrc_reconfiguration_answer rrc_reconfiguration_answer;
    rrc_reconfiguration_answer.answer = FAIL;
    int result = rrc_reconfiguration_answer_handler(&rrc_reconfiguration_answer);
    ABTS_INT_EQUAL(tc, -1, result);
}

abts_suite *test_rrc_reconfiguration(abts_suite *suite){
    suite = ADD_SUITE(suite)

    abts_run_test(suite, test_rrc_reconfiguration_handler_passed, NULL);
    abts_run_test(suite, test_rrc_reconfiguration_handler_fail, NULL);
    abts_run_test(suite, test_rrc_reconfiguration_answer_handler_success, NULL);
    abts_run_test(suite, test_rrc_reconfiguration_answer_handler_fail, NULL);

    return suite;
}