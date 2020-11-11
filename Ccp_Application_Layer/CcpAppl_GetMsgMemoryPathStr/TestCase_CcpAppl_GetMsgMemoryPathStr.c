#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


#include "../../UnitTest_Type.h"


#define TBOX_SAVE_DIR_NAME_MAX  200

typedef struct CCP_APPL_DATA_COLLECT_MNG_T
{

    char msgMemoryDir[TBOX_SAVE_DIR_NAME_MAX];  /*!< collect data save path */

    // data collect usage flag, indication...
    tboxTrueOrFalse startCollectInd;
    
}CcpAppl_DataCollectMng_t;

/*! @brief CCP Data Collect Manage */
static CcpAppl_DataCollectMng_t CcpAppl_DataCollectMng = {
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    TBOX_FALSE
};

/* A test case that does nothing and succeeds. */
static void null_test_success(void **state) {
    (void) state; /* unused */
}

/*!
************************************************************************************************************************
* @brief get message memory path string
* @param[in] u8 len: path string length
* @param[out] char * pDir: path string pointer
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2020-10-27
************************************************************************************************************************
*/

void CcpAppl_GetMsgMemoryPathStr(char * pDir, u8 len)
{
    if ((pDir == NULL) 
     || (len == 0u)
     || (len > (u8)TBOX_SAVE_DIR_NAME_MAX))
    {
        return; // input parameter exception
    }
    
    (void)memcpy(pDir, CcpAppl_DataCollectMng.msgMemoryDir, len);
}


static void UnitTest0001_LenIsZero(void **state)
{
    char dirStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
    const char resStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
 	(void) state; /* unused */
	CcpAppl_GetMsgMemoryPathStr(dirStr, 0);
    assert_memory_equal(resStr, dirStr, TBOX_SAVE_DIR_NAME_MAX);
}

static void UnitTest0002_DirIsNull(void **state)
{
    char * dirStr = NULL;
    const char resStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
 	(void) state; /* unused */
	CcpAppl_GetMsgMemoryPathStr(dirStr, 10);
    assert_int_equal(dirStr, NULL);
}

static void UnitTest0003_LenOutOfRange(void **state)
{
	char dirStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
    const char resStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
 	(void) state; /* unused */
	CcpAppl_GetMsgMemoryPathStr(dirStr, TBOX_SAVE_DIR_NAME_MAX+1);
    assert_memory_equal(resStr, dirStr, TBOX_SAVE_DIR_NAME_MAX);
}

static void UnitTest0004_CopyCorrect(void **state)
{
    char dirStr[TBOX_SAVE_DIR_NAME_MAX] = {0};
    const char resStr[TBOX_SAVE_DIR_NAME_MAX] = {'1', '2', '3', '4', '5'};
 	(void) state; /* unused */
	CcpAppl_GetMsgMemoryPathStr(dirStr, 5);
    assert_memory_equal(resStr, dirStr, TBOX_SAVE_DIR_NAME_MAX);

}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(UnitTest0001_LenIsZero),
		cmocka_unit_test(UnitTest0002_DirIsNull),
		cmocka_unit_test(UnitTest0003_LenOutOfRange),
        cmocka_unit_test(UnitTest0004_CopyCorrect),
    };
	cmocka_set_message_output(CM_OUTPUT_STDOUT);
    return cmocka_run_group_tests(tests, NULL, NULL);
}

