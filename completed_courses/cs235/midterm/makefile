CXX ?= c++
CXXFLAGS = -ansi -pedantic -g -Wall -I./ -I./inc/ -I./src/

BINDIR = ./bin
BIN = $(BINDIR)/test.bin
ARGS = 

SRCDIR = ./src

SRCS = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*.h*) $(wildcard $(SRCDIR)/*.inl)
MAINCPP = $(SRCDIR)/main.cpp

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

$(BIN) : $(SRCS)
	@- mkdir -p $(BINDIR)
	@ echo "Compiling binary"
	$(CXX) $(CXXFLAGS) -o $(BIN) $(MAINCPP)
	@ echo

