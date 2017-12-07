
all: speicherverwaltung.o display.o demoabsolute demorelative
#ledbar.o:
#	gcc -std=c11 -Wall -pedantic ledbar.c -o ledbar.o -c -g
speicherverwaltung.o:
	gcc -std=c11 -Wall -pedantic speicherverwaltung.c -o speicherverwaltung.o -c -g -I../include/
display.o:
	gcc -std=c11 -Wall -pedantic display.c -o display.o -c -g -I../include/
demoabsolute: ledbar.o speicherverwaltung.o display.o
	gcc -std=c11 -g speicherverwaltung.o display.o demoabsolute.c -I../include/ -o demoabsolute -L../lib/ -lledbar -lwiringPi -lm
demorelative: ledbar.o speicherverwaltung.o display.o
	gcc -std=c11 -g speicherverwaltung.o display.o demorelative.c -I../include/ -o demorelative -L../lib/ -lledbar -lwiringPi -lm

clean:
	rm -f *.o
	rm -f demoabsolute demorelative
