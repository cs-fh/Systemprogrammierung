CC	=	gcc
DOXYGEN	=	doxygen
CFLAGS	=	-I./include/ -Wall -std=c11 -pedantic
LFLAGS	=	-lwiringPi
LIBLED	=	-L./lib/ledbar
SRC	=	./src/*.c
INCLUDE	=	./include/*.h
TEST	=	./tests/
BIN	=	./bin/
DOC	=	./doc/
OBJS	=	main
.PHONY: all
all: makeLedbar
	$(CC) $(CFLAGS) -c $(SRC) $(INCLUDE) $(LFLAGS)
	rm ./*.o
build: all
	$(CC) $(CFLAGS) -o Main ./src/main.c $(LIBLED)
.PHONY: makebin
makebin: 
	mkdir bin
install: build installLedbar
	mv ./Main ./bin/Main
makeLedbar: ./include/ledbar.h ./src/ledbar.c
	$(CC) $(CFLAGS) -fpic -c ./src/ledbar.c ./include/ledbar.h $(LFLAGS)
	$(CC) -shared -o libledbar.so $^ $(LFLAGS)
installLedbar: makeLedbar
	mv ./libledbar.so ./lib/libledbar.so
.PHONY: test	
test:
	$(MAKE) -C $(TEST)
run: install
	./bin/Main
.PHONY: doc	
doc:
	$(DOXYGEN) Doxyfile
.PHONY: clean
clean:
	rm ./src/*.o
	rm ./*.o	
distclean: $(BIN)
	rm -rf ./bin/
	rm -rf ./doc/
	
