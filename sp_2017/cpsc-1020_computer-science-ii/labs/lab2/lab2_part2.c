/*
 * Dylan Mumm
 * dmumm
 * Lab #2, Section: 004
 * Nick Glyder
 *
 * Constructs a Polish flag
 *
 */

#include "stdio.h"

int main()
{

  int i, width, height, max;

  width = 600;
  height = 400;
  max = 255;

  printf("P6\n%d %d %d\n", width, height, max);

  for(i = 0; i < 600 * 200; i++)
  {
    printf("%c%c%c", 255, 255, 255);
  }

  for(i = 0; i < 600 * 200; i++)
  {
    printf("%c%c%c", 220, 20, 60);
  }


  return 0;
}
