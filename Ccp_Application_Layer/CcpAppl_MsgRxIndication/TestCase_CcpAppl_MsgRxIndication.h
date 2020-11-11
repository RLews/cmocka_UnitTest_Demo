

#ifndef TEST_CASE_CCPAPPL_MSG_RX_INDICATION_H
#define TEST_CASE_CCPAPPL_MSG_RX_INDICATION_H


#include "../../UnitTest_Type.h"



#define TBOX_SAVE_DIR_NAME_MAX  200

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


int __wrap_tboxCcpAnalysis_get_can_bus_data(const tboxCan1Can2RcvMsg_t * pData);

int tboxCcpAnalysis_get_can_bus_data(const tboxCan1Can2RcvMsg_t * pData);

int CcpAppl_MsgRxIndication(const tboxCan1Can2RcvMsg_t *pMsg);


#endif