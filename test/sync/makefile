TARGET := ResultTest CommandTest
INCLUDE := -I ../../inc/sync -I ../../inc/hiredis
LIB := -L../../lib -lrediscpp -lhiredis
ResultTest_objs := ResultTest.o
CommandTest_objs := CommandTest.o
include ../../makefile.inc

all:$(TARGET)

ResultTest:$(ResultTest_objs)
	$(XX) -o $@ $(ResultTest_objs) $(LDFLAGS) $(LIB)
CommandTest:$(CommandTest_objs)
	$(XX) -o $@ $(CommandTest_objs) $(LDFLAGS) $(LIB)

clean :
	rm -fr *.d *.o $(TARGET)
