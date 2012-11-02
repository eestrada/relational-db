CC = g++
CFLAGS = -Wall -g -I . -I inc/

BIN = bin/test.bin
ARGS = 
CPP_FILES = Mimic.cpp main.cxx
DEPS = Mimic.hpp

.PHONY : all run bin test clean touch memcheck

all : touch run

run: bin
	./$(BIN)

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

touch :
	@ touch $(BIN) $(CPP_FILES) $(DEPS)

memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CC) $(CFLAGS) -o $@ *.cpp *.cxx 
	@ echo

