BIN = ./test.bin
INPUT = ./tests/in4A.txt
OUTPUT = /tmp/actual4A.txt
OUTTEST = ./tests/out4A.txt
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

.PHONY : bin run clean test cleantest memcheck

bin : $(BIN)

run : bin
	$(BIN) $(ARGS)

clean :
	@ echo "Removing generated files"
	rm -vf $(BIN)
	rm -vf $(OUTPUT)
	rm -rf $(OBJDIR)
	rm -rf ./output
	rm -rf ./diffs

test : memcheck
	@ ./run_tests.sh

cleantest : clean test


memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	time valgrind --tool=memcheck --leak-check=full --max-stackframe=5000000 \
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
