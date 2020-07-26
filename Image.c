/* Image.c: source file for basic image manipulation*/
//Mason Harlan
//63263805

#include "Image.h"
#include "Constants.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y){
    return(image->R[x+y*ImageWidth(image)]);
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y){
    return(image->G[x+y*ImageWidth(image)]);
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y){
    return(image->B[x+y*ImageWidth(image)]);
}

void SetPixelR(IMAGE *image, unsigned int x,  unsigned int y, unsigned char r){
    //R[x][y] = r;
    image -> R[x+y*(ImageWidth(image))] = r;
}

void SetPixelG(IMAGE *image, unsigned int x,  unsigned int y, unsigned char g){
    image -> G[x+y*(ImageWidth(image))] = g;
}

void SetPixelB(IMAGE *image, unsigned int x,  unsigned int y, unsigned char b){
    image -> B[x+y*(ImageWidth(image))] = b;
}

/* Allocate dynamic memory for the image structure and its R/G/B values */
/* Return the pointer to the image, or NULL in case of error */
IMAGE *CreateImage(unsigned int Width, unsigned int Height){
    IMAGE *image = malloc(sizeof(IMAGE));
    image -> R = malloc(Width * Height * sizeof(unsigned char));
    image -> G = malloc(Width * Height * sizeof(unsigned char));
    image -> B = malloc(Width * Height * sizeof(unsigned char));
    image -> Width = Width;
    image -> Height = Height;
    if (image == NULL){
	return (NULL);
    }
    return image;

}

/* Free the memory for the R/G/B values and IMAGE structure */
void DeleteImage(IMAGE *image){
    free(image->R);
    image -> R = NULL;
    free(image->G);
    image -> G = NULL;
    free(image->B);
    image -> B = NULL;
    free(image);
    image = NULL;
}

/* Return the image's width in pixels */
unsigned int ImageWidth(const IMAGE *image){
    return (image->Width);
}

/* Return the image's height in pixels */
unsigned int ImageHeight(const IMAGE *image){
    return(image->Height);
}

