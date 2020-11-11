

INC=-I/usr/local/include/
LIB=-L/usr/local/lib/


TOP ?= $(shell pwd)
CSRC = $(wildcard *.c)
TAGS = $(basename $(CSRC))
SRC_OBJ = $(patsubst %.c, %.o, $(CSRC)) 
CC = gcc



all: $(CSRC)
	$(CC) -g $^ -o $(TAGS) $(INC) $(LIB) -lcmocka
	

clean:
	rm -f $(TOP)/*.o
