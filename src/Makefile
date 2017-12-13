CC=gcc
CXX=g++

CFLAGS=-std=c11 -pedantic -Wall
CXXFLAGS=-std=c++14 -pedantic -Wall -Werror
CXXFLAGS+=-I$(INCLUDE)

LDFLAGS=-L$(LIB) -Wl,-rpath=$(LIB)
LDLIBS=-lm -lstdc++

INCLUDE=.
LIB=.


SRC  = main.cpp MyString.cpp
OBJ  = $(SRC:.cpp=.o)
PROG = MyString

all: ringbuffer.o demoringbuffer
#ledbar.o:
#	gcc -std=c11 -Wall -pedantic ledbar.c -o ledbar.o -c -g
ringbuffer.o:
	gcc -std=c11 -Wall -pedantic ringbuffer.c -o ringbuffer.o -c -g -I../include/

demoringbuffer: #ledbar.o ringbuffer.o
	gcc -std=c11 -g demoringbuffer.c -I../include/ -o demoringbuffer -L../lib/ -lledbar -lringbuffer -lwiringPi -lm -Wl,-rpath=../lib/
#ldlibrarypath

clean:
	rm -f *.o
	rm -f demoringbuffer
