DIRS	:= $(shell find . -maxdepth 3 -type d)
TARGET  := ../../lib/librediscpp.a
INCLUDE :=  -I../../inc/hiredis/ -I../../inc/sync/
LIB := -L../../lib -lhiredis
include ../../makefile.inc
$(TARGET) : $(OBJS)
	ar -rs $@ $^
all : $(TARGET)
clean :
	rm -fr *.d *.o $(TARGET)
