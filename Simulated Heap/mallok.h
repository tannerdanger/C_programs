/*
 * Tanner Brown
 * TCSS 333 - Winter 2018
 * Assignment 7
 */
#ifndef MALLOK_H
#define MALLOK_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct memory_Block {

    void* memAddr;
    void *data;
    size_t size;
    int isAvailable;
    struct memory_Block *next;

}Heap, Block;






void create_pool(int size);
void*my_malloc(int size);
void my_free(void *block);
void free_pool();

Block * splitBlock(Block *splitBlock, int size);
Block *createBlock(void *, size_t); //memory address/memorysize
void freeBlocks(Block**);

#endif //HW7_MALLOK_H