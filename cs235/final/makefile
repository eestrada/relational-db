BINDIR = ./bin
BIN = $(BINDIR)/test.bin
ARGS = 

SRCDIR = ./src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCS = $(wildcard $(SRCDIR)/*.h*) $(wildcard $(SRCDIR)/*.inl)

CXX ?= c++
CXXFLAGS = -ansi -pedantic -g -Wall -I$(SRCDIR)/
#CXXFLAGS = -ansi -pedantic -g -Wall -I./ -I./inc/ -I./src/

.PHONY : run test clean memcheck

run : $(BIN)
	$(BIN) $(ARGS)

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
	$(CXX) $(CXXFLAGS) -o $(BIN) $(SRCS)
	@ echo

