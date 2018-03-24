/**
 * Tanner Brown
 * TCSS 333 - Assignment 2
 * Winter - 2018
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_NAME_LENGTH 25  /* Max length of a name. */
#define MAX_NAMES 1000     /* Max possible names would be 1000, although its not likely. */
#define YEARS 10           /* Number of years that is being compared. */

/********************** Prototypes *******************/
void read_all_files(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS],
                    char**files);

void read_single_file(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS],
                      FILE*inputFile, int*fileCounter);

void check_and_add(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS],
                   char*newName, int rankIndex, int*fileCounter);

void sort_names(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int low, int high);

void sort_three(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int low, int mid, int high);

void swap_names(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int low, int high);

void create_output(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], char**header);
/*********************** End Prototypes **************/

/**
 * Main function that drives the program.
 * @return 0 - no return.
 */
int main (void){

    /* The file names being read. */
    char *files[] = {"yob1920.txt", "yob1930.txt", "yob1940.txt", "yob1950.txt",
                     "yob1960.txt", "yob1970.txt", "yob1980.txt", "yob1990.txt",
                     "yob2000.txt", "yob2010.txt"};

    /* The header for the output csv file. */
    char *output_header[] = {"name",
                             "1920", "1930", "1940", "1950", "1960",
                             "1970", "1980", "1990", "2000", "2010"};

    /*
     * A char array of names. First dimension is a total list of names,
     * second dimension is an array of chars that spells the name.
     */
    char names[MAX_NAMES][MAX_NAME_LENGTH] = {'\0'};
    /**
     * Rankings of each name. First dimension is total list of names
     * that corresponds to the first dimension of the names array.
     * Second dimension is size of 10 and each value holds the ranking of
     * the name in the first array for each of the 10 years.
     */
    int name_ranks[MAX_NAMES][YEARS];

    //Go down the rabbit hole to gather all data
    read_all_files(names, name_ranks, files);

    //Print all names for testing
    int i = 0;


    //write output
    create_output(names, name_ranks, output_header);

    return 0;
}
/**
 * This function reads all files and sends the data to another function
 * to be interpereted.
 * @param names a char array of the names.
 * @param name_ranks an int array of the rankings.
 * @param files a char array of filenames to open.
 */
void read_all_files(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], char**files){

    int i;
    /*
     * Open the files.
     */
    FILE *name_file[YEARS];
    for(i = 0; i < YEARS; i++){
        name_file[i] = fopen(files[i], "r");
    }

    /*
     * Reads a single file at a time and gathers the data from that file.
     */
    for(i = 0; i < 10; i++){
        read_single_file(names, name_ranks, name_file[i], i);
    }

    i = 0;
    while(*names[i++] != '\0');

    /* Quick sort the names into alphebetical order. */
    sort_names(names, name_ranks, 0, i-2);

    /*
     * Note: I wasn't sure if just doing fclose(name_file) worked,
     * so I did this just to be safe.
     */
    for(i = 0; i < YEARS; i++){
        fclose(name_file[i]);
    }
}

/**
 * This function reads a single file and gathers
 * all of the necessary data.
 *
 * @param names a char array of the names.
 * @param name_ranks an int array of the rankings.
 * @param inputFile the file being read
 * @param fileCounter a counter of the file number to be used in ranking.
 */
void read_single_file(char (*names)[MAX_NAME_LENGTH],
                      int (*name_ranks)[YEARS], FILE*inputFile, int*fileCounter){

    /*
     * counts the line number which is associated with name ranking
     * Counts the commas for parsing the line.
     * for indexing the characters in the line
     */
    int rankIndex = 0, rowIndex, comma_index;
    //new line to be printed on;
    char *newLine = NULL;
    //length of new line
    size_t lineLength = 0;

    //read top 100 names from file
    for(rankIndex = 0; rankIndex < 100; rankIndex++){

        //reset values
        comma_index = 0;
        rowIndex = 0;
        //get data from the next line
        getline(&newLine, &lineLength, inputFile);
        //create a temp array that holds the name from the file
        char newName[MAX_NAME_LENGTH] = "\0";

        //Get name from left of first comma and save it to newName.
        while(rowIndex < MAX_NAME_LENGTH && comma_index == 0) {

            if (newLine[rowIndex] == ',') {
                comma_index = rowIndex;
            } else {
                newName[rowIndex] = newLine[rowIndex];
                rowIndex++;
            }
        }


        //Call to method to check and see if new name already exists.
        check_and_add(names, name_ranks, newName, rankIndex, fileCounter);
    }
}

/**
 * Checks if new name exists in array, and if it doesn't it adds it to the end.
 *
 * @param names - array of names
 * @param name_ranks - the array of ranks associated with name popularity
 * @param newName - the new name to be added to the array
 * @param rankIndex - the rank of the current name in the top 100 list of names.
 */
void check_and_add(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS],
                   char*newName, int rankIndex, int*fileCounter){

    bool nameFound = false;
    int i = 0, year;
    year = (int)fileCounter;
    //check if name exists, then add it.
    while(!nameFound && *names[i] != '\0' ){
        if(strcmp(names[i], newName) == 0){
            nameFound = true;
            name_ranks[i][year] = rankIndex +1;
        }else
            i++;
    }
    //if name wasn't found...
    if(!nameFound){
        strncpy(names[i], newName, sizeof names[i]);
        name_ranks[i][year] = rankIndex +1;
        names[0][sizeof(names[0]) - 1] = 0; // making sure to add the \0 byte
    }
}

/**
 * Utilizes quicksort to sort the names in the array.
 *
 * NOTE: This function and its helper functions sort_three and swap_names
 * are based off code written by myself for another class, repurposed
 * for this assignment.
 *
 * @param names the array of names
 * @param name_ranks the array defining the popularity rank of each name.
 * @param low the lower index in the unsorted portion of the array
 * @param high the higher index in the unsorted portion of the array.
 */
void sort_names(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int low, int high){
    int j, i = 0;
    int mid;
    int pivot;
    bool loop = true; //a value that indicates when to quit the partitioning loop.

    mid = ( low + high ) / 2;
    //sort the low, mid, and high elements
    sort_three(names, name_ranks, low, mid, high);


    if(high - low <= 2) {
        if(high - low ==2)
            sort_three(names, name_ranks, low, mid, high);
        if(high - low == 1)
            if(high < low)
                swap_names(names, name_ranks, low, high);
    }else{

        //move the pivot to high-1
        swap_names(names, name_ranks, mid, high-1);

        //Define the pivot
        pivot = high-1;
        i = low, j = high-1;
        //begin partitioning
        while(loop) {

            while (i < high-1 && strcmp(names[++i], names[pivot]) < 0);//increment i if < pivot
            while (j > low && strcmp(names[--j], names[pivot]) >= 0);//decrement j if > pivot

            if (i >= j)
                loop = false;

            else
                swap_names(names, name_ranks, i, j);
        }
        //Recurse lower half of unsorted portion.
        sort_names(names, name_ranks, low, i - 1);
        //Recurse upper half of unsorted portion.
        sort_names(names, name_ranks, i, high);
    }
}
/**
 * Helper method that sorts three values. Used for picking
 * high/low/med points and for sorting values when there
 * are 3 or less remaining in an unsorted partition.
 *
 * @param names the array of names
 * @param name_ranks the array defining the popularity rank of each name.
 * @param low the lower index to be sorted.
 * @param mid the middle index to be sorted.
 * @param high the higher index to be sorted.
 */
void sort_three(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int low, int mid, int high){

    //if low > high
    if(strcmp(names[low], names[high]) >0)
        swap_names(names, name_ranks, low, high);

    if(strcmp(names[low], names[mid]) >0)
        swap_names(names, name_ranks, low, mid);

    if(strcmp(names[mid], names[high]) >0)
        swap_names(names, name_ranks, mid, high);
}

/**
 * Helper method that swaps names and ranks as determined
 * by the quicksort method.
 *
 * @param names the array of names
 * @param name_ranks the array defining the popularity rank of each name.
 * @param index1 index of the first value to be swapped.
 * @param index2 index of the second value to be swapped.
 */
void swap_names(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], int index1, int index2){

    char tempName[MAX_NAME_LENGTH];
    int tempranks[YEARS];

    //pass index 1 to temp
    strncpy(tempName, names[index1], sizeof tempName);
    //pass index 2 to index 1
    strncpy(names[index1], names[index2], sizeof names[index1]);
    //pass temp to index 2
    strncpy(names[index2], tempName, sizeof names[index2]);

    //swap ranks at year i
    for(int i = 0; i < 10; i++) {
        //pass rankings of index 1 to temp array
        tempranks[i] = name_ranks[index1][i];
        //pass rankings of index 2 to index 1
        name_ranks[index1][i] = name_ranks[index2][i];
        //pass rankings of temp to index 2
        name_ranks[index2][i] = tempranks[i];
    }
}

/**
 * Creates the output csv file named "summary.csv" based on data
 * collected in the other functions.
 * @param names an array of names.
 * @param name_ranks an int array of names.
 * @param header a char array of data to go into the top row of the csv file.
 */
void create_output(char (*names)[MAX_NAME_LENGTH], int (*name_ranks)[YEARS], char**header){

    FILE *output = fopen("summary.csv", "w");
    //Write the header
    for(int i = 0; i <= YEARS; i++){
        fprintf(output, "%s,", header[i]);
    }
    //Move down a line
    fprintf(output, "\n");
    //Print all other data to file.
    for(int i = 0; i < MAX_NAMES && names[i] != '\0'; i++){
        fprintf(output, "%s,", names[i]);
        for(int j = 0; j < YEARS; j++){
            if(name_ranks[i][j] != 0)
                fprintf(output, "%d,", name_ranks[i][j]);
            else
                fprintf(output, ",");
        }
        fprintf(output, "\n");
    }
    fclose(output);
}