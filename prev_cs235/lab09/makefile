CC = g++
CFLAGS = -Wall -ansi -pedantic -g -I . -I Student_Code/

BIN = bin/test.bin
EXE=dont_run_me
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
	@$(CC) $(CFLAGS) -o$(EXE) Student_Code/*.cpp ignoreme.a
	@chmod 755 $(EXE);
	@#./$(EXE); 
	@valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=DONT_DELETE.supp ./$(EXE)
	@rm -f ./$(EXE)
	@read -p "Press any key to exit..."

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

