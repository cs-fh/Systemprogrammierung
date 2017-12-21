CC = gcc
CXX = g++

CFLAGS = -std=c11 -pedantic -Wall
CXXFLAGS = -std=c++14 -pedantic -Wall -Werror
CXXFLAGS+ = -I$(INCLUDE)

LDFLAGS = -L$(LIB) -Wl,-rpath=$(LIB)
LDLIBS = -lm -lstdc++

INCLUDE = .
LIB = .

SRC  = 
OBJ  = $(SRC:.cpp=.o)
PROG = 

all: installLedbar installRingbuffer
	cd src && $(MAKE)
install: all installLedbar installRingbuffer
	mkdir -p bin && mv src/demoringbuffer bin/

makeLedbar: src/ledbar.o
	gcc -c -o src/ledbar.o src/ledbar.c
	gcc -shared -o src/libledbar.so src/ledbar.o
installLedbar: makeLedbar
	mkdir -p lib && mv src/libledbar.so lib/

makeRingbuffer: src/ringbuffer.o
	$(CC) $(CFLAGS) -I./include/ -c -o src/ringbuffer.o src/ringbuffer.c
	$(CC) $(CFLAGS) -I./include/ -shared -o src/libringbuffer.so src/ringbuffer.o

installRingbuffer: makeRingbuffer
	mkdir -p lib && mv src/libringbuffer.so lib/

test:
	cd tests
	make
run: install
	cd bin && sudo ./demoringbuffer
doc:
	doxygen Doxygenfile
clean:
	cd src && $(MAKE) clean

.PHONY: distclean
distclean: clean
	rm -rf lib bin doc