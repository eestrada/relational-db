CXX ?= c++
CXXFLAGS = -ansi -pedantic -g -Wall -I./ -I./inc/

BINDIR = ./bin
BIN = $(BINDIR)/test.bin
ARGS = ./test/TestFile5.txt

INCDIR = ./inc
SRCDIR = ./src
OBJDIR = ./obj

INCS = $(wildcard $(INCDIR)/*.hpp) $(wildcard $(INCDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS := $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(OBJS))
MAINCPP = $(SRCDIR)/main.cpp
.PHONY : run bin test clean memcheck packproj

all:
	$(CXX) $(CXXFLAGS) -o $(BIN) $(MAINCPP)
	$(BIN) $(ARGS)

run : bin
	$(BIN) $(ARGS)

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)

memcheck : bin 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJS) $(SRCS) $(INCS)
	@- mkdir -p $(BINDIR)
	@ echo "Compiling binary"
	$(CXX) $(CXXFLAGS) -o $(BIN) $(MAINCPP) $(OBJS)
	@ echo

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCS)
	@- mkdir -p $(OBJDIR)
	@ #echo 'Creating object file "'$@'" From source file "'$<'".'
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	@ echo

