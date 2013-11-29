BIN = ./test.bin
INPUT = cat test_input.txt
#ARGS = input.txt

SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./obj
OBJS = obj/main.o 

SRCS = $(wildcard $(SRCDIR)/*.cpp)
INCS = $(wildcard $(INCDIR)/*.h*) $(wildcard $(INCDIR)/*.hpp)

OGLLIBS ?= -lglut -lGLU -lGL 
INCLUDES= -I$(INCDIR)/
CXX ?= c++
CXXFLAGS = -std=c++0x -g -Wall -pedantic $(INCLUDES)

.PHONY : run bin test clean memcheck

run : $(BIN)
	@ echo "Testing executable"
	$(BIN) $(ARGS)

bin : $(BIN)

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -f $(BIN)
	rm -rf $(OBJDIR)

memcheck : $(BIN) 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJS) $(INCS)
	@ echo "Compiling binary"
	$(CXX) -o $(BIN) $(OBJS) $(INCLUDES) $(OGLLIBS)
	@ echo

obj/%.o : src/%.cpp $(INCS)
	@- mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	@ echo
