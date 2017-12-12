
## Compiler and general flags
CC=gcc
CFLAGS=-std=c11 -pedantic -Wall
CFLAGS+=-fPIC
CFLAGS+=-DNDEBUG
CFLAGS+=-I$(INCLUDE) -I.

CXX=g++
CXXFLAGS=-Wall
CXXFLAGS+=-DNDEBUG
CXXFLAGS+=-I$(INCLUDE) -I.

CMOCKFLAGS=$(shell cmock-config --cflags)
CMOCKLDFLAGS:=$(shell cmock-config --libs)

LDFLAGS=-L. -Wl,-rpath=.
LDLIBS=-lwiringPi -lm -pthread -lgtest -lgmock -lgmock_main

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
SUTSRC = $(addprefix $(SRC), ledbar.c speicherverwaltung.c display.c)

## Flags and suffixes
## TODO: Project specific: Adapt accordingly!
FLAG = -DMALLOCSPLIT
SUFF = _flag

## Test binaries
## TODO: Project specific: Adapt accordingly!
TESTS      = speicherverwaltung
TESTS_FLAG = $(TESTS:%=%$(SUFF))
ALL_TESTS  = $(TESTS) $(TESTS_FLAG)

TESTS_SPEICHERVERWALTUNG = $(filter speicherverwaltung%,$(ALL_TESTS))

## Test sources
## TODO: Project specific: Adapt accordingly!
$(TESTS_SPEICHERVERWALTUNG): speicherverwaltung_tests.cpp ledbar_mock.cpp


## Main targets
.DEFAULT_GOAL=test  ## otherwise the definition of test sources would count as default target
.Phony: test
test: $(TESTS)
	-./speicherverwaltung

.Phony: test_flag
test_flag: $(TESTS_FLAG)
	-./speicherverwaltung$(SUFF)

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
abgabe: $(TESTS) $(TESTS_FLAG)
	-./speicherverwaltung
	-./speicherverwaltung$(SUFF)
	-valgrind --leak-check=yes ./speicherverwaltung
	-valgrind --leak-check=yes ./speicherverwaltung$(SUFF)
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





