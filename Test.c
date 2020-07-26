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

#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "DIPs.h"
#include "Advanced.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();
int main()
{
	IMAGE *image = NULL;

   	image = LoadImage("HSSOE");    
	SaveImage("test", image);
    	DeleteImage(image);
   	
	image = LoadImage("HSSOE");
	image = BlackNWhite(image);    
	SaveImage("bw", image);
    	DeleteImage(image);

	image = LoadImage("HSSOE");
	image = Edge(image);    
	SaveImage("edge", image);
    	DeleteImage(image);
   	
	image = LoadImage("HSSOE");
	image = Shuffle(image);    
	SaveImage("shuffle", image);
    	DeleteImage(image);

	image = LoadImage("HSSOE");
	image = Brightness(image, 100);    
	SaveImage("brightness", image);
    	DeleteImage(image);
	image = NULL;
	
	image = LoadImage("HSSOE");
	image = HMirror(image);    
	SaveImage("hmirror", image);
    	DeleteImage(image);

	image = LoadImage("HSSOE");
	image = HueRotate(image, (-1.5));    
	SaveImage("hue", image);
    	DeleteImage(image);
	
	image = LoadImage("HSSOE");
	image = Saturate(image, 90);    
	SaveImage("saturate", image);
    	DeleteImage(image);
	
	image = LoadImage("HSSOE");
	image = Rotate(image, 1);    
	SaveImage("rotate", image);
    	DeleteImage(image);

	image = LoadImage("HSSOE");
	image = Rotate(image, 3);    
	SaveImage("rotate", image);
    	DeleteImage(image);

	image = LoadImage("HSSOE");
	image = Resize(image, 170);    
	SaveImage("bigresize", image);
    	DeleteImage(image);
	
	image = LoadImage("HSSOE");
	image = Resize(image, 60);    
	SaveImage("smallresize", image);
    	DeleteImage(image);
	return 0;
}

