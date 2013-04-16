.PHONY: all clean

PREFIX ?= /usr/local
# note: to change anything in the library, we need to run make install from C:\temp\learn_environment\trunk\libalf\libalf. The executable in Examples links to the library in /usr/local


CPPFLAGS+=-I${PREFIX}/include -I/cygdrive/c/temp/learn_environment/trunk/scc/boost_1_53_0 -Wall -g

CPPFLAGS+=-I../../scc/boost

LDFLAGS+=-L${PREFIX}/lib  -g

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