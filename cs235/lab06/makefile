CXX ?= c++
CXXFLAGS = -ansi -pedantic -g -Wall -I./ -I./inc/ -I./src/

BINDIR = ./bin
BIN = $(BINDIR)/test.bin
ARGS = 

SRCDIR = ./Student_Code

SRCS =  $(wildcard $(SRCDIR)/*.cpp)
#SRCS =  $(SRCDIR)/Node.cpp $(SRCDIR)/BST.cpp
INCS =  $(wildcard $(SRCDIR)/*.h*)
LIB = ignoreme.a

.PHONY : run bin test clean memcheck

run : bin
	$(BIN) $(ARGS)

bin : $(BIN)
	@- # Do nothing

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf $(BINDIR)

memcheck : $(BIN) 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(SRCS) $(INCS)
	@- mkdir -p $(BINDIR)
	@ echo "Compiling binary"
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS) $(LIB)
	@ echo

