SRC = driver.cpp Circle.cpp Color.cpp Header.cpp Pixel.cpp Point.cpp Quadrilateral.cpp Shape.cpp Triangle.cpp
OBJ = driver.o Circle.o Color.o Header.o Pixel.o Point.o Quadrilateral.o Shape.o Triangle.o
PROG = driver

$(PROG) : $(OBJ)
	g++ $(OBJ) -o $(PROG) -Wall -lm -g

$(OBJ) : $(SRC)


clean:
	rm *.o driver
