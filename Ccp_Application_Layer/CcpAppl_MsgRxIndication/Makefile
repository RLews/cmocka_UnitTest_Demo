

INC=-I/usr/local/include/
LIB=-L/usr/local/lib/

CMOCKA_DIR = /home/lews/Cache/cmocka-embedded-example-master/test/cmocka

TOP ?= $(shell pwd)
CSRC = $(wildcard *.c)
TAGS = $(basename $(CSRC))
SRC_OBJ = $(patsubst %.c, %.o, $(CSRC)) 
CC = cc

MOCKS = tboxCcpAnalysis_get_can_bus_data 
LDFLAGS = $(INC)
LDFLAGS += $(LIB)
LDFLAGS += $(foreach n, $(MOCKS), -Wl,--wrap=$(n))
LDFLAGS += -lcmocka 


all:  $(TAGS) 

$(SRC_OBJ): $(CSRC)
	$(CC) -c $^ -o $@ $(LDFLAGS)

$(TAGS): $(SRC_OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	

clean:
	rm -f $(TOP)/*.o
