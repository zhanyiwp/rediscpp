DIRS	:= $(shell find . -maxdepth 3 -type d)
XX      := g++
LDFLAGS :=
DEFINES :=
TARGET := test_cmd
INCLUDE := -I./
LIB := -L./ -lhiredis -lev
CFLAGS  := -g -O0 -Wall -Wno-strict-aliasing -Wno-uninitialized $(DEFINES) $(INCLUDE) $(LIB) 
test_cmd_objs := async_cmd.o async_conn.o async_reply.o async_redis.o test_cmd.o
#include ./makefile.inc

test_cmd:$(test_cmd_objs)
	$(XX) $(CFLAGS) -o $@ $(test_cmd_objs) $(LDFLAGS) $(LIB)

all:$(TARGET)

clean :
	rm -fr *.d *.o $(TARGET)




