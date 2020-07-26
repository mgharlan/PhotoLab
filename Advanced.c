#include "Advanced.h"
#include "Image.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

/* Adjust the brightness of an image */
IMAGE *Brightness(IMAGE *image, int brightness) {
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	//assert(image);
	for (int i=0; i<WIDTH; i++){//changes brightness of an image
		for (int j=0; j<HEIGHT; j++){
			if (GetPixelR(image, i, j) + brightness > 255){
				SetPixelR(image, i, j, 255);
			}else if(GetPixelR(image,i,j) + brightness < 0){
				SetPixelR(image, i, j, 0);
			}else{
				SetPixelR(image,i,j,(GetPixelR(image, i,j) + brightness));
			}

			if (GetPixelG(image,i,j) + brightness > 255){
				SetPixelG(image,i,j,255);
			}else if(GetPixelG(image,i,j) + brightness < 0){
				SetPixelG(image,i,j,0);
			}else{
				SetPixelG(image, i, j, (GetPixelG(image, i, j) + brightness));
			}

			if (GetPixelB(image,i,j) + brightness > 255){
				SetPixelB(image,i,j,255);
			}else if(GetPixelB(image, i,j) + brightness < 0){
				SetPixelB(image,i,j,0);
			}else{
				SetPixelB(image, i, j, (GetPixelB(image, i, j) + brightness));
			}
		}
	}
	return image;
}

/* Mirror an image horizontally */
IMAGE *HMirror(IMAGE *image) {
	//assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	int x, y;
    for (y = 0; y < HEIGHT; y++) {
        for (x = 0; x < WIDTH / 2; x++) {
					SetPixelR(image, (WIDTH-1-x),y,GetPixelR(image,x,y));
					SetPixelG(image, (WIDTH-1-x),y, GetPixelG(image,x,y));
					SetPixelB(image, (WIDTH-1-x),y, GetPixelB(image,x,y));
		}
	}
	return image;
}

void matrix_3_3multiplyVector_3(float vector[3], const float matrix[3][3])
{
	/* Memory for result */
	float result[3] = {0, 0, 0};

	/* Perform multiplication */
	result[0] = matrix[0][0]*vector[0] + matrix[0][1]*vector[1] + matrix[0][2]*vector[2];
	result[1] = matrix[1][0]*vector[0] + matrix[1][1]*vector[1] + matrix[1][2]*vector[2];
	result[2] = matrix[2][0]*vector[0] + matrix[2][1]*vector[1] + matrix[2][2]*vector[2];

	/* Copy result into other stack's memory */
	vector[0] = result[0];
	vector[1] = result[1];
	vector[2] = result[2];
}

IMAGE *HueRotate(IMAGE *image, float angle)
{
	//assert(image);
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	/* Matrix to transform normalized
	// RGB color vector from the RGB
	// color space to the YIQ color space */
	static const float RGBtoYIQMatrix[3][3] = {{0.299,  0.587,  0.114},
								  			   {0.596, -0.274, -0.321},
								  			   {0.211, -0.523,  0.311}};

	/* Matrix to transform normalized
	// YIQ color vector from the YIQ
	// color space to the RGB color space */
	static const float YIQtoRGBMatrix[3][3] = {{1.000,  0.956,  0.621},
								  			   {1.000, -0.272, -0.647},
								  			   {1.000, -1.107,  1.705}};

	const float cs = cos(angle), ss = sin(angle);

	/* Matrix to perform a hue
	// rotation on a normalized
	// YIQ color vector*/
	const float XYPlaneVectorRotateMatrix[3][3] = {{1.000, 0.000, 0.000},
												   {0.000, cs, -ss},
												   {0.000, ss, cs}};

	/* Image variables */
	float temp[3];

	for(unsigned int i = 0; i < WIDTH; i++)
	{
		for(unsigned int j = 0; j < HEIGHT; j++)
		{
			/* Create a normalized RGB color
			// vector fro the current pixel
			// in the image */
			temp[0] = (float)(GetPixelR(image,i,j))/255;
			temp[1] = (float)(GetPixelG(image,i,j))/255;
			temp[2] = (float)(GetPixelB(image,i,j))/255;

			/* Transform the RGB vector
			// to a YIQ vector */
			matrix_3_3multiplyVector_3(temp, RGBtoYIQMatrix);

			/* Perform the DIP */
			matrix_3_3multiplyVector_3(temp, XYPlaneVectorRotateMatrix);

			/* Transform back to RGB */
			matrix_3_3multiplyVector_3(temp, YIQtoRGBMatrix);

			/* Denormalize and store back into the image */
			temp[0] = temp[0] * 255;
			temp[0] = temp[0] < 0 ? 0 : temp[0];
			temp[0] = temp[0] > 255 ? 255 : temp[0];
			temp[1] = temp[1] * 255;
			temp[1] = temp[1] < 0 ? 0 : temp[1];
			temp[1] = temp[1] > 255 ? 255 : temp[1];
			temp[2] = temp[2] * 255;
			temp[2] = temp[2] < 0 ? 0 : temp[2];
			temp[2] = temp[2] > 255 ? 255 : temp[2];

			SetPixelR(image,i,j,(unsigned char)temp[0]);
			SetPixelG(image, i,j,(unsigned char)temp[1]);
			SetPixelB(image, i,j,(unsigned char)temp[2]);
		}
	}
	return image;
}

//Adjusts the saturation of an image
IMAGE *Saturate(IMAGE *image, float percent){
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	float tempr,tempb,tempg;
	//float tmpr, tmpb, tmpg;
	for (int y = 0; y<HEIGHT; y++){//changes the saturation of an image
		for (int x = 0; x<WIDTH;x++){
			//sets temporary values
			tempr = (GetPixelR(image,x,y)+GetPixelG(image,x,y)+GetPixelB(image,x,y))/3;
			tempb = tempr;
			tempg = tempr;
			tempr = GetPixelR(image,x,y)- tempr;
			tempb = GetPixelB(image,x,y)- tempb;
			tempg = GetPixelG(image,x,y)- tempg;
			//if (tempr < 0){tmpr = 0;}
			//if (tempb < 0){tmpb = 0;}
			//if (tempg < 0){tmpg = 0;}
			//if (tempr > 255){tmpr = 255;}
			//if (tempb > 255){tmpb = 255;}
			//if (tempg > 255){tmpg = 255;}
			tempr  = GetPixelR(image,x,y)+(tempr*(percent)/100);
			tempg  = GetPixelG(image,x,y)+(tempg*(percent)/100);
			tempb  = GetPixelB(image,x,y)+(tempb*(percent)/100);
			//checks to make sure values are in bound
			if (tempr < 0){tempr = 0;}
			if (tempb < 0){tempb = 0;}
			if (tempg < 0){tempg = 0;}
			if (tempr > 255){tempr = 255;}
			if (tempb > 255){tempb = 255;}
			if (tempg > 255){tempg = 255;}
			SetPixelR(image,x,y,tempr);
			SetPixelG(image,x,y,tempg);
			SetPixelB(image,x,y,tempb);
		}
	}
	return image;
}


//Rotates an image
IMAGE *Rotate(IMAGE *image, int option){
	int HEIGHT = ImageHeight(image);
	int WIDTH = ImageWidth(image);
	IMAGE *timage = CreateImage(WIDTH, HEIGHT);
	if (option == 1){//Horizontal Flip
		for(int x =0; x<WIDTH; x++){
			for(int y =0; y<HEIGHT; y++){
				SetPixelR(timage, x,y,GetPixelR(image,(WIDTH-x-1),y));
				SetPixelG(timage, x,y,GetPixelG(image,(WIDTH-x-1),y));
				SetPixelB(timage, x,y,GetPixelB(image,(WIDTH-x-1),y));
			}
		}
		for(int x=0; x<WIDTH;x++){
			for(int y=0;y<HEIGHT;y++){
				SetPixelR(image, x,y,GetPixelR(timage,x,y));
				SetPixelG(image, x,y,GetPixelG(timage,x,y));
				SetPixelB(image, x,y,GetPixelB(timage,x,y));
			}
		}
	}

	if (option == 2){//vertical flip
		for(int x =0; x<WIDTH; x++){
			for(int y =0; y<HEIGHT; y++){
				SetPixelR(timage, x,y,GetPixelR(image,x,(HEIGHT-1-y)));
				SetPixelG(timage, x,y,GetPixelG(image,x,(HEIGHT-1-y)));
				SetPixelB(timage, x,y,GetPixelB(image,x,(HEIGHT-1-y)));
			}
		}
		for(int x=0; x<WIDTH;x++){
			for(int y=0;y<HEIGHT;y++){
				SetPixelR(image, x,y,GetPixelR(timage,x,y));
				SetPixelG(image, x,y,GetPixelG(timage,x,y));
				SetPixelB(image, x,y,GetPixelB(timage,x,y));
			}
		}

	}

	if (option == 3){//rotate clockwise
		timage -> Width = HEIGHT;
		timage -> Height = WIDTH;
		//int width = ImageWidth(timage);
		//int height = ImageHeight(timage);
		//printf("height: %d \n width:%d\n", height, width);
		//printf("height: %d \n width:%d\n", HEIGHT, WIDTH);
		for(int y =0; y<HEIGHT; y++){
			for(int x =0; x<WIDTH; x++){
				SetPixelR(timage,HEIGHT-1-y,x,GetPixelR(image,x,y));
				SetPixelG(timage,HEIGHT-1-y,x,GetPixelG(image,x,y));
				SetPixelB(timage,HEIGHT-1-y,x,GetPixelB(image,x,y));
			}
		}
		image->Width = HEIGHT;
		image->Height = WIDTH;
		//int w = ImageWidth(image);
		//int h = ImageHeight(image);
		//printf("height: %d \n width:%d\n", h, w);
		for(int y=0; y<WIDTH;y++){
			for(int x=0;x<HEIGHT;x++){
				SetPixelR(image,x,y,GetPixelR(timage,x,y));
				SetPixelG(image,x,y,GetPixelG(timage,x,y));
				SetPixelB(image,x,y,GetPixelB(timage,x,y));
			}
		}
		//DeleteImage(rclock);
	}
	
	if (option == 4){//rotate counterclockwise
		timage -> Width = HEIGHT;
		timage -> Height = WIDTH;
		//int width = ImageWidth(timage);
		//int height = ImageHeight(timage);
		//printf("height: %d \n width:%d\n", height, width);
		//printf("height: %d \n width:%d\n", HEIGHT, WIDTH);
		for(int y =0; y<HEIGHT; y++){
			for(int x =0; x<WIDTH; x++){
				SetPixelR(timage,y,WIDTH-1-x,GetPixelR(image,x,y));
				SetPixelG(timage,y,WIDTH-1-x,GetPixelG(image,x,y));
				SetPixelB(timage,y,WIDTH-1-x,GetPixelB(image,x,y));
			}
		}
		image->Width = HEIGHT;
		image->Height = WIDTH;
		//int w = ImageWidth(image);
		//int h = ImageHeight(image);
		//printf("height: %d \n width:%d\n", h, w);
		for(int y=0; y<WIDTH;y++){
			for(int x=0;x<HEIGHT;x++){
				SetPixelR(image,x,y,GetPixelR(timage,x,y));
				SetPixelG(image,x,y,GetPixelG(timage,x,y));
				SetPixelB(image,x,y,GetPixelB(timage,x,y));
			}
		}	
	}

 DeleteImage(timage);
 return image;
}

IMAGE *Resize(IMAGE *image, int percentage){
	int WIDTH = ImageWidth(image);
	int HEIGHT = ImageHeight(image);
	if (percentage == 100){//keeps image the same size
		return image;
	}
	if (percentage > 100){//increase size of image
		int newwidth = WIDTH*(percentage/100.00);
		int newheight = HEIGHT*(percentage/100.00);
		//printf("newheight: %d newwidth: %d\n", newwidth, newheight);
		IMAGE *big = CreateImage(newwidth, newheight);
		int ox, oy;
		for (int x=0;x<newwidth;x++){
			for(int y =0;y<newheight;y++){
				ox = x/((percentage/100.00));
				oy = y/((percentage/100.00));
				SetPixelR(big,x,y,GetPixelR(image,ox,oy));
				SetPixelG(big,x,y,GetPixelG(image,ox,oy));
				SetPixelB(big,x,y,GetPixelB(image,ox,oy));
			}
		}	
		//image->Height = newheight;
		//image->Width = newwidth;
		//for (int x=0;x<newwidth;x++){
		//	for(int y =0;y<newheight;y++){
		//		SetPixelR(image,x,y,GetPixelR(big,x,y));
		//		SetPixelG(image,x,y,GetPixelG(big,x,y));
		//		SetPixelB(image,x,y,GetPixelB(big,x,y));
		//	}
		//}
		DeleteImage(image);
		return big;	
	}
	if (percentage < 100){//decreases size of image
		int newwidth = WIDTH*(percentage/100.00);
		int newheight = HEIGHT*(percentage/100.00);
		IMAGE *small = CreateImage(newwidth, newheight);
		int x1, y1,x2,y2,range;
		for (int x=0;x<newwidth;x++){
			for(int y=0; y<newheight;y++){
				x1 = x/(percentage/100.00);
				x2 = (x+1)/(percentage/100.00);
				y1 = y/(percentage/100.00);
				y2 = (y+1)/(percentage/100.00);
				range = (x2-x1)*(y2-y1);
				SetPixelR(small,x,y,GetPixelR(image,x1,y1));
				SetPixelG(small,x,y,GetPixelG(image,x1,y1));
				SetPixelB(small,x,y,GetPixelB(image,x1,y1));
				/*int totalr, totalg, totalb = 0;
				
				for (int i = x1; i<x2;i++){//supposed to scan origianl image and find an average value
					for(int j = y1; j<y2;j++){
						totalr += GetPixelR(image,i,j);
						totalg += GetPixelG(image,i,j);
						totalb += GetPixelB(image,i,j);	
					}
				}

				int aver = totalr/range;
				int aveg = totalg/range;
				int aveb = totalb/range;
				if (aver > 255){aver = 255;}
				if (aveg > 255){aveg = 255;}
				if (aveb > 255){aveb = 255;}
				if (aver < 0){aver = 0;}
				if (aveg < 0){aveg = 0;}
				if (aveb < 0){aveb = 0;}
				SetPixelR(small,x,y,aver);
				SetPixelG(small,x,y,aveg);
				SetPixelB(small,x,y,aveb);
				aver = 0;
				aveg = 0;
				aveb = 0;*/
			}
		}
		DeleteImage(image);
		return small;
	}
	return image;
}
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
