/*
 * Tanner Brown
 * TCSS 333 - Assignment 6
 * Winter 2018
 *
 * NOTE TO PROF: This has been tested on lab computers, due to the problem currently
 * being faced on 5.
 */

/********** includes and prototypes *********/
#include "linkedlist.h"
#include "sort.h"

List *readFiles(FILE *, List *, int);

char validChar(char ch);
/*
 * Main function that drives program. Reads two text files and returns a sorted
 * count of the words that appear in the files.
 */
int main(){


    FILE *file1 = fopen("RedBadge.txt", "r");
    FILE *file2 = fopen("LittleRegiment.txt", "r");
    setvbuf(stdout, NULL, _IONBF, 0);

    if(!file1 || !file2)
        perror("Invalid file, please try again");
    else {

        List *list = createList();
        list = readFiles(file1, list, 1); //get words from file 1
        list = readFiles(file2, list, 2); //get words from file 2


        int wrdcnt = getSize(list) + 1;

        /***** Print Stuff ******/
        printf("There are (probably) %d unique words. \n\nSorted Alphabetically:\n", wrdcnt);
        print(list, wrdcnt);
        printf("\n\n--------------------------------------------\n\nSorted by difference:\n");
        bubble_sort_linkedList(&list, compare);
        print(list, wrdcnt);

        /***** ! Free Memory ! ****/
        freeList(list);

    }
    free(file1);
    free(file2);
    return 0;
}
/**
 * This function will read a file, parse out valid words, and insert them into the linked-list
 * @param file the file being read
 * @param list the linked-list of words
 * @param wordCount a count of the total words
 * @param fileNum the number of the file
 * @return the updated linked list
 */
List *readFiles(FILE *file, List *list, int fileNum) {
    int nodeCount, j, i;
    char word[25] = {'\0'};

    while (EOF != fscanf(file, "%s", word)) { //scan in the word

        if (word[0] != ' ' && strlen(word)!= 0) { //while a space or invalide character hasn't been found...
            i =  0;
            while((word[i] = validChar(word[i])) != '\0') { //while the character in the word is valid
                i++;
            }

            nodeCount += insert(&list, word, fileNum); //insert new word and update the count.
            //reset the word
            for(j = 0; j < 25; j++)
                word[j] = '\0';
        }
    }

    return list;
}
/**
 * This method determines if a char is valid for a word based on parameters
 * given by instructor.
 * @param ch the char being checked
 * @return the modified char.
 */
char validChar(char ch) {
    char ret = 0;

    if(ch >= 'A' && ch <= 'Z')
        ret = (char)tolower(ch);
    else if((ch >= 'a' && ch <= 'z') || ch == '\'' || ch == '-')
        ret = ch;
    else
        ret = '\0';

    return ret;
}