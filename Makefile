# Linux/Mac makefile

all:
	cd libalf/libalf; make install
	cd libalf/examples; make
	cd scc; make

example:
	./run.sh tcas_auto_instrumented.c 5
