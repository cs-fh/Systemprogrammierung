
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

#define MEM_POOL_SIZE 16384
#define MAGIC_INT 0xacdcacdc
//#define MALLOCSPLIT 1

#ifndef memblock
#define memblock beh
typedef struct memblock {
    size_t size;
    struct memblock *next;
} memblock;
#endif

/**
 *\brief Pointer auf den Heap
*/
extern char mempool[MEM_POOL_SIZE];
/**
 *\brief Pointer auf den Anfang der Freispeicherliste
*/
extern struct memblock *freemem;

/** init_heap
 *\brief Initialisiert den Heap und laesst den Pointer freemem auf den Beginn der Freispeicherliste zeigen.
*/
void init_heap(void);

/**
 *\brief Sucht nach einem freien Speicherblock mithilfe der Freispeicherliste.
 *NULL Pointer wenn:
 *      <size> = 0
 *      <freemem> = 0
 *      <curr> oder <next> > MEM_POOL_SIZE
 \param size Groesse, die der Speicherblock mindestens haben soll
 \return Gibt einen Pointer auf den allozierten Speicher zurueck
*/
void *cm_malloc(size_t size);  

/**
 *\brief Gibt den vom Parameter ptr referenzierten Speicherblock wieder frei. Wenn ptr ein NULL-Pointer oder kein durch
 * cm_malloc() angelegter Pointer ist, tut cm_free() nichts.
 \param ptr Pointer auf den Speicherblock, der freigegeben werden soll
*/
void cm_free(void *ptr);

/**
 *\brief Teilt den kompletten Heap in genau 10 unterschiedlich grosse freie Bloecke auf, die in der Freispeicherliste verlinkt sind.
*/
void ten_blocks(void);

/**
 *\brief Fuegt benachbarte aneinander grenzende freie Speicherbereiche zu einem einzigen Speicherbereich zusammen.
 * NULL Pointer bei:
 *      <freemem> = NULL
 *      <curr> out of range
*/
void cm_defrag(void);

/**
 *\brief Fuegt benachbarte aneinander grenzende freie Speicherbereiche zu einem einzigen Speicherbereich zusammen.
 Dabei wird vom Anfang des Heaps an der Heap blockweise durchlaufen. 
*/
void cm_defrag20(void);

/**
 *\brief cm_memcpy() kopiert n Bytes vom Speicherbereich, auf den src zeigt, auf den Speicherbereich, auf den dest zeigt. 
Die Spicherbereiche duerfen sich nicht ueberlappen.
 \param dest Ort, auf der beschrieben werden soll
 \param src Ort, von dem kopiert werden soll
 \param n Laenge des zu kopierenden Speicherbereichs in Bytes
 \return Gibt einen Pointer auf dest zurueck
*/
void *cm_memcpy(void *dest, const void *src, size_t n);

/**
 *\brief Aendert die Groesse eines Speicherblocks auf den der Pointer ptr zeigt auf die Groesse size.
 \param ptr Pointer auf den Block, dessen Groesse veraendert werden soll
 \param size Neue Groesse des Speicherblocks
 \return Gibt Pointer auf den neu allozierten Speicher zurueck
*/
void *cm_realloc(void *ptr, size_t size);

#ifdef __cplusplus
}
#endif
