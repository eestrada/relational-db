CXX ?= clang++
CXXFLAGS = -Wall -g -I . -I Student_Code/

BIN = bin/test.bin
DRVR = dont_run_me
ARGS = 2
OBJ_FILES = obj/main.o
CPP_FILES = Student_Code/*.cpp Student_Code/*.cxx

DEPS = Student_Code/Factory.h

.PHONY : runalways run touchall drvr235 bin test clean

runalways : clean $(BIN)
	./$(BIN) $(ARGS)

run : $(BIN)
	./$(BIN) $(ARGS)

touchall :
	touch -c $(BIN) $(CPP_FILES) $(DEPS)
	sleep 5

drvr235 :
	g++ -o $(DRVR) Student_Code/*.cpp ignoreme.a
	chmod 755 $(DRVR)
	#valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	#--show-reachable=yes --suppressions=DONT_DELETE.supp ./$(DRVR)
	./$(DRVR)
	rm ./$(DRVR)
	read -p "Press any key to exit..."

test : clean

clean :
	@ echo
	rm -f ./$(DRVR)
	rm -rf obj
	rm -rf bin
	@ echo

$(BIN) : $(CPP_FILES) $(DEPS)
	@ echo "Compiling binary"
	@- mkdir -p bin
	$(CXX) -o $@ $(CXXFLAGS) $(CPP_FILES)
	@ echo

