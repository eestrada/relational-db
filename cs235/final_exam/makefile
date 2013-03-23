CXX ?= c++ # Use the c++ compiler defined by CXX variable, otherise use c++
CXXFLAGS = -Wall -ansi -pedantic -O0 -g -I . -I exam_code/ -I eestrada_code/

BIN = bin/test.bin
EXE=dont_run_me
ARGS = 
OBJ_FILES = obj/main.o
TA=exam_code/*.cpp
MINE=eestrada_code/*.cpp
CPP_FILES = exam_code/*.cpp eestrada_code/*.cpp
EMAIN=eestrada_code/ethan_main.cxx

DEPS = exam_code/*.h eestrada_code/*.hpp

.PHONY : test other ccdata compile emain mem clean bin

test : emain
	@./$(BIN)

other : $(BIN)
	@./$(BIN)

ccdata :
	$(CXX) --version

compile : clean $(BIN)

emain : $(MINE) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CXX) -o $(BIN) $(CXXFLAGS) $(MINE) $(EMAIN)
	@chmod 755 $(BIN);
	@ echo
	
mem : $(BIN)
	@valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=suppressions.supp ./$(BIN)
	@read -p "Press any key to exit..."

clean :
	@ echo "Removing generated files"
	rm -rf bin
	@ echo

$(BIN) : $(MINE) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CXX) -o $@ $(CXXFLAGS) $(MINE) $(TA)
	@chmod 755 $(BIN);
	@ echo

