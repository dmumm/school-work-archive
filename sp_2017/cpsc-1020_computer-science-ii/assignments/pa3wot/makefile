SRC = driver.cpp Header.cpp Shape.cpp Triangle.cpp Point.cpp Color.cpp Circle.cpp
OBJ = driver.o Header.o Shape.o Triangle.o Point.o Color.o Circle.o	
PROG = driver

$(PROG) : $(OBJ)
	g++ $(OBJ) -o $(PROG) -Wall -lm -g

$(OBJ) : $(SRC)


clean:
	rm *.o driver
