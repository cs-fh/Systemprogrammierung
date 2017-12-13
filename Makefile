DOXYGEN	=	doxygen

all: makeLedbar
	cd src/speicherverwaltung && $(MAKE)
install: all installLedbar
	mkdir -p bin && cp src/speicherverwaltung/demoabsolute src/speicherverwaltung/demorelative bin/
makeLedbar:
	gcc -c -o src/ledanzeige/ledbar.o src/ledanzeige/ledbar.c
	gcc -shared -o src/ledanzeige/libledbar.so src/ledanzeige/ledbar.o
installLedbar: makeLedbar
	mkdir -p lib && cp src/ledanzeige/libledbar.so lib/
test:
	cd tests/speicherverwaltung
	make
run: install
	sudo ./bin/*
.PHONY: doc	
doc:
	$(DOXYGEN) Doxyfile
.PHONY: clean distclean
clean:
	cd src && $(MAKE) clean
distclean: clean
	rm -r lib bin doc
