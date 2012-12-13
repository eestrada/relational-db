CXX ?= c++ # Use the c++ compiler defined by CXX variable, otherise use c++
CXXFLAGS = -Wall -ansi -pedantic -O0 -g -I . -I exam_code/ -I eestrada_code/

BIN = bin/test.bin
EXE=dont_run_me
ARGS = 
OBJ_FILES = obj/main.o
CPP_FILES = exam_code/*.cpp eestrada_code/*.cpp

DEPS = exam_code/*.h eestrada_code/*.hpp

.PHONY : test ccdata compile mem clean bin

test : $(BIN)
	./$(BIN)

ccdata :
	$(CXX) --version

compile : clean $(BIN)

mem : $(BIN)
	@valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=suppressions.supp ./$(BIN)
	@read -p "Press any key to exit..."

clean :
	@ echo "Removing generated files"
	rm -rf bin
	@ echo

$(BIN) : $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CXX) -o $@ $(CXXFLAGS) $(CPP_FILES)
	@chmod 755 $(BIN);
	@ echo

