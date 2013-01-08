CXX ?= g++
CXXFLAGS = -ansi -Wall -I./ -I./inc/ 

BINDIR = ./bin
BIN = $(BINDIR)/Lex.bin
ARGS = ./test/TestFile4

OBJDIR = ./obj
# OBJS = $(OBJDIR)/*.o
OBJS = $(OBJDIR)/Input.o $(OBJDIR)/Lex.o $(OBJDIR)/State.o $(OBJDIR)/Token.o $(OBJDIR)/TokenType.o $(OBJDIR)/Utils.o
INCDIR = ./inc
DEPS = $(INCDIR)/Input.h $(INCDIR)/Lex.h $(INCDIR)/State.h $(INCDIR)/Token.h $(INCDIR)/TokenType.h $(INCDIR)/Utils.h
SRCDIR = ./src
SRCS = $(SRCDIR)/Input.cpp $(SRCDIR)/Lex.cpp $(SRCDIR)/State.cpp $(SRCDIR)/Token.cpp $(SRCDIR)/TokenType.cpp $(SRCDIR)/Utils.cpp
# MAINCPP = src/main.cpp
MAINCPP = 

.PHONY : bin test clean memcheck

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	@ echo

memcheck : bin 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJS) $(SRCS) $(DEPS)
	@- mkdir -p $(BINDIR)
	@ echo "Compiling binary"
	$(CXX) $(CXXFLAGS) -o $(BIN) $(MAINCPP) $(OBJS) $(CXXFLAGS)
	@ echo

$(OBJDIR)/%.o : ./src/%.cpp $(DEPS)
	@- mkdir -p $(OBJDIR)
	@ echo "Creating object file: " $@
	$(CXX) -c -o $@ $< $(CXXFLAGS) 
	@ echo

