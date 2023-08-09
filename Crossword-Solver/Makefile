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

OBJS = Code/program/main/main.o Code/program/grid/GridVisualization.o Code/program/grid/GridData.o Code/program/dictionary/Dictionary.o Code/program/hash_table/HashTable.o Code/program/vector/Vector.o Code/program/solve/Solve.o Code/program/solve/Sort.o  

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS) 