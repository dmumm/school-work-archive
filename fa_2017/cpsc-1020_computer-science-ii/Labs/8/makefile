# Config
CC=g++
CFLAGS=-Wall -g -std=c++11
LFLAGS=-lm
TARGET=out

# Generate source and object lists
SRCS := \
	$(wildcard *.cpp) \
	$(wildcard src/*.cpp) \
	$(wildcard src/**/*.cpp)

HDRS := \
	$(wildcard *.hpp) \
	$(wildcard src/*.hpp) \
	$(wildcard src/**/*.hpp)

OBJS := $(patsubst %.cpp, bin/%.o, $(wildcard *.cpp))
OBJS += $(filter %.o, $(patsubst src/%.cpp, bin/%.o, $(SRCS)))

# Link all built objects
build: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(TARGET)
%.o: %.cpp $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# Catch root directory src files
bin/%.o: %.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Catch all nested directory files
bin/%.o: src/%.cpp $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

which:
	@echo "FOUND SOURCES: ${SRCS}"
	@echo "FOUND HEADERS: ${HDRS}"
	@echo "GENERATED OBJS: ${OBJS}"

clean:
	rm -f $(TARGET)
	rm -rf bin

run: build
	./$(TARGET) dates.txt sorted.txt
