/*
 * Tanner Brown
 * TCSS 333 - Programming Assignment 2 - Image Manipulation
 * Winter 2018
 */

/**
 * This program reads the headers of two 24bit Bitmap images, and uses that
 * info to create two new images.
 * One image being a blend of the two images, where each pixel is the average
 * of the same pixel on both images.
 *
 * The second image is a checkerboard style image that alternates each image
 * in a checkerboard fashion.
 *
 * This program SHOULD work on all 24bit bmp images that are similar in size,
 * but has only been tested on the provided in1/in1a, and in2/in2a bmp files.
 *
 * @author Tanner Brown
 * @version 23 Jan 2018
 *
 */
#include <stdio.h>
#include <stdlib.h>
#define COLORSPERPIXEL 3;
#define CHECKERBOARDSIZE 8;
#define HEADERSIZE 54;

void checkerBoardPattern(unsigned char *firstImage, unsigned char *secondImage, int imgSize, int imgWidth);

void blendImages(unsigned char *firstImage, unsigned char *secondImage, int imgSize);

//unsigned char blendPixels(unsigned char *firstImage, unsigned char *secondImage, int pixelIndex);


int main(void) {


    int img1Width, img1Height, img2Width, img2Height,
            finalImageSize, finalImageWidth,img1Size, img2Size;

    unsigned char headerFirstImg[54], headerSecondImg[54];

    /*************** open image files ***************/
    FILE *infileFirstImg = fopen("in1.bmp", "rb");
    FILE *infileSecondImg = fopen("in2.bmp", "rb");

    if(infileFirstImg == (FILE *)0 || infileSecondImg == (FILE *)0){
        perror("Failed to open image. Please check filepath and try again...\nExiting program\nError");
        exit(0);
    }

    /******* Get important data from header ************/
    fread( headerFirstImg, 1 , 2 , infileFirstImg);
    fread( &img1Size, sizeof(int) , 1,  infileFirstImg); //get the image size

    fread( headerFirstImg, 1 , 12 , infileFirstImg);
    fread( &img1Width, sizeof(int) , 1,  infileFirstImg); //get the image size

    fread( headerFirstImg, 1 , 0 , infileFirstImg);
    fread( &img1Height, sizeof(int) , 1,  infileFirstImg);

    printf("image 1 data: \nsize:  %d\n", img1Size);
    printf("width: = %d\n", img1Width);
    printf("height: = %d\n -------\n", img1Height);
    /******** second image ***********/
    fread( headerSecondImg, 1 , 2 , infileSecondImg);
    fread( &img2Size, sizeof(int) , 1,  infileSecondImg); //get the image size

    fread( headerSecondImg, 1 , 12 , infileSecondImg);
    fread( &img2Width, sizeof(int) , 1,  infileSecondImg); //get the image size

    fread( headerSecondImg, 1 , 0 , infileSecondImg);
    fread( &img2Height, sizeof(int) , 1,  infileSecondImg);

    printf("\nimage 2 data: \nsize:  %d\n", img2Size);
    printf("width: = %d\n", img2Width);
    printf("height: = %d\n -------\n", img2Height);

    //rewind image reads to beginning
    rewind(infileFirstImg);
    rewind(infileSecondImg);
    /******************END************************/

    unsigned char image1[img1Size];
    unsigned char image2[img2Size];

    fread(image1, 1, img1Size, infileFirstImg); //this works
    fread(image2, 1, img2Size, infileSecondImg); //this works

    //Close file streams (not needed anymore)
    fclose(infileFirstImg);
    fclose(infileSecondImg);

    //If images are different sizes, pick the biggest as the size template
    if(img1Size > img2Size){
        finalImageSize = img1Size;
        finalImageWidth = img1Width;
    }else {
        finalImageSize = img2Size;
        finalImageWidth = img2Width;
    }

    //call functions to create images
    checkerBoardPattern(image1, image2, finalImageSize, finalImageWidth);
    blendImages(image1, image2, finalImageSize);

    return 0;
}



void checkerBoardPattern(unsigned char *firstImage, unsigned char *secondImage, int imgSize, int imgWidth){

    int index, pixelIndex, pixelsPerSquare;
    FILE *checkerOutFile = fopen("checker.bmp", "wb");

    int squareSize = CHECKERBOARDSIZE;
    pixelsPerSquare = imgWidth/CHECKERBOARDSIZE;
    pixelsPerSquare = pixelsPerSquare*COLORSPERPIXEL;

    /**
     * The indexer that determines the current pixel.
     * Starts at 54, which is the start of pixel data in the image.
     */
     pixelIndex = HEADERSIZE;


    unsigned char newImageData[imgSize];

    //add header data to imagedata
    for(int i = 0; i < pixelIndex; i++){
        newImageData[i] = firstImage[i];
    }

    //8 x 8 checkerboard
    for(int row = 0; row < squareSize; row++){

        for(int column = 0; column < imgWidth; column++){

            //if row/colum is even, add data from first image
            if ((row % 2) == (column % 2)) {
                index = 0;
                while(index < pixelsPerSquare) {
                    //newImageData[pixelIndex] = firstImage[newImageSize - pixelIndex];
                    newImageData[pixelIndex] = firstImage[pixelIndex];
                    index++;
                    pixelIndex++;
                }
            } else {
                //if row/colum is odd, add data from second image
                index = 0;
                while (index < pixelsPerSquare){
                    //newImageData[pixelIndex] = secondImage[newImageSize - pixelIndex];
                    newImageData[pixelIndex] = secondImage[pixelIndex];
                    index++;
                    pixelIndex++;
                }
            }
        }

    }

    //write image and close file.
    fwrite(newImageData, sizeof(unsigned char), imgSize, checkerOutFile);
    fclose(checkerOutFile);

}

void blendImages(unsigned char *firstImage, unsigned char *secondImage, int imgSize){


    FILE *blendOutFile = fopen("blend.bmp", "wb");
    unsigned char newImageData[imgSize];

    /**
     * The indexer that determines the current pixel.
     * Starts at 54, which is the start of pixel data in the image.
     */
    int pixelIndex = HEADERSIZE;

    //Create the header for the new image.
    for(int i = 0; i < pixelIndex; i++){
        newImageData[i] = firstImage[i];
    }

    //for the rest of the pixels, print the average of the two values
    for(pixelIndex; pixelIndex < imgSize; pixelIndex++){

        //newImageData[pixelIndex] = blendPixels(*firstImage, *secondImage, pixelIndex);
        newImageData[pixelIndex] = (unsigned char) ((firstImage[pixelIndex] + secondImage[pixelIndex]) / 2);
    }

    //write image and close file.
    fwrite(newImageData, sizeof(unsigned char), imgSize, blendOutFile);
    fclose(blendOutFile);

}




