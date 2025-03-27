default:
	gcc -Wall matmul_opt.c -o exe -O0
	gcc -Wall matmul_naive.c -o exeTest -O0

go:
	./exe 1000 1000 1000 >> test.txt
	./exeTest 1000 1000 1000 >> correct.txt

test:
	diff test.txt correct.txt	

make clean:
	rm -f exe exeTest test.txt correct.txt
