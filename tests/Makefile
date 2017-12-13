
## Compiler and general flags
CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CFLAGS+=-fPIC
CFLAGS+=-DNDEBUG
CFLAGS+=-I$(INCLUDE) -I.

CXX=g++
CXXFLAGS=-std=c++14 -Wall
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-I$(INCLUDE) -I.

CMOCKFLAGS=$(shell cmock-config --cflags)
CMOCKLDFLAGS:=$(shell cmock-config --libs)

LDFLAGS=-L. -Wl,-rpath=.
LDLIBS=-lwiringPi -lm -pthread -lgtest -lgtest_main  # -lgmock -lgmock_main

INCLUDE=../include/
SRC=../src/


###############################################################################
##
## Note 1: This makefile is not aware of changes to any test headerfile, i.e.
##         changes to .h files in the tests/ subdirectory are not detected
##         and taken care of.
##         (Changes to source files (test as well as sources under test) and
##         dependencies to the sources under test are detected as always.)
##
## Note 2: When switching from test to abgabe or vice versa please make sure
##         to call make clean. Otherwise the shared libraries and/or binaries
##         may be not be recompiled using the correct flags!
##
## Note 3: Tests should be run as sudo, i.e. `sudo make ...`
##
##
## This makefile deals with test targets with different test sources
## and an additional compiler flag like -DABGABE or -DMALLOCSPLIT.
##

## Sources under test
## TODO: Project specific: Adapt accordingly!
SUTSRC = $(addprefix $(SRC), ledbar.c ringbuffer.c)

## Flags and suffixes
## TODO: Project specific: Adapt accordingly!
FLAG =  # no extra flags in P3
SUFF = _flag

## Test binaries
## TODO: Project specific: Adapt accordingly!
TESTS      = ringbuffer smartpointer
TESTS_FLAG = $(TESTS:%=%$(SUFF))
ALL_TESTS  = $(TESTS) $(TESTS_FLAG)

TESTS_RINGBUFFER   = $(filter ringbuffer%,$(ALL_TESTS))
TESTS_SMARTPOINTER = $(filter smartpointer%,$(ALL_TESTS))

## Test sources
## TODO: Project specific: Adapt accordingly!
$(TESTS_RINGBUFFER): ringbufferTests.cpp
$(TESTS_SMARTPOINTER): smartpointerTests.cpp $(SRC)/smartpointer/RefCounter.cpp $(INCLUDE)/smartpointer/NullPointerException.h $(INCLUDE)/smartpointer/SmartPointer.h


## Main targets
.DEFAULT_GOAL=test  ## otherwise the definition of test sources would count as default target
.Phony: test
test: $(TESTS)
	-./ringbuffer
	-./smartpointer

.Phony: test_flag
test_flag: $(TESTS_FLAG)  ## not used in P3
	-./ringbuffer$(SUFF)
	-./smartpointer$(SUFF)

.Phony: test_ringbuffer test_smartpointer
test_ringbuffer test_smartpointer: test_%: %$
	-./$*

# Abgabe-Target:
# 1. Tests mit -DABGABE-Flag (normale Ausgabe)
# 2. Tests mit Valgrind (Ausgabe bzgl. Memory Leaks)
# Probleme:
# * Valgrind: "still reachable"; siehe Ticket 518 im Redmine (C++, Mocking)
# * Valgrind laeuft auf dem Raspi nicht 100%. Es gibt einen Fehler wg.
#   einer "illegal instruction". Dies stellt kein ernstes Problem dar, die
#   Berechnung der Speicherloecher funktioniert dennoch.
# Das `-` vor den Befehlen unterdrueckt das Abbrechen des Make-Runs
# bei einem Error. Der Error wird natuerlich dennoch kommuniziert.
.Phony: abgabe
abgabe: CFLAGS+=-DABGABE
abgabe: CXXFLAGS+=-DABGABE
abgabe: $(TESTS)
	-./ringbuffer
	-./smartpointer
	-valgrind --leak-check=yes ./ringbuffer
	-valgrind --leak-check=yes ./smartpointer
###############################################################################


## Auxiliary variables and dependencies of sources under test
SUTLIBS  = libsut.so libsut$(SUFF).so
SUTDEPS  = $(SUTLIBS:.so=.d)
$(SUTDEPS): %.d: $(SUTSRC)
	$(CC) $(CFLAGS) -MM $^ > $@ -MT $*.so
-include $(SUTDEPS)

## Extra flags: Compile with `-DABGABE`
libsut$(SUFF).so: CFLAGS+=$(FLAG)
$(TESTS_FLAG): CXXFLAGS+=$(FLAG)

## Extra dependencies: Libs and test targets
$(TESTS): LDLIBS+=-lsut
$(TESTS): libsut.so
$(TESTS_FLAG): LDLIBS+=-lsut$(SUFF)
$(TESTS_FLAG): libsut$(SUFF).so

## Do something :-)
$(ALL_TESTS):
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(CMOCKFLAGS) $(CMOCKLDFLAGS) $^ $(LDLIBS)

$(SUTLIBS): $(SUTSRC)
	$(CC) -shared $(CFLAGS) -o $@ $^


## ... and clean.
.Phony: clean
clean:
	rm -rf *.d *.o *.so $(ALL_TESTS)





