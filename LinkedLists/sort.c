/*
 * Tanner Brown
 * TCSS 333 - Assignment 6
 * Winter 2018
 */

#include "sort.h"

/**
 * Created on: Feb 13, 2018
 * @author dschues1@uw.edu - original author
 *
 * @author Tanner Brown - modified slightly from given code for assignment
 * @param list - the list to be sorted
 * @param compare - a function that sorts two nodes
 */
void bubble_sort_linkedList(List **list, int (*compare)(List *one, List *two)) {

    int i, size, sorted = 0;
    List *prior, *current, *front;

    for (size = 0, current = *list; current; size++, current = current->next);

    size--;

    while (size && !sorted) {
        prior = NULL;
        current = *list;
        front = (*list)->next;
        sorted = 1;
        if (compare(*list, front) > 0) {
            sorted = 0;
            current->next = front->next;
            *list = front;
            front->next = current;
            front = current->next;
            prior = *list;
        } else {
            prior = current;
            current = front;
            front = front->next;
        }

        for (i = 0; front && i <= size; i++) {

            if (compare(current, front) >= 0) {
                sorted = 0;
                prior->next = front;
                current->next = front->next;
                front->next = current;
                prior = front;
                front = current->next;
            } else {
                prior = current;
                current = front;
                front = front->next;
            }
        }
        size--;
    }
}

