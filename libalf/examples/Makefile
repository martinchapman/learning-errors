.PHONY: all clean

# PREFIX ?= $(PROG)/libalf
PREFIX ?= /usr/local
# note: to change anything in the library, we need to run make install from C:\.....\learn_environment\trunk\libalf\libalf. The executable in Examples links to the library in /usr/local


CPPFLAGS+=-I${PREFIX}/include -I../libalf/include -I../../scc/boost_1_53_0 -I/sw/include -I/sw/opt/boost-1_55/include -Wall -g

CPPFLAGS+=-I../../scc/boost -I../ -D_EXPERIMENT_MODE -U_WIN32 -D_MYWIN32

LDFLAGS+=-L${PREFIX}/lib -L${PWD}/../libalf/src -g

# Add winsock2 library if compiled for Windows.
ifeq (${OS}, Windows_NT)
	LDFLAGS += -lws2_32
endif

all: online 
#offline

clean:
	-rm -f online offline

online: ../../scc/dominators.cpp online.cpp 
	g++ ${CPPFLAGS} ../../scc/dominators.cpp online.cpp ${LDFLAGS} -o online -lalf

offline: offline.cpp
	g++ ${CPPFLAGS} offline.cpp ${LDFLAGS} -o offline -lalf