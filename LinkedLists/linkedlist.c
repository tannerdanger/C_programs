/*
 * Tanner Brown
 * TCSS 333 - Assignment 6
 * Winter 2018
 */

#include "linkedlist.h"


Node *createList(void) {
    return NULL;
}

/**
 * Linked List definition file: linkedlist.c
 *
 * created on: Feb 13, 2018
 * @author dschues1@uw.edu - original author
 * @author Tanner Brown - modified slightly to meet assignment standards
 * @param list a pointer to this list
 * @param name the name of the node i.e. the word being added
 * @param fileNum the file being read
 * @return 1 ot 0, depending on if the word is a new one or not.
 */
int insert(List **list, char *name, int fileNum) {
    int isNewNode = 0;


    if(name != NULL && name[0] != ' ' && name[0] != '\0') { //catch-all
        isNewNode = 1;
        Node *searchNode, *back = NULL;
        Node *newNode = malloc(sizeof(Node));
        strcpy(newNode->name, name);

        if (fileNum == 1) {
            (*newNode).f1_count = 1;
            (*newNode).f2_count = 0;
        }
        if (fileNum == 2) {
            (*newNode).f1_count = 0;
            (*newNode).f2_count = 1;
        }
        newNode->next = NULL;

        if (*list == NULL) { // Insert the very first node to the list:
            *list = newNode;

        } else {
            searchNode = *list;
            while (searchNode != NULL && (strcmp(searchNode->name, name) < 0 || strcmp(searchNode->name, name) == 0)) {
                back = searchNode;
                searchNode = searchNode->next;
            }

            if (searchNode == *list) {
                insertAtBeginning(list, newNode);

            }else if (strcmp(name, back->name) == 0) {

                if (fileNum == 1)
                    back->f1_count++;
                if (fileNum == 2)
                    back->f2_count++;

              //  back->difference = abs(back->f1_count - back->f2_count);
                isNewNode = 0; //not a new word

            } else if (searchNode == NULL) {       // insert at the end:
                newNode->next = back->next;  //yeah, I know, its already NULLL
                back->next = newNode;

            } else {                         // insert in the middle:
                newNode->next = searchNode;
                back->next = newNode;
            }
        }
    }
    return isNewNode;
}
/**
 * Inserts a node at the beginning of the list
 * @param theList the linked list
 * @param theNode the node being inserted
 */
void insertAtBeginning(List ** theList, Node * theNode){
    theNode->next = *theList;
    *theList = theNode;
}

/**
 * Compares two nodes for sorting
 * @param a first node
 * @param b second node
 * @return int value determinging the sorting weight of each node.
 */
int compare(Node *a, Node *b){
    int retVal = abs(b->f1_count - b->f2_count) - abs(a->f2_count - a->f1_count);

    if(!retVal)
        retVal = (int)(strlen(b->name) - strlen(a->name));

    if(!retVal)
        retVal = strcmp(a->name, b->name);

    return retVal;
}

/**
 * Prints the list of words. I know this
 * @param list the list
 * @param nodeCount a count of total words
 */
void print(List *list, int nodeCount) {
    if(list){
        printf("\nFirst 25 words:\n");
        int i = 0;
        int stop = nodeCount-5;
        Node *printNode = list;
        for( ; i < 9; i++){
            printf("%d. %25s   RedBadge.txt:   %10d,     LittleRegiment.txt:   %10d,   "
                           "Difference:  %10d\n", i+1, printNode->name, printNode->f1_count, printNode->f2_count, abs(printNode->f1_count - printNode->f2_count));
            printNode = printNode->next;
        }
        //print 9-25, slight formatting changes
        for( ;i < 25; i++){
            printf("%d.%24s    RedBadge.txt:   %10d,     LittleRegiment.txt:   %10d,   "
                           "Difference:  %10d\n", i+1, printNode->name, printNode->f1_count, printNode->f2_count, abs(printNode->f1_count - printNode->f2_count));
            printNode = printNode->next;
        }
        printf("\nLast 5 words:\n");
        while(++i < stop){
            printNode = printNode->next;
        }
        while(++i <= nodeCount){
            printf("%d. %20s     RedBadge.txt:   %10d,     LittleRegiment.txt:   %10d,   "
                           "Difference:  %10d\n", i+1, printNode->name, printNode->f1_count, printNode->f2_count, abs(printNode->f1_count - printNode->f2_count));
            printNode = printNode->next;
        }
        printf(" ");
    }
}


/**
 * Frees the memory and clears the list.
 * @param list
 */
void freeList(List *list) {
    if (list) {
        freeList(list->next);
        free(list);
    }
}
/**
 * Gets the size of the list.
 *
 * NOTE: I originally had a counter for list size, but it caused a problem with memory and I didn't have
 * time to debug it so I did this. I ended up fixing the problem, but didn't
 * have time to re-implement the counter, kept this function. I know its not the best but
 * it worked.
 * @param list the list being counted
 * @return the size of the list.
 */
int getSize(List *list){
    int count = 0;
    if(list){
        Node *n = list;
        while(n){
            count++;
            n = n->next;
        }
    }
    return count;
}