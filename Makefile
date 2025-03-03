# Compiler and flags
CC=g++
CXXFLAGS=-std=c++17 -Wall -Werror -Wextra -pedantic

SFML_FLAGS=-lsfml-graphics -lsfml-window -lsfml-system

SRC=$(wildcard src/*.cpp )

OBJ=$(SRC:.cpp=.o)

Target=main

$(info SRC: $(SRC))
$(info OBJ: $(OBJ))

all: $(Target)

$(Target): $(OBJ)
	$(CC) $(OBJ) -o $(Target) $(SFML_FLAGS)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(Target)

.PHONY: all clean
