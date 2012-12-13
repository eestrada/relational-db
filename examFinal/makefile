CC = g++
CFLAGS = -Wall -ansi -pedantic -O0 -g -I . -I exam_code/ -I eestrada_code/

BIN = bin/test.bin
EXE=dont_run_me
ARGS = 
OBJ_FILES = obj/main.o
CPP_FILES = exam_code/*.cpp eestrada_code/*.cpp

DEPS = exam_code/*.h eestrada_code/*.hpp

.PHONY : test compile mem clean bin

test : $(BIN)
	./$(BIN)

compile : $(BIN)

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
	$(CC) -o $@ $(CFLAGS) $(CPP_FILES)
	@chmod 755 $(BIN);
	@ echo


