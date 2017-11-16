all:
	make all -C src
	make all -C test
rebuild:
	make rebuild -C src
	make rebuild -C test
clean:
	make clean -C src
	make clean -C test
include ./makefile.inc










































