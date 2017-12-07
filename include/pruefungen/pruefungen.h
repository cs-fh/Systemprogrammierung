/*
 * pruefungen.h
 *
 * Alle Funktionen, Strukturen und Konstanten zur Pruefungsverwaltung sind in
 * diesem Header File zu deklarieren.
 *
 */

#include "studiverwaltung.h"

#include "ledbar.h"

/*student* exams[10];*/


/**
 *\brief Registriert den uebergebenden Student fuer den uebergebenden Listenplatz. Wenn Listenplatz belegt ist, wird solange der naechste Listenplatz versucht, bis einer gefunden wurde. Wenn Liste voll ist, wird -1 zurueckgegeben.
 \param s Student, der registriert werden soll
 \param nr Termin, an dem der Studierende registriert werden soll
 \return Termin, fuer den der Student angemeldet wurde
*/
int register_student(student *s, int nr);

/**
 *\brief Loescht einen Studierenden von der Liste. Wenn der Studierende nicht angemeldet war oder nicht existiert wird NULL zurueckgegeben.
 \param s Student, der von der Liste geloescht werden soll
 \return Bisheriger Listenplatz
*/
int remove_student(student *s);

/**
 *\brief Stellt die belegten Termine auf der LED-Bar dar.
*/
void display_absolute();

/**
 *\brief Berechnet den Mittelwert der Credits der angemeldeten Studenten und stellt ihn auf der LED-Bar dar.
 \return Prozentualer Wert als ganze Zahl.
*/
int display_average(void);





