//? c boilerplate

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//? read in d1.img, d2.img, d4.img, parity.img. Then write out d3.img
int main(int argc, char *argv[])
{
    FILE *fp1, *fp2, *fp3, *fp4;

    int i, j, k, l;
    unsigned char *d1, *d2, *d4, *p, *d3;
    int width, height, width2, height2, width4, height4;
    int size, size2, size4;
    int parity;
    int *p1, *p2, *p4, *p3;
    int *pp1, *pp2, *pp4, *pp3;
    int *dp1, *dp2, *dp4, *dp3;

    fp1 = fopen(d1.img, "rb");
    fp2 = fopen(d2.img, "rb");
    fp4 = fopen(d4.img, "rb");
    fp3 = fopen(parity.img, "wb");

    width = 0;
    height = 0;
    fscanf(fp1, "%d %d", &width, &height);

    size = width * height;

    fprintf(fp3, "%d %d\n", width, height);

    d1 = (unsigned char *)malloc(size * sizeof(unsigned char));
    fread(d1, sizeof(unsigned char), size, fp1);
    fclose(fp1);

    d2 = (unsigned char *)malloc(size * sizeof(unsigned char));
    fread(d2, sizeof(unsigned char), size, fp2);
    fclose(fp2);

    d4 = (unsigned char *)malloc(size * sizeof(unsigned char));
    fread(d4, sizeof(unsigned char), size, fp4);
    fclose(fp4);

    //? allocate memory for parity.img
    p = (unsigned char *)malloc(size * sizeof(unsigned char));

    fread(p, sizeof(unsigned char), size, fp3);
    fclose(fp3);
    d3 = (unsigned char *)malloc(size * sizeof(unsigned char));

    fprintf(fp3, "%d %d\n", width, height);

    //? calculate d3
    for (i = 0; i < size; i++)
    {
        parity = p[i];
        d3[i] = d1[i] ^ d2[i] ^ d4[i] ^ parity;
    }

    //? write out d3.img
    fp3 = fopen(argv[4], "wb");
    fprintf(fp3, "%d %d\n", width, height);
    fwrite(d3, sizeof(unsigned char), size, fp3);
    fclose(fp3);

}
