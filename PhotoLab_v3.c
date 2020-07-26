/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22,  Fall 2017       */
/* Modified: Mihnea Chirila for F18, 10/30/18                                                          */
/* Author: Mina Moghadam                                                */
/* Date:   11/8/2017                                                */
/*                                                                   */
/* Comments: */
/*                                                                   */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
void AutoTest(void);

int main()
{
	int rc ;
#ifdef DEBUG
	AutoTest();
	rc = 0 ;

#else
	IMAGE *image = NULL;

	/*unsigned char R[WIDTH][HEIGHT];
	unsigned char B[WIDTH][HEIGHT];
	unsigned char G[WIDTH][HEIGHT];*/

	int option;			/* user input option */
        char fname[SLEN];		/* input file name */
	int brightness = -256;
	float angle;
	int roption;
	int resizepercentage;
	float saturatepercentage;

	rc = 1 ;
	PrintMenu();
    printf("Please make your choice: ");
    scanf("%d", &option);

	while (option != EXIT) {
		if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            //rc = LoadImage(fname);
	    image = LoadImage(fname);
	    //assert(image);
		}

		/* menu item 2 - 8 requires image is loaded first */
        else if (option >= 2 && option <= 11) {
            if (image == NULL)	 {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
	switch (option) {
	case 2:
      	    printf("Please input the file name to save: ");
	    scanf("%s", fname);
	    SaveImage(fname, image);
	    break;
	 case 3:
            image = BlackNWhite(image);
            printf("\"Black & White\" operation is done!\n");
            break;
	case 4:
            image = Edge(image);
            printf("\"Edge\" operation is done!\n");
            break;
          case 5:
            image = Shuffle(image);
            printf("\"Shuffle\" operation is done!\n");
            break;
	case 6:
 	    while(brightness > 255 || brightness < -255){
	    printf("Enter brightness value (between -255 and 255):");
	    scanf("%d", &brightness);
						}
            image = Brightness(image, brightness);
            printf("\"brightness\" operation is done!\n");
            break;
	case 7:
            image = HMirror(image);
            printf("\"Horizontally Mirror\" operation is done!\n");
            break;
          case 8:
            printf("Enter hue rotation angle:");
            scanf("%f", &angle);
            image = HueRotate(image, angle);
            printf("\"HueRotate\" operation is done!\n");
            break;
	  case 9:
            printf("Enter 1 for Horizontal Flip, 2 for Vertical Flip,\n3 for Clockwise, 4 for Counterclockwise:");
            scanf("%d", &roption);
	    image = Rotate(image,roption);
	    printf("\"Rotate\" operation is done!\n");
            break;
	  case 10:
	    printf("Enter Resize percentage:");
	    scanf("%d", &resizepercentage);
	    image = Resize(image,resizepercentage);
	    printf("\"Resize\" operation is done!\n");
	  case 11:
	    printf("Enter Saturation percentage:");
	    scanf("%f", &saturatepercentage);
	    image = Saturate(image,saturatepercentage);
	    printf("\"Saturation\" operation is done!\n");
	default:
	    break;

				}
			}
		}

		else if (option == 12) {
            AutoTest();
            rc = SUCCESS;	/* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

		/* Process finished, waiting for another input */
        PrintMenu();
        printf("Please make your choice: ");
        scanf("%d", &option);
	}
	if (image != NULL){
		DeleteImage(image);}
    printf("You exit the program.\n");
#endif
	return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu() {
    printf("\n----------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save an image in PPM and JPEG format\n");
    printf(" 3: Change a color image to Black & White\n");
    printf(" 4: Sketch the edge of an image\n");
    printf(" 5: Shuffle an image\n");
    printf(" 6: Adjust the brightness of an image\n");
    printf(" 7: Mirror an image horizontally\n");
    printf(" 8: Adjust the hue of an image\n");
    printf(" 9: Rotate or flip the image\n");
    printf(" 10: Resize the image\n");
    printf(" 11: Saturate the image\n");
    printf(" 12: Test all functions\n");
    printf(" 13: Exit\n");
}


/* auto test*/

void AutoTest(void) {
	//unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];
    IMAGE *image = NULL;
     //char fname[SLEN] = "HSSOE";
		int brightness = 200;
		float angle = -1.5;


	image = LoadImage("HSSOE");
	image = BlackNWhite(image);    
	SaveImage("bw", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("BlackNWhite was tested!\n");
	#endif   

	image = LoadImage("HSSOE");
	image = Edge(image);    
	SaveImage("edge", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Edge was tested!\n");
	#endif   
   	
	image = LoadImage("HSSOE");
	image = Shuffle(image);    
	SaveImage("shuffle", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Shuffle was tested!\n");
	#endif   

	image = LoadImage("HSSOE");
	image = Brightness(image, brightness);    
	SaveImage("brightness", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Brightness was tested!\n");
	#endif   
	
	image = LoadImage("HSSOE");
	image = HMirror(image);    
	SaveImage("hmirror", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("HMirror was tested!\n");
	#endif   

	image = LoadImage("HSSOE");
	image = HueRotate(image, angle);    
	SaveImage("hue", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("HueRotate was tested!\n");
	#endif   
	
	image = LoadImage("HSSOE");
	image = Saturate(image, 90);    
	SaveImage("saturate", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Saturate was tested!\n");
	#endif   
	
	image = LoadImage("HSSOE");
	image = Rotate(image, 1);    
	SaveImage("rotate", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Rotate was tested!\n");
	#endif   

	image = LoadImage("HSSOE");
	image = Rotate(image, 3);    
	SaveImage("rotate", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Rotate was tested!\n");
	#endif   

	image = LoadImage("HSSOE");
	image = Resize(image, 170);
	SaveImage("bigresize", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Big Resize was tested!\n");
	#endif   
	
	image = LoadImage("HSSOE");
	image = Resize(image, 60);
	SaveImage("smallresize", image);
    	DeleteImage(image);
	#ifndef DEBUG
		printf("Small Resize was tested!\n");
	#endif  
//return 0;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
