BIN = ./test.bin
INPUT = cat test_input.txt
OUTPUT = OUTPUT.txt HASH_OUTPUT.txt
ARGS = input.txt

SRCDIR = ./src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCS = $(wildcard $(SRCDIR)/*.h*) $(wildcard $(SRCDIR)/*.inl)

CXX ?= c++
CXXFLAGS = -ansi -pedantic -g -Wall -I$(SRCDIR)/
#CXXFLAGS = -ansi -pedantic -g -Wall -I./ -I./inc/ -I./src/

.PHONY : run bin test clean memcheck

bin : $(BIN)

run : $(BIN)
	$(BIN) $(ARGS)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -f $(BIN)
	rm -f $(OUTPUT)

memcheck : $(BIN) 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(SRCS) $(INCS)
	@ echo "Compiling binary"
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS)
	@ echo

