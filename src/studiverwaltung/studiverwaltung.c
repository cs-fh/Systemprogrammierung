/*
 * studiverwaltung.c
 *
 * Alle Funktionen zur Studi-Verwaltung sind in diesem Source File zu definieren.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#include "../include/studiverwaltung.h"


/* **************************** VORGABEN ********************************** */
/* Wrapper-Funktion um das systemeigene free() mocken zu koennen */
void sp_free(void *pt) {
    free(pt);
}
/* **************************** VORGABEN ********************************** */





    void show_all(node* list) {
        node *current = list;
        if(list->next == NULL) {
            printf("Liste leer.\n");
            return;
        }

    	while(current->next != NULL) {
    	    printf("[%s] ", current->next->stdnt->name);
    	    current = current->next;
    	}
    	printf("\n");
    }

    struct node* get_ifm_students(node* list) {
        node *ifm_list = (struct node *) malloc(sizeof(struct node));
        node *current, *n;
        if(list->next == NULL) return NULL;
        current = list->next;
        n = ifm_list;
        
        while(current != NULL) {
            if(current->stdnt->enrolled == IFM) {
                n->next = (struct node *)malloc(sizeof(struct node));
                n = n->next;
                n->stdnt = current->stdnt;
            }
            current = current->next;
        }
        show_all(ifm_list);
        return ifm_list;
    }

    node* append_student(node* list, student* newstdnt) {
        node *start;
        if(newstdnt == NULL) {
            return NULL;
        }
        if(list == NULL) {
            list = (struct node *) malloc(sizeof(struct node));
            list->stdnt = newstdnt;
            return list;
        }
        start = list;
        while(list->next != NULL) {
            list = list->next;
        }
        list->next = (struct node *) malloc(sizeof(struct node));
        list->next->stdnt = newstdnt;
        list->next->prev = list->next;
        list->next->next = NULL;
        return start;
    }
    
    node* delete_node(node* nodetodel,  sp_boolean X) {
        node *x, *prev, *next;
        if(nodetodel == NULL || !X) {
        	printf("neg");
            return NULL;
        }
        x = nodetodel;
        if(nodetodel->prev == NULL && nodetodel->next == NULL) {
            if(X == TRUE) {
                sp_free(nodetodel->stdnt);
            }
            sp_free(x);
            return NULL;
        }
        if(nodetodel->prev != NULL && nodetodel->next == NULL) {
            if(X == TRUE) {
                sp_free(nodetodel->stdnt);
            }
            printf("%s", nodetodel->prev->next->stdnt->name);
            /*(nodetodel->prev)->next = NULL; ==?*/
            x = nodetodel->prev;
            x->next = NULL;
            sp_free(nodetodel);
            nodetodel = NULL;
            return get_list_origin(x);
        }
        if(nodetodel->prev != NULL && nodetodel->next != NULL) {
            if(X == TRUE) {
                sp_free(nodetodel->stdnt);
            }
            printf("%s", nodetodel->stdnt->name);
            prev = nodetodel->prev;
            next = nodetodel->next;
            prev->next = next;
            next->prev = prev;
            sp_free(nodetodel);
            return get_list_origin(prev);
        }
        return NULL;
    }

    int delete_list(node* listnode) {
        
        int numberofdelnodes = 0;
        node *current = listnode;
        node *next = NULL;
	current = get_list_origin(listnode);
        while(current != NULL) {
            next = current->next;
            delete_node(current, TRUE);
            current = next;
            numberofdelnodes++;
        }
        return numberofdelnodes;
    }

    int delete_list_partial(node* listnode) {
        
        int numberofdelnodes = 0;
        node *current = listnode;
        node *next = NULL;
	current = get_list_origin(listnode);
        while(current != NULL) {
            next = current->next;
            delete_node(current, FALSE);
            current = next;
            numberofdelnodes++;
        }
        return numberofdelnodes;
    }

    node* get_list_origin(node* listnode) {
        if(listnode == NULL) {
            return NULL;
        }
        if(listnode->prev == NULL) {
            return listnode;
        } else {
            while(listnode->prev != NULL) {
                listnode = listnode->prev;
            }
            return listnode;
        }
    }



    


