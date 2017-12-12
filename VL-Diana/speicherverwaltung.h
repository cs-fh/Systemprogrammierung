#ifndef SPEICHERVERWALTUNG_H
#define SPEICHERVERWALTUNG_H


#ifdef __cplusplus
extern "C" {
#endif

#define MEM_POOL_SIZE 16384
#define MAGIC_INT 0xacdcacdc


#include"stddef.h"

/*Heap soll durch ein Byte-Array mempool simuliert werden:*/
extern char mempool[MEM_POOL_SIZE];

/*Jeder Block (frei und belegt) beginnt mit einer Verwaltungsstruktur memblock:*/
typedef struct memblock {
    size_t size;            // Für User nutzbare Länge des Blocks [Bytes]
    struct memblock *next; // Zeiger auf Anfang des nächsten freien Blocks (oder NULL)
} memblock;

/*Der Pointer freemem (Typ: memblock*) zeigt immer auf den Anfang der Freispeicherliste. Wenn es keine
freien Blöcke mehr gibt, hat freemem den Wert NULL.*/
extern memblock* freemem;

/*die den simulierten Heap initialisiert und den
Pointer freemem auf den Beginn der Freispeicherliste zeigen lässt*/
void init_heap(void);

/*Funktion, die sich ähnlich zu malloc() aus der C-Standardbibliothek verhält*/
void *cm_malloc(size_t size);

/*Funktion die sich ähnlich zu free() aus C-Standardbibliothek verhällt. übergebende Block
soll als freier Block am Anfang der Freispeicherliste eingehängt werden*/
void cm_free(void *ptr);

/*benachbarte (aneinander grenzende) freie Blöcke werden zu einem einzigen Block zusammenfügt*/
void cm_defrag(void);

/*effizientere Alternative, die nicht die Freispeicherliste nutzt, sondern direkt blockweise durch das Array mempool läuft*/
void cm_defrag20(void);

#ifdef __cplusplus
}
#endif

#endif /* SPEICHERVERWALTUNG_H
 */
/*
https://www.proggen.org/doku.php?id=c:compiler:options
https://de.wikibooks.org/wiki/C-Programmierung:_Pr%C3%A4prozessor

http://www.lcs-chemie.de/c_comp.htm
https://www.oreilly.de/german/freebooks/rlinux3ger/ch132.html

https://www.oreilly.de/german/freebooks/rlinux3ger/ch133.html

https://www-user.tu-chemnitz.de/~hmai/gcc/Ausarbeitung_1/
!!!!!!!!!!!!!!!!!!
https://www-user.tu-chemnitz.de/~hmai/gcc/Ausarbeitung_1/prae_opt.html
????makefile
http://www.ijon.de/comp/tutorials/makefile.html
https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html

http://www.c-howto.de/tutorial/makefiles/
https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html
*/
