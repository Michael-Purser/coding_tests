all: main fork_one_child fork_children

GCC_OPTIONS = -Wall -pedantic

MAIN_EXEC = main
MAIN_OBJS = ./src/main.cpp
MAIN_DEPS = -lpthread

FORK_ONE_CHILD_EXEC = fork_one_child
FORK_ONE_CHILD_OBJS = ./src/fork_one_child.cpp
FORK_ONE_CHILD_DEPS =

FORK_CHILDREN_EXEC = fork_children
FORK_CHILDREN_OBJS = ./src/fork_children.cpp
FORK_CHILDREN_DEPS =

main: ./src/main.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(MAIN_OBJS) -o ./build/$(MAIN_EXEC) $(MAIN_DEPS)

fork_one_child: ./src/fork_one_child.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_ONE_CHILD_OBJS) -o ./build/$(FORK_ONE_CHILD_EXEC) $(FORK_ONE_CHILD_DEPS)

fork_children: ./src/fork_children.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_CHILDREN_OBJS) -o ./build/$(FORK_CHILDREN_EXEC) $(FORK_CHILDREN_DEPS)
