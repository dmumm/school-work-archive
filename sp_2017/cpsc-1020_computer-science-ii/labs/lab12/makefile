SRC = driver.cpp functions.cpp
OBJ = driver.o functions.o
PROG = driver

$(PROG) : $(OBJ)
	g++ $(OBJ) -o $(PROG) -Wall -lm -g

$(OBJ) : $(SRC)


clean:
	rm *.o driver

run:
	./driver input1.txt
	./driver input2.txt
