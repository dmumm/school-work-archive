# my first makefile

reverse_echo: reverse_echo.c
	gcc -Wall -o reverse_echo reverse_echo.c

run: reverse_echo
	./reverse_echo

clean:
	rm reverse_echo
	rm -f output.txt

test: reverse_echo
	echo Testing a few examples:
	@./reverse_echo testing 1 2 3
	./reverse_echo testing again
	./reverse_echo hello world
	./reverse_echo "single string"
