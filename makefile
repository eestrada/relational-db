BIN = ./test.bin
INPUT = ./tests/in10.txt
OUTPUT = /tmp/actual10.txt
OUTTEST = ./tests/out10.txt
#ARGS = < $(INPUT) > $(OUTPUT)
ARGS = $(INPUT) $(OUTPUT)

SRCDIR = ./src
INCDIR = ./inc
OBJDIR = ./obj

SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
INCS = $(wildcard $(INCDIR)/*.h*)

INCLUDES= -I$(INCDIR)/
CXX ?= c++
CXXFLAGS = -std=c++11 -O0 -g -Wall -pedantic $(INCLUDES)

.PHONY : run bin test clean memcheck

run : $(BIN)
	@ echo "Testing executable" 1>&2
	@ $(BIN) $(ARGS)
	@ diff $(OUTPUT) $(OUTTEST)

bin : $(BIN)

test : clean memcheck
	@ ./run_tests.sh

clean :
	@ echo "Removing generated files"
	rm -vf $(BIN)
	rm -vf $(OUTPUT)
	rm -rf $(OBJDIR)
	rm -rf ./output
	rm -rf ./diffs

memcheck : $(BIN) 
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(OBJS) $(INCS)
	@ echo "Compiling binary"
	$(CXX) -o $(BIN) $(OBJS) $(CXXFLAGS) $(INCLUDES)
	@ echo

obj/%.o : src/%.cpp $(INCS)
	@- mkdir -p $(OBJDIR)
	$(CXX) -c -o $@ $< $(CXXFLAGS)
	@ echo
