CC = g++
CFLAGS = -Wall -g -I . -I Student_Code/

BIN = bin/test.bin
ARGS = 
OBJ_FILES = obj/main.o
CPP_FILES = Student_Code/*.cpp Student_Code/*.cxx

DEPS = Student_Code/Factory.h

.PHONY : runalways run touchall drvr235 bin test clean

runalways : clean $(BIN)
	./$(BIN)

run : $(BIN)
	./$(BIN)

touchall :
	touch -c $(BIN) $(CPP_FILES) $(DEPS)
	sleep 5

drvr235 :
	@ ./Run_Test_Driver.sh

test : clean

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	@ echo

$(BIN) : $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CC) -o $@ $(CFLAGS) $(CPP_FILES)
	@ echo

