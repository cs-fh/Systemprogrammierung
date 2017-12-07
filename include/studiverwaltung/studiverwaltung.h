/*
 * studiverwaltung.h
 *
 * Alle Funktionen, Strukturen und Konstanten zur Studi-Verwaltung sind in
 * diesem Header File zu deklarieren.
 *
 */

/*#include "pruefungen.h"*/

/* **************************** VORGABEN ********************************** */
typedef enum {
    FALSE, TRUE
} sp_boolean;

void sp_free(void *ptr);  /* Prototyp hier fuer Tests */
/* **************************** VORGABEN ********************************** */

#define NAME_LENGTH 13

enum degree_program {IFM, ELM, PFLEGE};




/**
 *\brief Student mit dem Namen des Studierenden, gesammelten Credits und dem eingeschriebenen Studiengang.
*/
    typedef struct student {
    	char name[NAME_LENGTH];
    	unsigned short cps;
    	enum degree_program enrolled;
    } student;
    /**
 *\brief Knoten, der einen Pointer auf einen Studierenden, sowie je einen Pointer auf den naechsten und den vorigen Knoten in der Liste enthaelt.
*/
    typedef struct node {
        struct student *stdnt;
    	struct node *next;
    	struct node *prev;
    } node;

/**
 *\brief Gibt alle Studenten einer Liste aus.
 \param list Studentenliste
*/
void show_all(struct node* list);

/**
 *\brief Erstellt aus der uebergebenen Liste eine neue Liste, in der nur Informatiker enthalten sind. Dabei wird die Reihenfolge nicht geaendert.
 \param list Hauptliste aller Studenten
 \return Informatiker-Liste
*/
struct node* get_ifm_students(struct node* list);

/**
 *\brief Fuegt einen neuen Studenten ans Ende der per Pointer uebergebenden Liste.
 \param list Liste, in die der Student eingefuegt werden soll
 \param newstdnt Neuer Student
 \return Knoten auf den Anfang der Liste
*/
node* append_student(node* list, student* newstdnt);

/**
 *\brief Gibt den Speicher des uebergebenden Knoten frei.
 \param nodetodel Knoten, der freigegeben werden soll
 \param X bei "TRUE" wird der verankerte Student freigegeben
 \return Pointer auf den Anfang einer Liste
*/
node* delete_node(node* nodetodel, sp_boolean X );

/**
 *\brief Gibt den gesamten von einer Liste belegten Heapspeicher frei.
 \param listnode Knoten einer Liste
 \return Anzahl der freigegebenen Knoten
*/
int delete_list(node* listnode);

/**
 *\brief Gibt saemtliche Knoten einer Liste frei. Dabei werden die in den Knoten enthaltenden Studis nicht freigegeben.
 \param listnode Knoten einer Liste
 \return Anzahl der freigegebenen Knoten
*/
int delete_list_partial(node* listnode);

/**
 *\brief Findet Startelement zu einem in einer Liste enthaltenem Knoten.
 \param listnode Knoten, der Tei einer Liste ist.
 \return Startelement einer Liste.
*/
node* get_list_origin(node* listnode);
