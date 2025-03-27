SRC = driver.cpp Header.cpp Shape.cpp Triangle.cpp Point.cpp Color.cpp Circle.cpp Quadrilateral.cpp
OBJ = driver.o Header.o Shape.o Triangle.o Point.o Color.o Circle.o Quadrilateral.o	
CXXFLAGS = -std=c++11
PROG = driver

$(PROG) : $(OBJ)
	g++ $(CFLAGS) -Wall $(OBJ) -o $(PROG) -lm -g

$(OBJ) : $(SRC)


clean:
	rm *.o driver
