TARGET := MultiThread
INCLUDE := -I ../inc/sync -I ../inc/hiredis
LIB := -L../lib -lrediscpp -lhiredis -lpthread
MultiThread_objs := MultiThread.o
include ../makefile.inc

all:$(TARGET)

MultiThread:$(MultiThread_objs)
	$(XX) -o $@ $(MultiThread_objs) $(LDFLAGS) $(LIB)
clean :
	rm -fr *.d *.o $(TARGET)
