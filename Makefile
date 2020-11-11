INC=-I/usr/local/include/
LIB=-L/usr/local/lib/


TOP ?= $(shell pwd)
CSRC = $(wildcard *.c)
TAGS = $(basename $(CSRC))
SRC_OBJ = $(patsubst %.c, %.o, $(CSRC)) 
CC = gcc

TEST_CASE_SRC = $(TOP)/Ccp_Application_Layer/CcpAppl_GetMsgMemoryPathStr
TEST_CASE_SRC += $(TOP)/Ccp_Application_Layer/CcpAppl_MsgRxIndication
TEST_CASE_SRC += $(TOP)/Ccp_Application_Layer/tboxSave2Sd_mkdir_data_ymd

RUNABLE += $(foreach n, $(TEST_CASE_SRC), $(basename $(wildcard $(n)/*.c)))

all: $(TEST_CASE_SRC)
	@echo $(TEST_CASE_SRC)
	for d in $(TEST_CASE_SRC) ; do $(MAKE) -C $$d all ; done
	

run_all_testcase: 
	@echo $(RUNABLE)
	$(foreach n, $(RUNABLE), cd / && .$(n))

clean:
	for d in $(TEST_CASE_SRC) ; do $(MAKE) -C $$d clean ; done
