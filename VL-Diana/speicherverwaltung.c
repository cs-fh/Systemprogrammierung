#include "../include/speicherverwaltung.h"
#include "../include/display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Der Pointer freemem (Typ: memblock*) zeigt immer auf den Anfang der Freispeicherliste. Wenn es keine
freien Blöcke mehr gibt, hat freemem den Wert NULL.*/
memblock* freemem = NULL;

/*Heap soll durch ein Byte-Array mempool simuliert werden:*/
char mempool[MEM_POOL_SIZE];

/*Funktion die den simulierten Heap initialisiert und den
Pointer freemem auf den Beginn der Freispeicherliste zeigen lässt*/
void init_heap(void)
{
    static bool bUnicFunktionCall = true; /*initialisierung Heaps beim ersten aufruf*/

    if(bUnicFunktionCall == true)
    {
        bUnicFunktionCall = false;/*damit die Funktion beim nächsten Aufruf nichts tut*/

        freemem = (memblock*) mempool;  /*Pointer freemem zeigen auf Beginn Freispeicherliste*/
        freemem->size = sizeof(mempool) - sizeof(memblock); /*Blockgröße*/
        freemem->next = NULL;
    }
    return;
}

/*Funktion, die sich ähnlich zu malloc() aus der C-Standardbibliothek verhält.
Dabei wird mit dem first-fit-Verfahren nach dem ersten freien Speicherblock gesucht,
der eine nutzbare Größe von mindestens 𝑋 Bytes (mit 𝑋 =size Bytes, vgl. Funktionsparameter) hat:*/
void *cm_malloc(size_t size)
{
    init_heap();                             /*soll am Anfang immer aufgerufen werden*/

    memblock *current = freemem;     /*Initialisierung aktuellen Zeigers*/
    memblock *Prev_FreeBlock = NULL;         /*vorheriger freier Block*/
    memblock *New_FreeBlock = NULL;         /*nächster freier Block*/
    int iBlockSize_bevore = 0;               /*Variable zum Speichern der Blockgröße vor Zerlegung des eigentlichen Blocks*/
    bool bBlockWasSplit = false;
    /*Für Aufrufe mit size=0 dürfen keine neuen Blöcke angelegt werden. Rückgabe: NULL-Pointer.*/
    if(size == 0)
    {
        return NULL;
    }

    while(current != NULL && current->next != (memblock*)MAGIC_INT)
    {
        if(current->size > size + (2 * sizeof(memblock))+32)       /* #1. Erfolg mit "first-fit" Verfahren: Blockgröße passt !!!X = size Bytes!!!*/
        {
            iBlockSize_bevore = current->size;
            current->size = size;               /*Blockgröße verändern*/
            New_FreeBlock->size = iBlockSize_bevore - size;/*größe des neuen Blocks festlegen*/

            // Compileroptionen von gcc/g++: -DKonstante  Definiert die angegeben Preprozessorkonstante. Diese wird standardmäßig mit dem Wert 1 definiert.
            #ifdef MALLOCSPLIT
                /* Code, der nicht an den Compiler weitergegeben wird,
                   wenn MALLOCSPLIT nicht von der Compiler-Option "-DKonstante" defnirt wurde!
                   z.B.:  -DMALLOCSPLIT --> muss ins makefile hinzugefügt werden
               */
                if(New_FreeBlock->size >= sizeof(memblock)+1)/*neuer Block kann erzeugt werden*/
                {
                    bBlockWasSplit = true;

                    New_FreeBlock->next = current->next;
                    if(Prev_FreeBlock != current)
                    {
                        Prev_FreeBlock->next = New_FreeBlock->next;
                    }

                    if( current == freemem)
                    {
                        freemem = current->next;
                    }
                    current->next = (memblock*)MAGIC_INT;
                }

            #endif


            if(!bBlockWasSplit) /*neuer Block kann nicht erzeugt werden*/
            {
                if(Prev_FreeBlock == current)/*am Anfang von mempool*/
                {
                    current->size = iBlockSize_bevore;

                    if( current == freemem)
                    {
                        freemem = current->next;
                    }

                    current->next = (memblock*)MAGIC_INT;
                }
                else /*in Mitte oder am Ende von mempool*/
                {
                    current->size = iBlockSize_bevore;


                    Prev_FreeBlock->next = current->next;

                    current->next = (memblock*)MAGIC_INT;
                }

            }

            return(current = current + sizeof(memblock)); /*Der gesamte gefundene Block wird alloziert und ein Pointer auf den Beginn des Nutzdatenbereichs des
                                                        Blocks wird zurückgeliefert.*/
        }
        else /*passt nicht*/
        {
            if(current == Prev_FreeBlock)
            {
                current = current->next;
            }
            else
            {
                Prev_FreeBlock = current;
                current = current->next;
            }
        }
    }
    return NULL; /*Falls kein ausreichend großer Block gefunden wird, soll ein NULL-Pointer zurückgeliefert werden.*/
}

/*Funktion die sich ähnlich zu free() aus C-Standardbibliothek verhällt. übergebende Block
soll als freier Block am Anfang der Freispeicherliste eingehängt werden*/
void cm_free(void* ptr) /*verhalten wie free*/
{
    memblock* help_ptr = (memblock*) ptr;

    if(ptr != NULL && help_ptr->next == (memblock*)MAGIC_INT)/*wenn ptr = NULL || ptr nicht durch malloc angelegt*/
    {
        if(freemem != NULL)     /*Freispeicherliste existiert*/
        {
            if(freemem->next != (memblock*)MAGIC_INT)
            {
                help_ptr->next = freemem; /*freien Block markieren -> Liste existent*/
            }
            else
                return; /*Fehler in der Verlinkung*/
        }
        else /*freemem -Zeiger zeigt nicht auf den Physikalisch ersten Block*/
        {
            help_ptr->next = NULL; /*freien Block markieren -> Liste nicht existent*/
        }

        freemem = help_ptr;/*Block vorn in Liste einhängen*/
    }

   return;
}
/*benachbarte (aneinander grenzende) freie Blöcke werden zu einem einzigen Block zusammenfügt*/
void cm_defrag(void)
{
    memblock* ptr_Curr = freemem;                   /*Den Zeiger vom aktuellen freien Block auf der Anfang der Freispeicherliste setzen!*/
    memblock* ptr_Prev = NULL;                      /*Zeiger vom vorherigen freien Block*/
    memblock* ptr_Next = NULL;                      /*Zeiger vom nächsten freien Block*/
    char* char_ptr = NULL;                          /*Pointer für den Schritt der Verschiebung [BYTE]*/
    bool bShift_freemem = true;                     /* bool: soll "freemem" nach links verschoben werden?*/
    bool bLink_Through_Many_Fields = false;         /*verlinkung durch mehrere Felder*/

    while(ptr_Curr != NULL && ptr_Curr->next != (memblock*)MAGIC_INT && ptr_Curr->next != NULL)
    {
        if(ptr_Next != NULL)    /*Prev_ptr exist!*/
        {
            ptr_Next = ptr_Next->next;
            bLink_Through_Many_Fields = true;
        }
        else
            ptr_Next = ptr_Curr->next;                              /*Next-ptr setzen!*/

        if(ptr_Next->next != (memblock*)MAGIC_INT)              /*Ist Next-ptr frei?*/
        {
            char_ptr = (char*) ptr_Next;                        /*Schritt der Verschiebung [BYTE] setzen!!*/

            if((char_ptr + sizeof(memblock) + ptr_Next->size) == (char*)ptr_Curr)   /*next-Block links v. cuurent*/
            {
                if(!bLink_Through_Many_Fields)
                    ptr_Curr->next = ptr_Next->next;                 /*L und N Felder von Curr_ptr setzen*/
                else
                    ptr_Next->next = ptr_Curr->next;

                ptr_Curr->size = ptr_Curr->size + ptr_Next->size;
                ptr_Curr = ptr_Next;                                /*Curr_ptr verschieben*/

                if(bShift_freemem)
                     freemem = ptr_Next;                            /*freemem nach links schieben*/
            }
            else
            {
                char_ptr = (char*) ptr_Curr;

                if((char_ptr + sizeof(memblock) + ptr_Curr->size) == (char*)ptr_Next)/*/*next-Block rechts v. cuurent*/
                {
                    bShift_freemem = false;                        /*freemem nicht mehr schieben!!!*/
                    ptr_Curr->next = ptr_Next->next;                    /*L und N Felder von Curr_ptr setzen*/
                    ptr_Curr->size = ptr_Curr->size + ptr_Next->size;
                }
            }

            ptr_Next = NULL;                        /* unnötige Zeiger deaktivieren*/
            char_ptr = NULL;                        /* unnötige Zeiger deaktivieren*/
            ptr_Prev = ptr_Curr;                    /*Prev_ptr setzen!*/
            ptr_Curr = ptr_Curr->next;              /* Den nechsten freien Block untersuchen */
        }
    }

    return;
}
/*effizientere Alternative, die nicht die Freispeicherliste nutzt, sondern direkt blockweise durch das Array mempool läuft*/
void cm_defrag20(void)
{
    memblock* ptr_Curr = (memblock*)mempool;                    /*Den Zeiger vom aktuellen freien Block auf der Anfang des Heaps(!!!) setzen!*/
    memblock* ptr_Prev = NULL;                                  /*Zeiger vom vorherigen freien Block*/
    memblock* ptr_Next = NULL;                                  /*Zeiger vom nächsten freien Block*/
    char* char_ptr = (char*) ptr_Curr;                                   /*Pointer für den Schritt der Verschiebung [BYTE]*/
    bool bSet_freemem = true;                                   /* bool: soll "freemem" nach links verschoben werden?*/


    while(char_ptr <= (char*) MEM_POOL_SIZE)
    {
        if (ptr_Curr->next != (memblock *)MAGIC_INT)       /*Der aktueller Block ist NICHT belegt!*/
        {
            if( bSet_freemem )
            {
                freemem = ptr_Curr;   /*Den Zeiger vom aktuellen freien Block auf der Anfang der Freispeicherliste setzen!*/
                bSet_freemem = false;
            }

            char_ptr = (char_ptr + sizeof(memblock) + ptr_Curr->size);
            ptr_Next = (memblock *)char_ptr;

            if (ptr_Next->next != (memblock *)MAGIC_INT)    /*TO DO UNITE ...*/
            {
                if( ptr_Prev != NULL)
                {
                    ptr_Prev->next = ptr_Curr->next;                 /*L und N Felder von ptr_Prev und Curr_ptr setzen*/
                }

                ptr_Curr->size = ptr_Curr->size + ptr_Next->size;
            }

            ptr_Curr->next = NULL;                              /*zunächst auf NULL setzen!*/
            ptr_Prev = ptr_Curr;                                /*Prev_ptr setzen!*/
        }

        /*????? verschiebe auf die nächste Position: Den nächsten freien Block untersuchen ????*/
        char_ptr = (char_ptr + sizeof(memblock) + ptr_Curr->size);
        ptr_Curr = (memblock *)char_ptr;
    }

    return;
}


