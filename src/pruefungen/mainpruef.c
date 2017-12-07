#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>



/*#include "./include/studiverwaltung.h"
#include "./include/ledbar.h"*/
#include "../include/pruefungen.h"



int main() {

    student *st1 = (struct student *) malloc(sizeof(struct student));
    strcpy(st1->name, "Rakshata");
    st1->cps = 10;
    st1->enrolled = IFM;
    student *st2 = (struct student *) malloc(sizeof(struct student));
    strcpy(st2->name, "Guido");
    st2->cps = 33;
    st2->enrolled = IFM;
    student *st3 = (struct student *) malloc(sizeof(struct student));
    strcpy(st3->name, "Diethard");
    st3->cps = 110;
    st3->enrolled = ELM;
    student *st4 = (struct student *) malloc(sizeof(struct student));
    strcpy(st4->name, "Hildegarn");
    st4->cps = 110;
    st4->enrolled = IFM;
    
    node *main_list = (struct node *) malloc(sizeof(struct node));
    node *node1 = (struct node *) malloc(sizeof(struct node));
    node1->stdnt = st1;
    node *node2 = (struct node *) malloc(sizeof(struct node));
    node2->stdnt = st2;
    node *node3 = (struct node *) malloc(sizeof(struct node));
    node3->stdnt = st3;
    node *node4 = (struct node *) malloc(sizeof(struct node));
    node4->stdnt = st4;
    main_list->next = node1;
    node1->prev = main_list; node1->next = node2;
    node2->prev = node1; node2->next = node3;
    node3->prev = node2; node3->next = node4;
    node4->prev = node3;
	
	show_all(main_list);

	node *ifm_list = get_ifm_students(main_list);
	node *lala = (struct node *) malloc(sizeof(struct node));
	lala->next = NULL; lala->prev = NULL;

	sp_boolean U = TRUE;
	delete_node(main_list, U);
	delete_node(lala, U);

	show_all(main_list);

	printf("%s\n", node1->stdnt->name); printf("%s\n", node2->stdnt->name);
	delete_list(main_list->next->next);
	show_all(main_list);
	printf("%s\n", node1->stdnt->name); printf("%s\n", node2->stdnt->name); printf("%s", node3->stdnt->name); printf("%s", node4->stdnt->name);
	
    int F = register_student(st1, 1);
    printf("=%d=\n", F);
    F = register_student(st1, 1);
    printf("=%d=\n", F);
    F = register_student(st1, 1);
    printf("=%d=\n", F);
 
    int result1 = register_student(st2, 9); result1 = register_student(st3, 9);
    printf("Student bei belegtem Termin 9: %d\n", result1);

    extern student* exams[10];
    memset(exams, 0, sizeof(student*) * 10);

    student std1 = {"Klaus", 20, IFM};
    student std2 = {"Peter", 26, IFM};
    student std3 = {"Eugen", 90, IFM};
    student std4 = {"RR", 268, IFM};
    student std5 = {"Dosenkohl", 305, IFM};
    
    exams[0] = &std1;
    exams[4] = &std2;
    exams[3] = &std3;
    exams[7] = &std4;
    exams[9] = &std5;
int pp = display_average();
printf("%s - %d", exams[7]->name, pp);


}
