CC	=	gcc
DOXYGEN	=	doxygen
CFLAGS	=	-I./../../include/ -Wall -pedantic -std=c11 -g
LFLAGS	=	-lwiringPi
LIB	=	-L../../lib/
TEST	=	./../../tests/speicherverwaltung/
BIN	=	./bin/
DOC	=	./doc/
OBJSV	=	 display.o speicherverwaltung.o ledbar.o demoabsolute.o demorelative.o

all: speicherverwaltung.o demoabsolute demorelative display.o

speicherverwaltung.o: speicherverwaltung.c ./../../include/speicherverwaltung/speicherverwaltung.h
	$(CC) $(CFLAGS) -c speicherverwaltung.c -o speicherverwaltung.o $(LFLAGS)

display.o: ../ledanzeige/display.c ../../include/ledanzeige/display.h
	$(CC) $(CFLAGS) -c ../ledanzeige/display.c -o display.o $(LFLAGS)
	
ledbar.o: ./../ledanzeige/ledbar.c ./../../include/ledanzeige/ledbar.h
	$(CC) $(CFLAGS) -c ./../ledanzeige/ledbar.c -o ledbar.o $(LIB) $(LFLAGS)

demoabsolute: ledbar.o speicherverwaltung.o display.o
	$(CC) -std=c11 -g speicherverwaltung.o demoabsolute.c -I../../include/ -o demoabsolute -lwiringPi -lm display.o

demorelative: ledbar.o speicherverwaltung.o display.o
	$(CC) -std=c11 -g speicherverwaltung.o demorelative.c -I../../include/ -o demorelative -lwiringPi -lm display.o

	
.PHONY: doc	
doc:
	$(DOXYGEN) ../../Doxyfile
	
.PHONY: clean distclean
clean:
	rm  -rf ./*.o speicherverwaltung demoabsolute demorelative
	
distclean: $(BIN)
	rm -rf ./lib/
	rm -rf ./bin/
	rm -rf ./doc/