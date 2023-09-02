# compile with gcc
CC=gcc

# Compiler options:
#
# -pg is used for profiling (gprof)
CFLAGS = -g3 -g -pg

# Linker options:
#
# -lm: link with the math library
LDFLAGS += -lm

# set the name of the executable file to compile here
PROGRAM = crossw
TEST = test

OBJS = Code/program/main/main.o Code/program/grid/VisualGrid.o Code/program/grid/DataGrid.o Code/program/hash_table/HashTable.o Code/program/vector/Vector.o Code/program/dictionary/Dictionary.o Code/program/solve/Solve.o 
TEST_OBJS = Code/test/test.o Code/program/grid/VisualGrid.o Code/program/grid/DataGrid.o Code/program/hash_table/HashTable.o Code/program/vector/Vector.o Code/program/dictionary/Dictionary.o Code/program/solve/Solve.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

$(TEST): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LDFLAGS) -o $(TEST)

clean:
	rm -f $(PROGRAM) $(OBJS) 
	rm -f $(TEST) $(TEST_OBJS)