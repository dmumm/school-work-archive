# ANSI color codes
RED   = \033[1;31m
GREEN = \033[1;32m
BLUE  = \033[1;34m
CYAN  = \033[1;36m
RESET = \033[0m

# Source and object files
SRCS = $(wildcard *.c)
OFILES = $(SRCS:.c=.o)
TEST = sorber_basic_test.c
OFILES := $(filter-out $(TEST:.c=.o), $(OFILES))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g -O3 -fPIC
LDFLAGS = -shared

INCLUDES = -I./

# Compile .c to .o
.c.o:
	@echo "$(BLUE)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Linking to create shared library
libmyalloc.so: $(OFILES)
	@echo "$(GREEN)Linking $@...$(RESET)"
	$(CC) $(LDFLAGS) -o $@ $(OFILES)

# Default target
all: clean libmyalloc.so
	@echo "$(GREEN)Build complete.$(RESET)"

# Clean up
clean:
	@echo "$(RED)Cleaning up...$(RESET)"
	rm -rf *.o libmyalloc.so

# Add a rule for building the test program if needed
test: $(TEST) libmyalloc.so
	@echo "$(CYAN)Linking $@...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $(TEST) -L. -lmyalloc
