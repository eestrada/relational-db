CC = g++
CFLAGS = -Wall -g -I . -I inc/

BIN = bin/test.bin
ARGS = 
CPP_FILES = Mimic.cpp main.cxx
DEPS = Mimic.hpp

.PHONY : all run test clean touch memcheck dirs

all : touch run

run: $(BIN)
	./$(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

touch : dirs
	@- touch $(CPP_FILES) $(DEPS) $(BIN)

memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

dirs :
	@- mkdir -p bin

$(BIN) : dirs $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	$(CC) $(CFLAGS) -o $@ *.cpp *.cxx 
	@ echo

