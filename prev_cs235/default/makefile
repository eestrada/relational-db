CC = g++
CFLAGS = -Wall -g -I . -I inc/

BIN = bin/test.bin
ARGS = 
OBJ_FILES = obj/main.o
DEPS = inc/header.hpp

.PHONY : bin test clean memcheck

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJ_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CC) -o $@ $(OBJ_FILES) $(CFLAGS)
	@ echo

obj/%.o : src/%.cpp $(DEPS)
	@ echo "Creating object file: " $@
	@- mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)
	@ echo
