/*
 * Dylan Mumm
 * dmumm
 * Lab 4
 * Lab Section: 004
 * Nick glyder
 */

#include <iostream>
#include "functions.h"

int checkPoint(point_t *p, point_t *test){

  double a = ((y1 - y3) * (x - x3) + (x3 - x2) * (y - y3)) 
             /
             ((y2 - y3) * (x1 - x3) * (x1 - x3) + (x3 - x3) * (y1 - y3));

  double b = ((y3 - y1) * (x - x3) + (x1 - x3) * (y - y3))
	     /
	     ((y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3));

  double c = 1 - a - b;ZZ

  if (a >= 0 && a <= 1 ||
      b >= 0 && b <= 1 ||
      c >= 0 && b <= 1 ){

    return(1);
  }

  else{
    return(0);
  }

}
