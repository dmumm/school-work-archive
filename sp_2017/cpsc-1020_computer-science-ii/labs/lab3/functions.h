#include <stdio.h>
#include <stdlib.h>
#include "functions.c"


typedef struct
{
    char magic[3];
    int height, width, maxval;
}header_t;

typedef struct
{
  unsigned char r, g, b;
}pixel_t;

header_t hdr;
pixel_t pix;


void readHeader(FILE*, struct header_t *);

void createHeader(FILE*, struct header_t *);

void readPixels(FILE*, struct header_t *, struct pixel_t**);

void writePixels(FILE*, struct header_t *, struct pixel_t** );
