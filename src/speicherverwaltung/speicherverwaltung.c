
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>

#include "speicherverwaltung.h"

char mempool[MEM_POOL_SIZE];
struct memblock *freemem = 0;

void init_heap(void) {
    static bool heapInitialised = false;
    if(freemem == NULL && !heapInitialised) {
	freemem = (memblock *) mempool;
	freemem->size = MEM_POOL_SIZE - sizeof(memblock);
	freemem->next = NULL;
	heapInitialised = true;
    }
}

void *cm_malloc(size_t size) {
    memblock *mem, *curr, *prev = NULL;
    #ifndef MALLOCSPLIT
    init_heap();

    if( (size_t*)size == NULL || size == 0) return NULL;

    if(freemem == NULL) return NULL;

    curr = freemem;
    while(curr != NULL) {
	if(curr > (memblock*)(mempool + MEM_POOL_SIZE -1) || curr->next > (memblock*)(mempool + MEM_POOL_SIZE -1)) return NULL;

    if(curr->size >= size) {
	mem = curr;
	if(curr->next == NULL && prev != NULL) {
	    curr = NULL; prev->next = NULL;}
	else if(prev != NULL && curr->next != NULL) {
	    prev->next = curr->next;
	} else if(curr == freemem && curr->next != NULL){
	    freemem = freemem->next; //freemem->next = NULL;
	} else {
	    freemem = NULL;
	}
	mem->next = (memblock*) MAGIC_INT;
	return (void*) (((memblock*) mem )+ 1); /*(mem + sizeof(memblock) + 1); */
    }
    prev = curr;
    curr = curr->next; //printf("CURR: %d, ", curr);
    }
return NULL;
#endif

#ifdef MALLOCSPLIT
    memblock *alloblock;
    init_heap();

    if((size_t*)size == NULL || size == 0) return NULL;

    if(freemem == NULL) return NULL;

    //size_t allocate_size = size + sizeof(memblock);
    curr = freemem;
    while(curr != NULL) {

    if(curr > (memblock*)(mempool + MEM_POOL_SIZE -1) || curr < (memblock*) mempool /*curr->next > (mempool + MEM_POOL_SIZE -1)*/ ) return NULL;

    if(curr->size >= size) {
	alloblock = curr;
	if(curr->size > ( size + 2*sizeof(memblock) + 32 * sizeof(char) ) ) {
	    	//((memblock*)curr +1) = (memblock* ) ((((memblock*) freemem) + 1));
		mem = curr;
		mem = (memblock*) ( ((char*)curr) + (size + sizeof(memblock)));
		mem->size = curr->size - sizeof(memblock) - size;
		mem->next = (curr->next == NULL?NULL:curr->next);
		curr->next = mem;
		curr->size = size;
	
	}

	if(curr->next == NULL && prev != NULL) {
	    curr = NULL; 
	    prev->next = NULL;
	} else if(prev != NULL && curr->next != NULL) {
	    prev->next = curr->next;
	} else if(curr == freemem && curr->next != NULL){
	    freemem = freemem->next; //freemem->next = NULL;
	} else {
	    freemem = NULL;
	}
	alloblock->next = (memblock*) MAGIC_INT; 
	/*mem->size = size;*/
	return (void*) (((memblock*) alloblock )+ 1);
    }
    prev = curr;
    if(curr->next == NULL) curr = NULL; 
    else curr = curr->next;
    }
return NULL;

#endif

}

void cm_free(void *ptr) {
    memblock *d;
    if(ptr == NULL) return;
    if( ((memblock*) ptr - 1)->next != (memblock*) MAGIC_INT) return;
    if( ((memblock*)ptr-1) > (memblock*)(mempool + MEM_POOL_SIZE -1) || 
	((memblock*)ptr-1) < (memblock*)mempool ) return;
    d = freemem;

    freemem = ((memblock*)ptr-1);
    freemem->next = d;
    ptr = NULL;
    return;
}    



void ten_blocks(void) {
    memblock *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    //void *tmp;
    a = (memblock*) mempool;
    freemem = a;

    b = (memblock*) ((char*) (a + 1) + 100);
    a->size = 100;
    a->next = b;

    c = (memblock*) ((char*) (b + 1) + 140);
    b->size = 140;
    b->next = c;

    d = (memblock*) ((char*) (c + 1) + 100);
    c->size = 100;
    c->next = d;

    e = (memblock*) ((char*) (d + 1) + 500);
    d->size = 500;
    d->next = e;

    f = (memblock*) ((char*) (e + 1) + 160);
    e->size = 160;
    e->next = f;

    g = (memblock*) ((char*) (f + 1) + 1000);
    f->size = 1000;
    f->next = g;

    h = (memblock*) ((char*) (g + 1) + 160);
    g->size = 160;
    g->next = h;

    i = (memblock*) ((char*) (h + 1) + 160);
    h->size = 160;
    h->next = i;

    j = (memblock*) ((char*) (i + 1) + 160);
    i->size = 160;
    i->next = j;

    //f = (memblock*) ((char*) (j + 1) + 160);
    j->size = &mempool[MEM_POOL_SIZE - 1] - ((char*) (j + 1));
    j->next = NULL;



/*
memblock *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;

    a = (memblock*) mempool;
    b = (memblock*) (mempool + 200);
    c = (memblock*) (mempool + 400);
    d = (memblock*) (mempool + 600);
    e = (memblock*) (mempool + 800);
    f = (memblock*) (mempool + 1000);
    g = (memblock*) (mempool + 1200);
    h = (memblock*) (mempool + 1400);
    i = (memblock*) (mempool + 1600);
    j = (memblock*) (mempool + 1800);

    a->size = 200 - sizeof(memblock);
    a->next = b;

    b->size = 200 - sizeof(memblock);
    b->next = c;

    c->size = 200 - sizeof(memblock);
    c->next = d;

    d->size = 200 - sizeof(memblock);
    d->next = e;

    e->size = 200 - sizeof(memblock);
    e->next = f;

    f->size = 200 - sizeof(memblock);
    f->next = g;

    g->size = 200 - sizeof(memblock);
    g->next = h;

    h->size = 200 - sizeof(memblock);
    h->next = i;

    i->size = 200 - sizeof(memblock);
    i->next = j;

    j->size = MEM_POOL_SIZE - 1 - (9*200) -sizeof(memblock);
    j->next = NULL;

    freemem = a;
*/
}

void cm_defrag(void) {

    memblock *curr, *prev = NULL, /**test, *PREV,*/ *nextBlock;

    if(freemem == NULL) return;
    curr = freemem;
    //test = curr->next;

    while(curr != NULL) {
        if(curr > (memblock*)(mempool + MEM_POOL_SIZE -1) || curr < (memblock*) mempool ) return;
	
	//PREV = curr;
	if(curr->next == (memblock*) MAGIC_INT) return; //usedMem += curr->size + sizeof(memblock);

	if( (((char*)curr) + (curr->size + sizeof(memblock))) <= (mempool + MEM_POOL_SIZE - 1) ) {
	if( ( (memblock*) ((char*)curr) + (curr->size + sizeof(memblock)))->next != (memblock*) MAGIC_INT /*&& curr->next != NULL*/ && curr->next != (memblock*) MAGIC_INT) {
	    nextBlock = ((memblock*) (((char*)curr) + (curr->size + sizeof(memblock))));
	    while( nextBlock->next != (memblock*) MAGIC_INT && ((memblock*) (((char*)nextBlock) + (nextBlock->size + sizeof(memblock)))) <= (memblock*) (mempool + MEM_POOL_SIZE)   ) {
		if( nextBlock->next != (memblock*) MAGIC_INT ) {
		    
		    curr->size = curr->size + nextBlock->size + sizeof(memblock);
		    //if(curr->next == NULL) curr->next = NULL;
		    if(freemem == nextBlock) freemem = curr;
		}
		nextBlock = ((memblock*) (((char*)nextBlock) + (nextBlock->size + sizeof(memblock))));
	    }
	    //if(freemem == PREV) freemem = curr;
	} }
	if(prev != NULL) prev->next = curr;
	prev = curr;
	curr = curr->next;
	prev->next = NULL;
    }
    return;
}

void cm_defrag20(void) {
    memblock *curr, *freememIndex, *nextBlock;
    curr = (memblock*) mempool;
    freemem = NULL;
    freememIndex = freemem;
    while(curr <= (memblock*)(mempool + MEM_POOL_SIZE - 1) && curr != NULL 
	&& (((char*)curr) + (curr->size + sizeof(memblock))) <= (mempool + MEM_POOL_SIZE - 1)  ) {

	if(curr->next == (memblock*)MAGIC_INT && (memblock*)(((char*)curr) + (curr->size + sizeof(memblock))) <= (memblock*)(mempool + MEM_POOL_SIZE /*- 1*/) ) {
	    //curr = (memblock*) (((char*)curr) + (curr->size + sizeof(memblock)));
	curr = curr;

	} else if( (memblock*)(((char*)curr) + (curr->size + sizeof(memblock))) <= (memblock*)(mempool + MEM_POOL_SIZE - 1) && curr->next != (memblock*)MAGIC_INT) {

	    

	    nextBlock = ((memblock*) (((char*)curr) + (curr->size + sizeof(memblock))));
	    while( nextBlock->next != (memblock*)MAGIC_INT && ((memblock*) (((char*)nextBlock) + (nextBlock->size + sizeof(memblock)))) <= (memblock*)(mempool + MEM_POOL_SIZE)   ) {
		if( nextBlock->next != (memblock*)MAGIC_INT ) {
		    
		    curr->size = curr->size + nextBlock->size + sizeof(memblock);
		    curr->next = NULL;
		}
		nextBlock = ((memblock*) (((char*)nextBlock) + (nextBlock->size + sizeof(memblock))));
	    }	   

	    if(freemem == NULL) {
		freemem = curr;
		freememIndex = curr;
		curr->next = NULL; 

	    } else if(freememIndex != NULL){
		freememIndex->next = curr;
		freememIndex = curr;
		//if( (((char*)nextBlock) + (nextBlock->size + sizeof(memblock)))) > (mempool + MEM_POOL_SIZE - 1) ) curr
	    }
	}
	if( (memblock*)(((char*)curr) + (curr->size + sizeof(memblock))) <= (memblock*)(mempool + MEM_POOL_SIZE - 1) )
	    curr = (memblock*)(((char*)curr) + (curr->size + sizeof(memblock)));
	else curr = NULL;
    }
    if(curr != NULL) {
	if(curr->next != (memblock*)MAGIC_INT && freememIndex != NULL) {
	    freememIndex->next = curr;
	    curr->next = NULL;
	}
    }
    return;
}

void *cm_memcpy(void *dest, const void *src, size_t n) {
    memblock *srcblock = ((memblock*)((memblock*)src - 1));
    memblock *destblock = ((memblock*)((memblock*)dest - 1));
//void* x = NULL;
//char bytesToCopy[n+1] = NULL;
    /*size_t xx = 0;*/ int i;
    char *d = (char*) dest;
    char *s = (char*) src;

    if(src != NULL && dest != NULL && (memblock*)dest >= (memblock*)mempool && (memblock*)dest < (memblock*)(mempool + MEM_POOL_SIZE - 1) && (memblock*)src >= (memblock*)mempool && (memblock*)src < (memblock*)(mempool + MEM_POOL_SIZE - 1) ) {
        if( srcblock->size >= n && destblock->size >= n && destblock->size >= srcblock->size
        && destblock->next == (memblock*)MAGIC_INT && srcblock->next == (memblock*)MAGIC_INT ) {
            if ( srcblock > (destblock + destblock->size + sizeof(memblock))
            || (srcblock + srcblock->size + sizeof(memblock)) < destblock ) {
                for(i = 0; i < n; i++) {
	            d[i] = s[i];
    	        } 
	    }
        }
    }
    return dest;
}

void *cm_realloc(void *ptr, size_t size) {
    void* x = NULL;

    if(ptr == NULL) {
	x = cm_malloc(size);
	if(x != NULL) ptr = x;
    }
    else if(ptr != NULL && size == (int)0) cm_free(ptr);
    return ptr;
}


