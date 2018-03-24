/**
 * Tanner Brown
 * TCSS 333 - Winter 2018
 * Assignment 8
 */
#include <stdio.h>
#include <stdlib.h>

struct bit_data {
    unsigned int bit : 32;
};
typedef union bitFloat{
    float f;
    struct bit_data bits;
}BitFloat;

//is x negative? If so, make it positive and return b as true.
#define IS_NEG(x, b) (((x)<(0))?((x)=(-x)), (b) = 1:(x))

char* binary(BitFloat theFloat);
float getFloat(float, float, float);

int main() {

    FILE* inFile = fopen("hw8in.txt", "r");
    if(inFile) {

        union bitFloat myBitFloat;
        float f;
        float x, y, z;

        while(!feof(inFile)){
            fscanf(inFile, "%f %f %f", &x, &y, &z); //get values

            f = getFloat(x,y,z); //convert to float

            printf("Floating point format of    %.15f:\n", f); //print float

            myBitFloat.f = f; //assign float to union

            char *printStr = binary(myBitFloat); //get binary value string

            printf("       %s\n", printStr);

            free(printStr); //free each loop to free allocated memory in function.
        }
        fclose(inFile);
    }
    return 0;
}
/**
 * Takes 3 numbers, if they are negative it converts them to positive,
 * adds x to y/z, and returns it to negative if it was originally negative.
 *
 * @param x the value to be added
 * @param y the numerator
 * @param z the denominator
 * @return the result
 */
float getFloat(float x, float y, float z){
    int isNeg = 0;
    IS_NEG(x, isNeg);
    IS_NEG(y, isNeg);
    IS_NEG(z, isNeg);
    float retFl = x + (y/z);
    if(isNeg) retFl *= -1;

    return retFl;
}
/**
 * Function takes a float and converts it into a 32bit binary number
 * represented by a string.
 *
 * @param theFloat a union with an associated float value
 * @return a binary representation of theFloat in a char array.
 */
char* binary(BitFloat theFloat) {
    char *bitString = malloc(sizeof(char) * 34);//{'\0'};
    int i, j, k, n;
    n = theFloat.bits.bit;
    for (i = 0, j = 33 ; i < 32; i++, j--) {
        if (i == 23 || i == 31)
            bitString[j--] = ' ';
        k = n >> i;
        if (k & 1)
            bitString[j] = '1';
        else
            bitString[j] = '0';
    }return bitString;
}