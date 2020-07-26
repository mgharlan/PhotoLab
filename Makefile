######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2018
#
# 10/30/18 Mihnea Chirila: updated for EECS22 Assignment 3 Fall 2018
#####################################################################
# design name
DESIGN = PhotoLab PhotoLabTest Test

#libs
LIBS   = libFilter.a

CC     = gcc
DEBUG  = -g -DDEBUG
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall -lm
AR     = ar rc
RANLIB = ranlib

IMAGES = bw.ppm \
         edge.ppm \
         shuffle.ppm \
	 brightness.ppm \
         hmirror.ppm \
         hue.ppm \
         rotate.ppm \
         saturate.ppm \
         smallresize.ppm \
         bigresize.ppm \

all: PhotoLab PhotoLabTest Test


########### generate object files ###########

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h Image.h 
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate Image.o
Image.o: Image.h Image.c Constants.h
	$(CC) $(CFLAGS) Image.c -o Image.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h Image.h
	$(CC) $(CFLAGS)  DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Constants.h Image.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

#target to generate PhotoLab.o
PhotoLab.o: PhotoLab_v3.c DIPs.h Advanced.h FileIO.h Constants.h Image.h
	$(CC) $(CFLAGS) PhotoLab_v3.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
PhotoLab_DEBUG.o: PhotoLab_v3.c DIPs.h Advanced.h FileIO.h Constants.h Image.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab_v3.c -o PhotoLab_DEBUG.o

Test.o: Test.c Image.h Constants.h FileIO.h DIPs.h Advanced.h
	$(CC) $(CFLAGS) $(DEBUG) -c Test.c -o Test.o

########### generate library files ###########

#target to generate libFilter.a
libFilter.a: DIPs.o Advanced.o
	$(AR) libFilter.a Advanced.o DIPs.o
	$(RANLIB) libFilter.a

########### generate executables ###########
#target to generate mytest
#myTest: PhotoLabT.o FileIO.o DIPs.o Image.o Advanced.o
#	$(CC) $(LFLAGS) PhotoLabT.o Image.o FileIO.o Advanced.o DIPs.o -o PhotoLabT

#target to generate PhotoLab
Test: Test.o FileIO.o DIPs.o Image.o Advanced.o
	$(CC) $(LFLAGS) Test.o Image.o FileIO.o Advanced.o DIPs.o -o Test

PhotoLab: PhotoLab.o FileIO.o libFilter.a Image.o
	$(CC) $(LFLAGS) PhotoLab.o Image.o FileIO.o -L. -lFilter -o PhotoLab

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o libFilter.a Image.o
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o Image.o FileIO.o -L. -lFilter -o PhotoLabTest
	
#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)

