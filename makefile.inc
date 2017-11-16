SOURCE  := $(foreach dir, $(DIRS), $(wildcard ${dir}/*.c ${dir}/*.cpp ${dir}/*.cc ${dir}/*.S))
OBJS    := $(patsubst %.c, %.o, $(patsubst %.cpp,%.o, $(patsubst %.cc, %.o, $(patsubst %.S, %.o, $(SOURCE)))))
XX      := g++
LDFLAGS :=
DEFINES :=
C11FLAGS := 
CFLAGS  := -g -O0 -std=c++11 -Wall -Wno-strict-aliasing -Wno-uninitialized $(DEFINES) $(INCLUDE) $(LIB)

.PHONY : all clean

-include *.d

.cpp.o :
	$(XX) $(CFLAGS) -MMD -MF $*.d -c -o $@ $<
.c.o :
	$(XX) $(CFLAGS) -MMD -MF $*.d -c -o $@ $<
.cc.o :
	$(XX) $(CFLAGS) -MMD -MF $*.d -c -o $@ $<
.S :
	$(XX) $(CFLAGS) -MMD -MF $*.d -c -o $@ $<
