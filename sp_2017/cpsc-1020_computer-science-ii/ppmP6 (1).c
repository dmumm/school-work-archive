#include <stdio.h>

int main()
{
    int i = 0;
    fprintf(stdout, "P6\n400 400 255\n");
    for( ; i < 400*400; i++)
    {
        //Clemson orange
        fprintf(stdout, "%c%c%c", 234, 106, 32);
    }
    return 0;
}
