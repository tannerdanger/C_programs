/*
 * Tanner Brown
 * TCSS 333 - Assignment 4
 * Winter 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>


#define COLORSPERPIXEL 3
#define HEADERSIZE 54
#define CHECKERS 8
#define WIDTH_HEADER_LOC 18

void processFiles(FILE *file1, FILE *file2, size_t fileSize);

unsigned long getSize(char *s);

void checkerBoardPattern (unsigned char *file1,
                          unsigned char *file2, size_t fileSize);


void blendImages(unsigned char *file1, unsigned char *file2, size_t fileSize);

/**
 * This program accepts two image files as command line arguments and
 * creates two new images by minipulating the user given ones.
 *
 * @param argc the number of arguments
 * @param argv the arguments
 * @return 0
 */
int main (int argc, char **argv) {

    unsigned long fileSize, fileSize2;
    FILE *file1, *file2;
    int f1Exists = 0, f2Exists = 0;
    char *f1 = *++argv;
    char *f2 = *++argv;


    if(argc == 3) { //3 arguments given by user minimum for 2 image files
        if (f1Exists = (long)(fileSize = getSize(f1)) >= 0){
            file1 = fopen(f1, "rb");
        }
        if (f2Exists =(long)(fileSize2 = getSize(f2)) >= 0) {
            file2 = fopen(f2, "rb");
        }

        if(!f1Exists || !f2Exists){
            perror("Failed to open outputImage. Please check file path and try again...\nExiting program\nError");
        }
    }


    if(f1Exists && f2Exists){
        if(fileSize2 == fileSize)
            processFiles(file1, file2, fileSize);
        else{
            perror("Image sizes do not match, please try again...\nExiting program\nError");
        }


        /***********! Free Memory !********/
        //free memory, fclose files
        fclose(file1);
        fclose(file2);
    }
    return  0;
}

/**
 * This function determines the size of the files given.
 * @param s the name of the file
 * @return unsigned long size of file.
 */
unsigned long getSize(char *s){
    unsigned long size = -1;
    struct stat file_info;
    if(stat(s, &file_info) > -1){
        size = (unsigned long)(file_info.st_size);
    }
    return (unsigned long)size;
}

/**
 * This function processes the files and ensures they are the
 * right format to continue.
 * @param file1 the first file being used
 * @param file2 the second file being used
 * @param fileSize the size of the files.
 */
void processFiles(FILE *file1, FILE *file2, size_t fileSize) {
    void *fileData1, *fileData2;
    unsigned char *fileType1, *fileType2;
    fileData1 = (void *)malloc(fileSize);
    fileData2 = (void *)malloc(fileSize);

    //Two freads
    fread(fileData1, fileSize, 1, file1);
    fread(fileData2, fileSize, 1, file2);

    fileType1 = (unsigned char *)fileData1;
    fileType2 = (unsigned char *)fileData2;

    if((*fileType1 == 'B' && *++fileType1 == 'M') &&
       (*fileType2 == 'B' && *++fileType2 == 'M')){
        checkerBoardPattern(fileData1, fileData2, fileSize);
        blendImages(fileData1, fileData2, fileSize);
    }else{
        perror("Image was not a bmp file, please check file type and try again...\nExiting program\nError");
    }
    /***********! Free Memory !********/
    free(fileData1);
    free(fileData2);
}
/**
 * This function creates a checkerboard pattern by alternating between
 * two images.
 * @param file1 the first image file.
 * @param file2 the second image file.
 * @param fileSize the size of the image files.
 */
void checkerBoardPattern (unsigned char *file1, unsigned char *file2, size_t fileSize){

    FILE *checkerBoardFile = fopen("checker.bmp", "wb");

    //Get width from header locations and multiply by 256 to get 16bit width
    int width = *(file2 + WIDTH_HEADER_LOC) + (*(file2 + WIDTH_HEADER_LOC+1) * 256);

    // 3 bits per width for RBG colors, divided by amount of checkers
    int width_per_checker = (width * COLORSPERPIXEL) / CHECKERS;

    //determines if it will be printing data from file 1 or not
    bool printFromFile1 = true;
    unsigned char *outputImage;
    outputImage = malloc(fileSize);

    int i, row, col, pixelCount;
    i = row = 0;
    pixelCount = -1;

    //copy bmp header data
    while(pixelCount++ < 54){
        *(outputImage + pixelCount) = *(file1 + pixelCount);
    }

    // 8x8 checker pieces
    for ( ;  row < CHECKERS;  row++) {
        for ( col = 0;  col < width; i = 0, col++) {
            if(printFromFile1) { //print all data from file 1
                for (; i < width_per_checker; i++, pixelCount++) {
                    *(outputImage + pixelCount) = *(file1 + pixelCount);
                }
            }else{ //print all data from file 2
                for (; i < width_per_checker; i++, pixelCount++) {
                    *(outputImage + pixelCount) = *(file2 + pixelCount);
                }
            }printFromFile1 = ((col % 2) == (row %2) && pixelCount < fileSize);
        }
    }
    // write bmp checker board data to the file
    fwrite(outputImage, sizeof(char), fileSize, checkerBoardFile);

    /***********! Free Memory !********/
    fclose(checkerBoardFile);
    free(outputImage);
}

/**
 * This function blends two images together.
 *
 * @param file1 the first image file.
 * @param file2 the second image file.
 * @param fileSize the size of the image files.
 */
void blendImages(unsigned char *file1, unsigned char *file2, size_t fileSize){

    FILE *blendFile = fopen("blend.bmp", "wb");

    unsigned char *outImage;
    unsigned  char *imgPointer;
    int pixelIndex = 0;
    outImage = malloc(fileSize);
    imgPointer = outImage;


    for ( ; pixelIndex < fileSize; pixelIndex++) {
        if(pixelIndex >= HEADERSIZE)
            *(imgPointer+pixelIndex) = (*(file1+pixelIndex)/2 + *(file2+pixelIndex)/2);
        else
            *(imgPointer+pixelIndex) = *(file1+pixelIndex);
    }
    fwrite(outImage, sizeof(char), fileSize, blendFile);

    /***********! Free Memory !********/
    free(outImage);
    fclose(blendFile);
}
