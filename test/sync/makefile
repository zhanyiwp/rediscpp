DIRS	:= $(shell find . -maxdepth 3 -type d)
TARGET := ResultTest CommandTest
INCLUDE := -I ../../inc/sync -I ../../inc/hiredis
LIB := -L../../lib -lrediscpp -lhiredis
ResultTest_objs := ResultTest.o
CommandTest_objs := CommandTest.o
include ../../makefile.inc

ResultTest:$(ResultTest_objs)
	$(XX) $(CFLAGS) -o $@ $(ResultTest_objs) $(LDFLAGS) $(LIB)
CommandTest:$(CommandTest_objs)
	$(XX) $(CFLAGS) -o $@ $(CommandTest_objs) $(LDFLAGS) $(LIB)

all:$(TARGET)
clean :
	rm -fr *.d *.o $(TARGET)
	#rm -fr $(foreach dir, $(DIRS), $(wildcard ${dir}/*.o ${dir}/*.d))