all: thread_wrong fork_one_child fork_children

GCC_OPTIONS = -Wall -pedantic

THREAD_WRONG_EXEC = thread_wrong
THREAD_WRONG_OBJS = ./src/thread_wrong.cpp
THREAD_WRONG_DEPS = -lpthread

FORK_ONE_CHILD_EXEC = fork_one_child
FORK_ONE_CHILD_OBJS = ./src/fork_one_child.cpp
FORK_ONE_CHILD_DEPS =

FORK_CHILDREN_EXEC = fork_children
FORK_CHILDREN_OBJS = ./src/fork_children.cpp
FORK_CHILDREN_DEPS =

thread_wrong: ./src/thread_wrong.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(THREAD_WRONG_OBJS) -o ./build/$(THREAD_WRONG_EXEC) $(THREAD_WRONG_DEPS)

fork_one_child: ./src/fork_one_child.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_ONE_CHILD_OBJS) -o ./build/$(FORK_ONE_CHILD_EXEC) $(FORK_ONE_CHILD_DEPS)

fork_children: ./src/fork_children.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_CHILDREN_OBJS) -o ./build/$(FORK_CHILDREN_EXEC) $(FORK_CHILDREN_DEPS)
