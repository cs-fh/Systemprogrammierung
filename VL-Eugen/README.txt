*************
 KNWN BUGS
*************

In der Makefile funktioniert das Target 'all' noch nicht, 
da wird noch keine ausführbaren Dateien (deklariert) haben.

*************
**TO	   **
**	DO **	
*************
~ 1. Doxygen-Kommentare in den Dateien einfügen 

~ 2. Dateien mit main-Funktion schreiben, damit
	das all-Target funktioniert.

~ 3. Targets testen.

~ 4. Programmierung der Dateien.

	~ 4.1 Anlegen des Heap als globale Variable in spei~waltung.c
	
	~ 4.2 Funktion void init_heap(void), die Pointer auf Beginn von Heap setzt
	
	~ 4.3 Implementieren einer eigenen cm_malloc(size_t size) Funktion
	
	~ 4.4 void ten_blocks() Funktion schreiben, die Heap in Blöcke
		unterteilt
	
	~ 4.5 Anpassen der Funktion display_absolute()
	
	~ 4.6 Eigenes cm_free(void* ptr) implementieren.

	~ 4.7 Erweitern der Funktion cm_malloc(size_t size) nach Aufgabenteil 4.4

	~ 4.8 Relative Füllstandsanzeige der LED-Bar implementieren. 
		int display_average(void)

	~ 4.9 Defragmentierungsfunktion void cm_defrag(void) implementieren

	~ 4.10 Verbesserte Funktion void cm_defrag20(void) implementieren

	~ 4.11 (...)
~ 5. GDB User-Defined-Commands

	~ 5.1 Erstellen von User-Commands, die den Heap blockweise traversieren
		und ausgeben können.
	
	~ 5.2 Erstellen eines Makros, welches einen belegten Block ausgeben kann
	
	~ 5.3 Erstellen eines Makros zum Ausgeben aller Speicherblöcke

~ 6. Codestyle-Check der Dateien.

~ 7. Valgrind?