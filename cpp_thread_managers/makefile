all: main

GCC_OPTIONS = -Wall -pedantic

MAIN_EXEC = build/main
MAIN_OBJECTS = src/main.cpp src/thread_manager.cpp
MAIN_DEPS = -lstdc++fs -lpthread

main: $(MAIN_OBJECTS)
	g++ --std=c++17 $(GCC_OPTIONS) $(MAIN_OBJECTS) -o $(MAIN_EXEC) $(MAIN_DEPS)
