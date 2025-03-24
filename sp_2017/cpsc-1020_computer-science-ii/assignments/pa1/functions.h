/*
 * Dylan Mumm
 * CPSC 1020, Section: 001, Spring 2017
 * dmumm
 * Yvon Feaster
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

// defining the structs
typedef struct header
{
	char type[2];
	int height, width, maxval;
} header_t;

typedef struct pixel
{
	unsigned char r, g, b;
} pixel_t;

// declaring function prototypes
void readHeader(header_t*, FILE*);
void readImage(header_t*, pixel_t **, FILE*);
void chooseTransform(header_t *, pixel_t **, FILE*);
void printP6Image(header_t*, pixel_t **, FILE*);
void grayScaleImage(header_t *, pixel_t **, FILE*);
void flipImage(header_t *, pixel_t **, FILE*);
void rotateLeft(header_t * , pixel_t **, FILE*);
void rotateRight(header_t *, pixel_t **, FILE*);
void color2Negative(header_t*, pixel_t **, FILE*);
void reprint(header_t*, pixel_t**, FILE*);

#endif
