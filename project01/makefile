CXX ?= c++
CXXFLAGS = -ansi -Wall -I./ -I./inc/ 

BINDIR = ./bin
BIN = $(BINDIR)/Lex.bin
ARGS = ./test/TestFile4

INCDIR = ./inc
SRCDIR = ./src
OBJDIR = ./obj

INCS = $(wildcard $(INCDIR)/*.h)
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS := $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(OBJS))
# MAINCPP = src/main.cpp
MAINCPP = 

.PHONY : echome bin test clean memcheck

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
	$(CXX) -c -o $@ $< $(CXXFLAGS) 
	@ echo

