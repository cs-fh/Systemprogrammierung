#ifndef MEMORY
#define MEM_POOL_SIZE 16384 /*!<Größe des simulierten Heap*/
#define MAGIC_INT 0xacdcacdc /*!<Magischer Wert, der einen belegten Speicherblock anzeigt*/
#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#endif
char mempool[MEM_POOL_SIZE]; /*!<Der simulierte Heap, dargestellt als Char-Array*/
/*! \brief Struktur für einen Speicherblock im Heap
 * Diese Struktur stellt die Freispeicherliste des simulierten Heap dar.
 */
typedef struct memblock {
	size_t size; /*!<Größe des Nutzdatenbereichs*/
	struct memblock *next; /*!<Nächster Speicherblock in der Freispeicherliste*/
} memblock;
memblock* freemem;	 /*!<Anfang der Freispeicherliste, zeigt auf den simulierten Heap*/
void init_heap(void);
void* cm_malloc(size_t size);
void* cm_free(void*);
void ten_blocks(void);
void cm_defrag(void);
void cm_defrag20(void);
void* cm_memcpy(void *dest, const void *src, size_t n);
void* cm_realloc(void *ptr, size_t size);
#ifdef __cplusplus	
}
#endif
#endif
