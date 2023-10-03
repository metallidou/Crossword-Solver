# compile with gcc
CC=gcc

# Compiler options:
#
# -pg is used for profiling (gprof)
CFLAGS = -g3 -g -pg

# set the name of the executable file to compile here
PROGRAM = crossw

OBJS = Code/program/main/main.o Code/program/grid/VisualGrid.o Code/program/grid/DataGrid.o Code/program/hash_table/HashTable.o Code/program/vector/Vector.o Code/program/dictionary/Dictionary.o Code/program/solve/Solve.o Code/program/solve/Backtracking.o Code/program/solve/Words.o Code/program/solve/Gap.o

$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

clean:
	rm -f $(PROGRAM) $(OBJS) 
