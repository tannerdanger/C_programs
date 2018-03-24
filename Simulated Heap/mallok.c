/*
 * Tanner Brown
 * TCSS 333 - Winter 2018
 * Assignment 7
 */
#include <stdlib.h>
#include "mallok.h"


//Version2.1

static void*privateHeap;
static int availHeapSize;
static Block *front; //the head of the memory heap

/**
 * Recieves an integer representing the requested size for a heap.
 *
 * @param size - indicates how many bytes should be included in the heap.
 */
void create_pool(int size){


    if(!privateHeap){ //if heap isn't null
        privateHeap = malloc((size_t)size); //allocate memory of size size.
        availHeapSize = size;
        front = NULL;
    }
}

/**
 * Searches the block list for the FIRST free block that is big enough to satisfy requested size.
 * Returns a piece of the private heap if possible
 * @param size size of the block
 * @return a allocated piece of the heap, or NULL if unsatisfied.
 */
void*my_malloc(int size) {


    void *returnValue = NULL; //Define as null so it returns null if no block placed.

    if(size <= availHeapSize) {
        Block *current, *back, *newBlock;

        //list hasn't been created yet, insert first node.
        if (!front) {
            front = createBlock(privateHeap, (size_t) size);
            returnValue = (void *)front->memAddr;
        } else {
            current = front;
            while (NULL != current && (current->size < size || !current->isAvailable)){
                back = current;
                current = current->next;
            }

            //if found block is too big
            if (current && current->size > size) {
                newBlock = splitBlock(current, size);
                returnValue = (void *)newBlock->memAddr;

            //if found block is the right size
            }else if(current && current->size == size) {
                returnValue = (void *) current->memAddr;
                current->isAvailable = 0;
                current->size = (size_t) size;

            //if not block is found
            }else if(!current && back){
                    newBlock = createBlock(back->memAddr+size, size);
                    back->next = newBlock;
                    returnValue = newBlock->memAddr;
            }
        }//update heap size if block was placed.
        if (returnValue) {
            availHeapSize -= size;
        }
    }
    return returnValue;
}
/**
 * Frees a block of memory, and combines it with neighboring blocks
 * if applicable.
 * @param block the address of the block being freed.
 */
void my_free(void *block){

    if(block) {
        Block *scanBlock, *prior;
        scanBlock = front;
        prior = NULL;

        //find the block via its start address
        while(scanBlock && (void*)scanBlock->memAddr != block){
            prior = scanBlock;
            scanBlock = scanBlock->next;
        }
        if(scanBlock){
            scanBlock->isAvailable = 1;
            availHeapSize+=scanBlock->size;

            //Combine with next if available.
            if(scanBlock->next && scanBlock->next->isAvailable) {
                scanBlock->size += scanBlock->next->size;
                scanBlock->next = scanBlock->next->next;
            }

            //Combine with prior if available.
            if (prior && prior->isAvailable) {
                prior->size += scanBlock->size;
                prior->next = scanBlock->next;
            }
        }
    }
}

/**
 * This function splits a block that has too much memory by creating a
 * new memory block on the end of the desired size.
 *
 * @param splitBlock the block of memory being split
 * @param size the size of the new memory block
 * @return the new memory block.
 */
Block*splitBlock(Block *splitBlock, int size) {

    Block *temp = createBlock(splitBlock->memAddr + splitBlock->size-size, size);
    if(splitBlock->next)
        temp->next = splitBlock->next;

    splitBlock->next = temp;

    //decrement size of block that is shrinking
    splitBlock->size -= size;

    return temp;
}
/**
 * Function that creates a new block of memory from
 * a given address and given size.
 * @param addr the address the block will start at.
 * @param theSize the size of the memory block.
 * @return the new block of data.
 */
Block *createBlock(void* addr, size_t theSize) {
    Block *dataBlock = (Block *)malloc(sizeof(Block));
    dataBlock->size = theSize;
    dataBlock->memAddr = addr;
    dataBlock->isAvailable = 0; //not freed
    dataBlock->next = NULL;

    return dataBlock;
}
/**
 * A function that frees the memory from the heap.
 */
void free_pool(){

    if(front){
        freeBlocks(&front); //Go to recursive method for freeing.
        availHeapSize = 0;
        free(privateHeap);
        privateHeap = NULL;
    }
}

/**
 * Helper method that recursively frees blocks
 * @param theBlock the block being free'd
 */
void freeBlocks(Block **theBlock) {

    if (*theBlock) {
        freeBlocks(&(*theBlock)->next);
        if ((*theBlock)->data) {
            free((*theBlock)->data);
        }
        (*theBlock)->data = NULL;
        (*theBlock)->memAddr = NULL;
        (*theBlock)->size = 0;
        (*theBlock)->next = NULL;
        (*theBlock)->isAvailable = 0;
        free(*theBlock);
        *theBlock = NULL;
    }
}