CC = g++
CFLAGS = -Wall -g -I . -I Student_Code/

BIN = bin/test.bin
ARGS = 
OBJ_FILES = obj/main.o
CPP_FILES = Student_Code/*.cpp Student_Code/*.cxx

DEPS = Student_Code/Factory.h

.PHONY : runalways run touchall drvr235 bin test clean memcheck

runalways : touchall $(BIN)
	./$(BIN)

run : $(BIN)
	./$(BIN)

touchall :
	touch -c $(BIN) $(CPP_FILES) $(DEPS)

drvr235 :
	./Run_Test_Driver.sh

test : clean memcheck

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

memcheck : bin
	@ echo "Running valgrind to check for memory leaks"
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes $(BIN) $(ARGS)
	@ echo

$(BIN) : $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CC) -o $@ $(CFLAGS) $(CPP_FILES)
	@ echo

