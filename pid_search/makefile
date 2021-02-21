all: main

GCC_OPTIONS = -Wall -pedantic

MAIN_EXEC = main
MAIN_OBJECTS = main.cpp
MAIN_DEPS = -lstdc++fs

main: $(MAIN_OBJECTS)
	g++ --std=c++17 $(GCC_OPTIONS) $(MAIN_OBJECTS) -o $(MAIN_EXEC) $(MAIN_DEPS)
