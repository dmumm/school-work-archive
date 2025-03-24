# Compiles and runs the program "arrays"

arrays: main.c initArray.c defs.h printArray.c findValues.c
	gcc -Wall -o arrays defs.h main.c initArray.c printArray.c findValues.c

run: arrays input.txt
	./arrays < input.txt

clean:
	rm arrays
