#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


#include "TestCase_CcpAppl_MsgRxIndication.h"


/*! @brief CCP Data Collect Manage */
static CcpAppl_DataCollectMng_t CcpAppl_DataCollectMng = {
    SAVE_COLLECT_STEP_WAIT_INIT,
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    TBOX_FALSE
};

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

/*! @brief Don`t define this function, it will cause fail in used mock function. */
//int tboxCcpAnalysis_get_can_bus_data(const tboxCan1Can2RcvMsg_t * pData)
//{
//    printf("CMock Fail.\n");
//    return -1;
//}

/*! @brief mock function */
int __wrap_tboxCcpAnalysis_get_can_bus_data(const tboxCan1Can2RcvMsg_t * pData)
{
    // allows the calling test to check if the supplied parameters are as expected
    //check_expected(pData);
    printf("CMock Success.\n");
	function_called();
    return mock_type(int);
}

/*!
************************************************************************************************************************
* @brief CCP Message Receiver, Update Ecu Collect Data.
* @param[in] const tboxCan1Can2RcvMsg_t *pMsg: CCP Can Message
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2020-10-26
************************************************************************************************************************
*/

int CcpAppl_MsgRxIndication(const tboxCan1Can2RcvMsg_t *pMsg)
{
    int ret = 0;
    if (CcpAppl_DataCollectMng.startCollectInd == TBOX_FALSE)
    {
        return 0; // collect is not ready
    }

    switch (CcpAppl_DataCollectMng.dataCollectStep)
    {
        case SAVE_COLLECT_STEP_START:
            ret = tboxCcpAnalysis_get_can_bus_data(pMsg);
            break;

        default: // Don`t handle on others step
            break;
    }
    return ret;
}


static void UnitTest0001_IndNotTure(void **state)
{
    tboxCan1Can2RcvMsg_t *pMsg = NULL;
    int ret = 0;
 	(void) state; /* unused */
    CcpAppl_DataCollectMng.startCollectInd = TBOX_FALSE;

    ignore_function_calls(__wrap_tboxCcpAnalysis_get_can_bus_data);
    //will_return(__wrap_tboxCcpAnalysis_get_can_bus_data, 1);
	ret = CcpAppl_MsgRxIndication(pMsg);
    assert_int_equal(ret , 0);
}

static void UnitTest0002_NotStart(void **state)
{
    tboxCan1Can2RcvMsg_t *pMsg = NULL;
    int ret = 0;
 	(void) state; /* unused */
    CcpAppl_DataCollectMng.startCollectInd = TBOX_TRUE;
    CcpAppl_DataCollectMng.dataCollectStep = SAVE_COLLECT_STEP_WAIT_INIT;

    ignore_function_calls(__wrap_tboxCcpAnalysis_get_can_bus_data);
    //will_return(__wrap_tboxCcpAnalysis_get_can_bus_data, 1);
	ret = CcpAppl_MsgRxIndication(pMsg);
    assert_int_equal(ret , 0);
}

static void UnitTest0003_CallCorrect(void **state)
{
	tboxCan1Can2RcvMsg_t *pMsg = NULL;
    int ret = 0;
 	(void) state; /* unused */
    CcpAppl_DataCollectMng.startCollectInd = TBOX_TRUE;
    CcpAppl_DataCollectMng.dataCollectStep = SAVE_COLLECT_STEP_START;

    expect_function_call(__wrap_tboxCcpAnalysis_get_can_bus_data);
    will_return(__wrap_tboxCcpAnalysis_get_can_bus_data, 1);
	//ret = CcpAppl_MsgRxIndication(pMsg);
    assert_true(CcpAppl_MsgRxIndication(pMsg) == 1);
}



int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(UnitTest0001_IndNotTure),
		cmocka_unit_test(UnitTest0002_NotStart),
		cmocka_unit_test(UnitTest0003_CallCorrect),
    };
	cmocka_set_message_output(CM_OUTPUT_STDOUT);
    return cmocka_run_group_tests(tests, NULL, NULL);
}

