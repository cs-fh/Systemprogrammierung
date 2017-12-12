#include "../include/speicherverwaltung.h"
#include <malloc.h>
extern memblock *freemem;
extern char mempool[MEM_POOL_SIZE];
/*! \brief Methode zum Initialisieren des Heap
 * Die Methode setzt den freemem-Pointer auf den
 * Anfang des Heap
 */
void init_heap ()
{
	static char init = 0;
	if (!init)
	{
		freemem = (memblock *) mempool;
		freemem->size = MEM_POOL_SIZE - sizeof (memblock);
		freemem->next = NULL;
		init = 1;
	}
}

/*! \brief Eigene malloc-Methode
 * Die Methode reserviert Speicher in Größe des mitgegebenen Parameter
 * und liefert einen Pointer auf diesen Speicherbereich, falls es
 * erfolgreich war.
 * \param size Größe des Speichers der angelegt werden soll
 * \return Pointer auf den Speicherbereich, den man bekommen hat. Bei Fehler wird NULL zurückgegeben.
 */
void *cm_malloc (size_t size)
{
	init_heap ();
	memblock *currentPtr = freemem;
	memblock *prev = NULL;
	if (size == 0 || size >= MEM_POOL_SIZE || currentPtr == NULL)
	{
		return NULL;
	}
	if (currentPtr->next != NULL)
	{
		while (currentPtr->next != NULL)
		{
			if (currentPtr->size >= size)
			{
				if (prev != NULL)
				{
					prev->next = currentPtr->next;
				}
				currentPtr->next = (memblock *) MAGIC_INT;
				void *output = currentPtr + 1;
				return output;
			}
			prev = currentPtr;
			currentPtr = currentPtr->next;
		}
	}else if (currentPtr->size >= size)
	{
		if (prev != NULL)
		{
			prev->next = currentPtr->next;
		}
		currentPtr->next = (memblock *) MAGIC_INT;
		void *output = currentPtr + 1;
		freemem = NULL;
		return output;
	}
	return NULL;
}

/*! \brief Eigene free-Methode
 * Methode zum Freigeben des reservierten Speichers. Falls der Speicher
 * nicht freigegeben werden kann, wird NULL zurückgegeben.
 * \param ptr Pointer auf den Speicherbereich, der freigegeben werden soll
 * \return Pointer auf den freigegeben Speicherbereich.
 *
 */
void* cm_free(void* ptr){
    if(ptr==NULL){
		return NULL;
	}
	memblock* curr = ((memblock*)ptr)-1;
	memblock* free = freemem;
	if(curr==NULL){
		return NULL;
	}
	if(curr->next != NULL){
		if(curr->next == (memblock*)MAGIC_INT){
			if(free!=NULL){
				if(free->next !=NULL){
					curr->next = free;
					freemem = curr;
					return curr;
				}else{
					curr->next = free;
					freemem = curr;
					return curr;
				}
			}else{
				freemem = curr;
				curr->next = NULL;
				return curr;
			}
			
		}
	} 
	return NULL;   
}
/*! \brief Methode zum Unterteilen des Heaps in zehn Blöcke
 * Die Methode legt zehn Speicherblöcke im Heap an und hängt diese
 * in die Freispeicherliste ein.
 */
void ten_blocks ()
{
	memblock *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
	int size = MEM_POOL_SIZE / 10;
	int blocksize = size - sizeof (memblock);
	memblock ablock, bblock, cblock, dblock, eblock, fblock, gblock, hblock, iblock, jblock;
	a = (memblock *) mempool;
	*a = ablock;
	freemem = &ablock;
	
	b = (memblock *) ((char *) (a + 1) + blocksize);
	*b = bblock;
	ablock.size = blocksize;
	ablock.next = &bblock;
	
	c = (memblock *) ((char *) (b + 1) + blocksize);
	*c = cblock;
	bblock.size = blocksize;
	bblock.next = c;

	d = (memblock *) ((char *) (c + 1) + blocksize);
	*d = dblock;
	cblock.size = blocksize;
	cblock.next = d;

	e = (memblock *) ((char *) (d + 1) + blocksize);
	*e = eblock;
	dblock.size = blocksize;
	dblock.next = e;

	f = (memblock *) ((char *) (e + 1) + blocksize);
	*f = fblock;
	eblock.size = blocksize;
	eblock.next = f;

	g = (memblock *) ((char *) (f + 1) + blocksize);
	*g = gblock;
	fblock.size = blocksize;
	fblock.next = b;

	h = (memblock *) ((char *) (g + 1) + blocksize);
	*h = hblock;
	gblock.size = blocksize;
	gblock.next = c;

	i = (memblock *) ((char *) (h + 1) + blocksize);
	*i = iblock;
	hblock.size = blocksize;
	hblock.next = d;
	j = (memblock *) ((char *) (i + 1) + blocksize);
	*j = jblock;
	iblock.size = blocksize;
	iblock.next = j;

	jblock.size = blocksize;
	jblock.next = NULL;
}

/*! \brief Methode zum Defragmentieren der Freispeicherliste
 * Die Methode geht durch die Freispeicherliste und fügt nebeneinanderliegende
 * freie Speicherblöcke wieder zu einem Speicherblock zusammen.
 */
void cm_defrag(){

 }
/*! \brief Methode zum Defragmentieren des Heap
 * Die Methode geht durch das Heap-Array und versucht benachbarte
 * Speicherblöcke wieder zusammenzuführen.
 */
void cm_defrag20 ()
{

}

/*! \brief Methode zum Kopieren von Inhalten auf den simulierten Heap
 * Die Methode kopiert einen Inhalt von einem Pointer in den simulierten
 * Heap über einen Pointer der in den Heap zeigt.
 * \param dest Pointer auf Heap, wo der Inhalt reinkopiert werden soll
 * \param src Pointer auf den Inhalt der in den Heap kopiert wird
 * \param n Größe des Inhalts der kopiert werden soll
 * \return Pointer auf den kopierten Speicherblock *
 */
void *cm_memcpy (void *dest, const void *src, size_t n)
{
	char* destPtr = (char*)dest;
    char* srcPtr = (char*)src;
    int count = 0;     
    while(n--) {
        *destPtr = *srcPtr;
        destPtr = destPtr + 1;
        srcPtr = srcPtr +1;
        count++;
    }
    while(count!=0){
		destPtr = destPtr - 1;
		count--;
	}
    return dest;
}

/*! \brief Methode zum Vergrößern eines Speicherblocks im Heap
 * Die Methode vergrößert einen übergebenen Speicherblock der im
 * simulierten Heap liegt um size Bytes.
 * \param size Wert um den der Block vergrößert werden soll
 * \param ptr Pointer auf den Speicherblock im Heap
 * \return Pointer auf den vergrößerten Speicherblock
 */
void *cm_realloc (void *ptr, size_t size)
{
}
