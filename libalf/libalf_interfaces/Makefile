# $Id: Makefile 1473 2011-04-01 00:09:31Z davidpiegdon $
# Makefile for libalf interfaces

.PHONY: all clean install uninstall testsuites

include config.mk

all:
	+make -C dispatcher all
	+make -C jalf all

testsuites:
	make -C testsuites

clean:
	make -C dispatcher clean
	make -C jalf clean
	make -C testsuites clean

install:
	+make -C dispatcher install
	+make -C jalf install

uninstall:
	+make -C dispatcher uninstall
	+make -C jalf uninstall
	-rmdir ${JARDIR}


