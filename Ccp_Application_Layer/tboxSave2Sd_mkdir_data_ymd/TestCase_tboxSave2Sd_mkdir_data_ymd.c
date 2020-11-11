
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>


#include "../../UnitTest_Type.h"


#define TBOX_SAVE_DIR_NAME_MAX  200
#define	DIR_PATH_RXD_DATA_								"/2ndfile/cdrom/rxd/data_"
#define F_OK    0

typedef enum{
    SAVE_COLLECT_STEP_WAIT_INIT = 0U,
	SAVE_COLLECT_STEP_START	 = 1,
	SAVE_COLLECT_STEP_LOAD_SETTING,
	SAVE_COLLECT_STEP_LOAD_SETTING_OK_INIT,
	SAVE_COLLECT_STEP_GET_CAR_INFO_FROM_ECU,
	SAVE_COLLECT_STEP_GET_CAR_INFO_OVER_INIT,
	
	SAVE_STEP_ERROR = 0xff
}tboxSaveCollectStep_e;

typedef struct{
    uint8_t Rc1Rc2flag;             // type tboxSaveSendOrRcv_t
}tboxCan1Can2RcvMsg_t;


typedef struct CCP_APPL_DATA_COLLECT_MNG_T
{
    tboxSaveCollectStep_e dataCollectStep;
    char msgMemoryDir[TBOX_SAVE_DIR_NAME_MAX];  /*!< collect data save path */

    // data collect usage flag, indication...
    tboxTrueOrFalse startCollectInd;
    
}CcpAppl_DataCollectMng_t;

typedef struct TBOX_SYS_TIME_T
{
    u16 year;
    u8 mon;
    u8 day;
    u8 hour;
    u8 min;
    u8 sec;
}TboxSysTime_t;


/*! @brief CCP Data Collect Manage */
static CcpAppl_DataCollectMng_t CcpAppl_DataCollectMng = {
    SAVE_COLLECT_STEP_WAIT_INIT,
    {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'},
    TBOX_FALSE
};


void __wrap_TboxIf_GetCurrentTime(TboxSysTime_t *pTime)
{
    check_expected(pTime);
    pTime->year = mock_type(u16);
    pTime->mon = mock_type(u8);
    pTime->day = mock_type(u8);
    pTime->hour = mock_type(u8);
    pTime->min = mock_type(u8);
    pTime->sec = mock_type(u8);
}

int __wrap_mkdir(void * pDir, u32 param)
{
    check_expected(pDir);
    check_expected(param);
    return mock_type(int);
}

int __wrap_access(void * pDir, u32 param)
{
    check_expected(pDir);
    check_expected(param);
    return mock_type(int);
}

/*!
************************************************************************************************************************
* @brief create message save path
* @param[in] void
* @param[out] void
* @param[in,out] void
* @returns void
* @pre none
* @note none
* @author Lews Hammond
* @date 2020-10-27
************************************************************************************************************************
*/

static void tboxSave2Sd_mkdir_data_ymd(void)
{
	u32 i = 0;
	
u32 j = 0;
    TboxSysTime_t tNowTime = {0};
	CcpAppl_DataCollectMng_t *pDataCollectMng = &CcpAppl_DataCollectMng;

    TboxIf_GetCurrentTime(&tNowTime);
    i = sprintf(&pDataCollectMng->msgMemoryDir[0],"%s%02d%02d%02d",DIR_PATH_RXD_DATA_,     
                            tNowTime.year,  
                            tNowTime.mon,  
                            tNowTime.day); 

    if (i < TBOX_SAVE_DIR_NAME_MAX)
    {
        pDataCollectMng->msgMemoryDir[i] = (char)0;  
    }
    (void)mkdir(pDataCollectMng->msgMemoryDir,666);
    
    if(0 == access(pDataCollectMng->msgMemoryDir,F_OK)){
        (void)printf("DIR_PATH_RXD_DATA_ = %s \n",pDataCollectMng->msgMemoryDir);
    }else{
        (void)printf("DIR_PATH_RXD_DATA_ MKDIR ERROR \n");
    }

}

static void UnitTest0001_AccessPass(void **state)
{
    TboxSysTime_t tNowTime = {2020, 11, 11, 12, 13, 14};
    expect_not_value(__wrap_TboxIf_GetCurrentTime, pTime, NULL);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.year);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.mon);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.day);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.hour);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.min);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.sec);

    expect_not_value(__wrap_mkdir, pDir, NULL);
    expect_value(__wrap_mkdir, param, 666);
    will_return(__wrap_mkdir, 0);

    expect_not_value(__wrap_access, pDir, NULL);
    expect_value(__wrap_access, param, F_OK);
    will_return(__wrap_access, 0);

    tboxSave2Sd_mkdir_data_ymd();

    assert_memory_equal(CcpAppl_DataCollectMng.msgMemoryDir, "/2ndfile/cdrom/rxd/data_20201111", sizeof("/2ndfile/cdrom/rxd/data_20201111"));
}

static void UnitTest0002_AccessFail(void **state)
{
    TboxSysTime_t tNowTime = {2020, 11, 11, 12, 13, 14};
    expect_not_value(__wrap_TboxIf_GetCurrentTime, pTime, NULL);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.year);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.mon);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.day);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.hour);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.min);
    will_return(__wrap_TboxIf_GetCurrentTime, tNowTime.sec);

    expect_not_value(__wrap_mkdir, pDir, NULL);
    expect_value(__wrap_mkdir, param, 666);
    will_return(__wrap_mkdir, 0);

    expect_not_value(__wrap_access, pDir, NULL);
    expect_value(__wrap_access, param, F_OK);
    will_return(__wrap_access, -1);

    tboxSave2Sd_mkdir_data_ymd();

    assert_memory_equal(CcpAppl_DataCollectMng.msgMemoryDir, "/2ndfile/cdrom/rxd/data_20201111", sizeof("/2ndfile/cdrom/rxd/data_20201111"));
}


int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(UnitTest0001_AccessPass),
		cmocka_unit_test(UnitTest0002_AccessFail),
    };
	cmocka_set_message_output(CM_OUTPUT_STDOUT);
    return cmocka_run_group_tests(tests, NULL, NULL);
}
