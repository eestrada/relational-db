CC = g++
CFLAGS = -Wall -g -I . -I inc/
SUPP = ../string.supp
ARGS = 

BIN = bin/crawlmain
OBJ_FILES = obj/LinkedList.o obj/BST.o obj/main.o
DEPS = inc/LinkedList.h inc/BST.h
STYLECHECKER = ~/Documents/CppCheckStyle/CppCheckStyle

.PHONY : bin memcheck clean

bin : $(BIN)

memcheck : $(BIN)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=$(SUPP) $(BIN) $(ARGS)

$(BIN) : $(OBJ_FILES) $(DEPS)
	@- mkdir -p bin
	$(CC) -o $@ $(OBJ_FILES) $(CFLAGS)

obj/%.o : src/%.cpp $(DEPS)
	@- mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)
	@ echo
	$(STYLECHECKER) $<
	@ echo

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
