CC	=	gcc
DOXYGEN	=	doxygen
CFLAGS	=	-I./../../include/ -Wall -pedantic -std=c11 -g
LFLAGS	=	-lwiringPi
LIB	=	-L../../lib/
TEST	=	./../../tests/speicherverwaltung/
BIN	=	./bin/
DOC	=	./doc/
OBJSV	=	 display.o speicherverwaltung.o ledbar.o demoabsolute.o demorelative.o

all: speicherverwaltung

speicherverwaltung: $(OBJSV)
	$(CC) $(CFLAGS) -o speicherverwaltung speicherverwaltung.o

speicherverwaltung.o: speicherverwaltung.c ./../../include/speicherverwaltung/speicherverwaltung.h
	$(CC) $(CFLAGS) -c speicherverwaltung.c -o speicherverwaltung.o $(LFLAGS)

display.o: ../ledanzeige/display.c ../../include/ledanzeige/display.h
	$(CC) $(CFLAGS) -c ../ledanzeige/display.c -o display.o $(LFLAGS)
	
ledbar.o: ./../ledanzeige/ledbar.c ./../../include/ledanzeige/ledbar.h
	$(CC) $(CFLAGS) -c ./../ledanzeige/ledbar.c -o ledbar.o $(LIB) $(LFLAGS)
	
demoabsolute: ledbar.o speicherverwaltung.o display.o demoabsolute.o
	$(CC) -std=c11 -g speicherverwaltung.o display.o -I./../../include/ $(LIB) -lledbar -lwiringPi -lm
demoabsolute.o: demoabsolute.c
	$(CC) $(CFLAGS) -c demoabsolute.c -o demoabsolute.o $(LFLAGS)

demorelative.o: demorelative.c
	$(CC) $(CFLAGS) -c demorelative.c -o demorelative.o $(LFLAGS)
	
install:

.PHONY: test	
test:
	$(MAKE) -C $(TEST)
run: $(OBJSV)

.PHONY: doc	
doc:
	$(DOXYGEN) Doxyfile
	
.PHONY: clean
clean:
	rm  -rf ./*.o speicherverwaltung
	
distclean: $(BIN)
	rm -rf ./bin/
	rm -rf ./doc/


#all: speicherverwaltung.o display.o demoabsolute demorelative
#ledbar.o:
#	gcc -std=c11 -Wall -pedantic ledbar.c -o ledbar.o -c -g
#speicherverwaltung.o:
#	gcc -std=c11 -Wall -pedantic speicherverwaltung.c -o speicherverwaltung.o -c -g -I../include/
#display.o:
#	gcc -std=c11 -Wall -pedantic display.c -o display.o -c -g -I../include/
#demoabsolute: ledbar.o speicherverwaltung.o display.o
#	gcc -std=c11 -g speicherverwaltung.o display.o demoabsolute.c -I../include/ -o demoabsolute -L../lib/ -lledbar -lwiringPi -lm
#demorelative: ledbar.o speicherverwaltung.o display.o
#	gcc -std=c11 -g speicherverwaltun
#