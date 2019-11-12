all: thread_wrong thread_better fork_one_child fork_children get_pid

GCC_OPTIONS = -Wall -pedantic

THREAD_WRONG_EXEC = thread_wrong
THREAD_WRONG_OBJS = ./src/thread_wrong.cpp
THREAD_WRONG_DEPS = -lpthread

THREAD_BETTER_EXEC = thread_better
THREAD_BETTER_OBJS = ./src/thread_better.cpp
THREAD_BETTER_DEPS = -lpthread

FORK_ONE_CHILD_EXEC = fork_one_child
FORK_ONE_CHILD_OBJS = ./src/fork_one_child.cpp
FORK_ONE_CHILD_DEPS =

FORK_CHILDREN_EXEC = fork_children
FORK_CHILDREN_OBJS = ./src/fork_children.cpp
FORK_CHILDREN_DEPS =

GET_PID_EXEC = get_pid
GET_PID_OBJS = ./src/get_pid.cpp
GET_PID_DEPS =

thread_wrong: ./src/thread_wrong.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(THREAD_WRONG_OBJS) -o ./build/$(THREAD_WRONG_EXEC) $(THREAD_WRONG_DEPS)

thread_better: ./src/thread_better.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(THREAD_BETTER_OBJS) -o ./build/$(THREAD_BETTER_EXEC) $(THREAD_BETTER_DEPS)

fork_one_child: ./src/fork_one_child.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_ONE_CHILD_OBJS) -o ./build/$(FORK_ONE_CHILD_EXEC) $(FORK_ONE_CHILD_DEPS)

fork_children: ./src/fork_children.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(FORK_CHILDREN_OBJS) -o ./build/$(FORK_CHILDREN_EXEC) $(FORK_CHILDREN_DEPS)

get_pid: ./src/get_pid.cpp
	g++ --std=c++17 $(GCC_OPTIONS) $(GET_PID_OBJS) -o ./build/$(GET_PID_EXEC) $(GET_PID_DEPS)
