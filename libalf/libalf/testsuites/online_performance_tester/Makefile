# $Id: Makefile 1472 2011-03-31 23:03:06Z davidpiegdon $
# performance tester for online algorithms: Makefile

.PHONY: all clean run jpegs test plot

include ../../config.mk
CXXFLAGS+=-Xlinker -rpath=${LIBDIR}

CPPFLAGS+=-I../../include -I${INCLUDEDIR} -Wall -ggdb3

LDFLAGS+=-L../../src -L${LIBDIR} -lalf -llangen -lAMoRE++

all: performance_test

clean: nodata
	-rm -f *.o performance_test

nodata:
	-rm -f *.dot *.jpg *.stat

run:
	LD_LIBRARY_PATH=../../src ./performance_test

jpegs:
	for EACH in *.dot; do dot -Tjpg "$$EACH" -o "$$EACH.jpg"; done;

performance_test: performance_test.cpp

plot: performance_test
	gnuplot plot.conf

