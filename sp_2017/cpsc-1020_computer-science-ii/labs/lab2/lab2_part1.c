/*
 * Dylan Mumm
 * dmumm
 * Lab #2, Section: 004
 * Nick Glyder
 *
 * Imports a ppm and reconstructs an identical ppm
 *
 */

#include "stdio.h"

int main(int argc, char const *argv[])
{

  int i, width, height, max;
  char red, green, blue, type[2];
  FILE *fi;
  FILE *fo;

  fi = fopen(argv[1], "r");
  fo = fopen(argv[2], "w");


  if (fi == NULL)
  {
    printf("Didn't work");
  }

  fscanf(fi, "%s %d%d%d ", type, &width, &height, &max);

  fprintf(fo, "%s\n%d %d %d\n", type, width, height, max);


  for(i = 0; i < width * height; i++)
  {
    fscanf(fi, "%c%c%c", &red, &green, &blue);
    fprintf(fo, "%c%c%c", red, green, blue);
  }

  return 0;
}
