# Makefile for building the coding standards example source files.
# This is the build command CodeQL will trace to create a database.

CC      = gcc
CXX     = g++
CFLAGS  = -std=c11 -Wall -Wextra
CXXFLAGS = -std=c++14 -Wall -Wextra

C_SRC   = $(wildcard src/c/*.c)
CPP_SRC = $(wildcard src/cpp/*.cpp)

C_OBJ   = $(C_SRC:.c=.o)
CPP_OBJ = $(CPP_SRC:.cpp=.o)

C_BIN   = $(C_SRC:.c=)
CPP_BIN = $(CPP_SRC:.cpp=)

.PHONY: all clean c cpp

all: c cpp

c: $(C_BIN)

cpp: $(CPP_BIN)

src/c/%: src/c/%.c
	$(CC) $(CFLAGS) -o $@ $<

src/cpp/%: src/cpp/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm -f $(C_BIN) $(CPP_BIN) $(C_OBJ) $(CPP_OBJ)
