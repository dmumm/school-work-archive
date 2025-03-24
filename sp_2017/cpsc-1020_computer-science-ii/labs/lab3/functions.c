#include <stdio.h>
#include <stdlib.h>

header_t hdr;
pixel_t hdr;


void readHeader(FILE* ptr, struct header_t *hdr)
{
  fscanf(ptr, "%s %d %d %d ", hdr->magic, &hdr->width, &hdr->height,
                                &hdr->maxval);
}

void createHeader(FILE* ptr, struct header_t *hdr)
{
  fprintf(ptr, "%s %d %d %d\n", hdr->magic, hdr->width, hdr->height,
                                 hdr->maxval);
}

void readPixels(FILE* ptr, struct header_t *hdr, struct pixel_t **pix)
{
  int i, j;

  for(i = 0; i < hdr->height; i++)
  {
    for(j = 0; j < hdr->width; j++)
    {
       fscanf(ptr, "%c%c%c", pix[i][j].r, pix[i][j].g, pix[i][j].b);
    }
  }
}

void writePixels(FILE* ptr, struct header_t *hdr, struct pixel_t **pix)
{
  int i;
  int j;
  for(i = 0; i < hdr->height; i++)
  {
    for(j = 0; j < hdr->width; j++)
    {
       fprintf(ptr, "%c%c%c", pix[i][j].r, pix[i][j].g, pix[i][j].b);
    }

  }
}
