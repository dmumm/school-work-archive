

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

void whereis(char *name, void *p);

int global_int = 5;
extern char **environ;

int main(int argc, char **argv)
{
	int x = 89;
	int *p = malloc(sizeof(int));

	putenv("STUFF=JUNK");

	whereis("main", main);
	whereis("&x", &x);
	whereis("whereis", whereis);
	whereis("&argc", &argc);
	whereis("&global_int", &global_int);
	whereis("p", p);
	whereis("environ", environ);
}

void whereis(char *name, void *p)
{
	printf("%s = %p (main + %lx)\n", name, p,
		   ((uintptr_t)p - (uintptr_t)main));
}
