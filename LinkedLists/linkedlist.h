/*
 * Tanner Brown
 * TCSS 333 - Assignment 6
 * Winter 2018
 */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "linkedlist.h"
//#include "sort.h"


//Node definition
typedef struct node {
    char name[10];
    int f1_count;
    int f2_count;
    int difference;
    struct node *next;
}Node, List;

//Prototypes
Node *createList(void);
int insert(List **, char *, int);
void insertAtBeginning(List **, Node *);
int compare(Node *a, Node *b);
void print(List *, int i);
void freeList(List *);
int getSize(List *);


#endif //ASSIGNMENT6_LINKEDLIST_H