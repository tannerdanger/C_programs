/*
 * Tanner Brown
 * TCSS 333 - Winter 2018
 * Assignment 7
 */
#include <stdio.h>
#include "mallok.h"


void test1();
void test2();
void test3();
void test4();
void test5();
/**
 * This file runs 5 seperate tests on the mallok.c program.
 * @return
 */
int main(void) {

    test1();
    test2();
    test3();
    test4();
    test5();

return 0;
}
void test1(){



    //insert(&heapList, 'a', 1000, 5000);

    create_pool(1000);
    int mal_ctr = 0;
    while(NULL != my_malloc(100)) {
        mal_ctr++;
    }
    if(mal_ctr == 10){
        printf("Test 1 Success! Was able to allocate the correct amount of memory.\n\n");
    }else
        printf("Test 1 FAILED! Was able to allocate 10 byte of memory %d times.  Correct amount of times should be 100\n\n", mal_ctr);


    free_pool();

    //create pool of 1000 bytes
    //count how many times you can successfully request a block of size 10
    //free pool

}

void test2(){

    create_pool(1000);//create pool of 1000 bytes
    int failed = 0;

    void*p[5];
    int i, j;

    for(i = 0; i < 10; i++){

        //make 5 requests for blocks of 200 bytes
        for(j = 0; j < 5; j++) {
            p[j] = my_malloc(200);
        }

        //free all 5 blocks
        for(j = 0; j < 5; j++) {
            my_free(p[j]);
            p[j] = NULL;
        }
    }

    for(int i = 0; i < 5; i++){
        if(p[i])
            failed = 1;
    }

    if(failed)
        printf("Test 2 Failed.\n\n");
    else
        printf("Test 2 Passed.\n\n");


    //repeat this request/free pattern several times to make sure you can reuse blocks after they are returned
    free_pool();
}

void test3(){

    //create pool of 1000 bytes
    create_pool(1000);
    void*p[5];
    //make 5 requests for blocks of 200 bytes
    for(int i = 0; i < 5; i++){
        p[i] = my_malloc(200);
    }
    //free the middle block
    my_free(p[3]);
    p[3] = NULL;

    //Test 3a: request a block of 210 bytes (should fail)
    p[3] = my_malloc(210);
    if(!p[3]){
        printf("Test 3a Success! Did not allocate size too big\n");
    }else if(p[3]){
        printf("\nTest 3a FAILED!! Was able to allocate memory that exceeded heap size\n");
    }
    my_free(p[3]);
    p[3] = NULL;

    //Test 3b: request a block of 150 bytes (sould succeed)
    p[3] = my_malloc(150);
    if(p[3])
        printf("Test 3b Success!\n");
    else
        printf("Test 3b FAILED!!\n");

    //Test 3c: request block of 60 bytes (should fail)
    void*p2 = my_malloc(60);
    if(p2)
        printf("Test 3c FAILED!! Should not have been able to allocated 60 blocks of memory\n");
    else
        printf("Test 3c Success!\n");

    //request block of 50 bytes (should succeed)
    void*p3 = my_malloc(50);
    if(p3)
        printf("Test 3d Success!\n\n");
    else
        printf("Test 3d FAILED!!\n\n");
    //etc


    free_pool();
}

void test4(){

    //create a pool of 1000 bytes.
    create_pool(1000);
    //Request 5 blocks of 200 bytes.
    void *p1, *p2, *p3, *p4, *p5;
    int test[5];
    for(int i = 0; i < 5; i++)
        test[i] = 1;
    char *letPnt;

    p1 = my_malloc(200);
    memset(p1, 'a', 200);
    p2 = my_malloc(200);
    memset(p2, 'b', 200);
    p3 = my_malloc(200);
    memset(p3, 'c', 200);
    p4 = my_malloc(200);
    memset(p4, 'd', 200);
    p5 = my_malloc(200);
    memset(p5, 'e', 200);

    for(letPnt = (char*)p1; letPnt<(char*)+200; ++letPnt)
        test[0] = (*letPnt == 'a');

    for(letPnt = (char*)p1; letPnt<(char*)+200; ++letPnt)
        test[1] = (*letPnt == 'b');

    for(letPnt = (char*)p1; letPnt<(char*)+200; ++letPnt)
        test[2] = (*letPnt == 'c');

    for(letPnt = (char*)p1; letPnt<(char*)+200; ++letPnt)
        test[3] = (*letPnt == 'd');

    for(letPnt = (char*)p1; letPnt<(char*)+200; ++letPnt)
        test[4] = (*letPnt == 'e');


    for(int i = 0; i < 5; i++){
        if(test[i])
            printf("Test 4 - %d PASSED\n", i);
        else
            printf("Test 4 - %d FAILED\n", i);
    }

    printf("\n\n");
    // Fill the first block with the letter 'A', the second block with 'B', etc.
    // Verify that the values stored in each block are still there. (Is the first block full of A's, second block full of B's, etc.)
    free_pool();
}

void test5(){
    //create a pool of 1000 bytes.
    create_pool(1000);
    void *p[10];
    for(int i = 0; i < 10; i++){
        p[i] = NULL;
    }
    int failed = 0;

    //5a Request and return a block of 1000 byte
    p[0] = my_malloc(1000);
    if(p[0]){
        printf("Test 5a passed\n");
        my_free(p[0]);
        p[0] = NULL;
    }else{
        printf("test 5a Failed, could not allocate block of size 1000\n");
    }

    //5b  Request and return four blocks of 250 bytes
    for(int i = 0; i < 4; i++) {
        p[i] = my_malloc(250);
    }
    for(int i = 0; i < 4; i++) {
        if(p[i]) {
            my_free(p[i]);
            p[i] = NULL;
        }else{
            failed = 1;
        }
    }

    if(failed){
        printf("Test 5b failed to allocated 4 blocks of 250 memory.\n");
    }else{
        printf("Test 5b Passed\n");
    }

    failed = 0;

    // Test 5c Request and return ten blocks of 100 bytes
    for(int i = 0; i < 10; i++) {
        p[i] = my_malloc(100);
    }

    for(int i = 0; i < 10; i++) {
        if(p[i]) {
            my_free(p[i]);
            p[i] = NULL;
        }else{
            failed = 1;
        }
    }
    if(failed){
        printf("Test 5c failed to allocated 10 blocks of 100 memory.\n");
    }else{
        printf("Test 5c Passed\n");
    }

    free_pool();

}


