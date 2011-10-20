CC = g++
CFLAGS = -Wall -g -I . -I inc/
SUPP = ../string.supp
ARGS = 

#LIB = cs240utils/lib/libcs240utils.a
LIB = cs240utils/obj/CommandRunner.o cs240utils/obj/FileSystem.o cs240utils/obj/HTMLTokenizer.o cs240utils/obj/StringUtil.o cs240utils/obj/FileInputStream.o cs240utils/obj/HTMLToken.o cs240utils/obj/HTTPInputStream.o cs240utils/obj/URLInputStream.o
BIN = bin/crawlmain
OBJ_FILES = obj/LinkedList.o obj/BST.o obj/main.o
DEPS = inc/LinkedList.h inc/BST.h
STYLECHECKER = ~/Documents/CppCheckStyle/CppCheckStyle

.PHONY : bin lib memcheck clean

bin : $(BIN)

lib : $(LIB)
	@- mkdir -p cs240utils/lib/
	ar -rcs cs240utils/lib/libcs240utils.a cs240utils/obj/*.o

cs240utils/obj/%.o : cs240utils/src/%.cpp
	@- mkdir -p cs240utils/obj/
	$(CC) -c -o $@ $< $(CFLAGS) -I cs240utils/inc/

memcheck : $(BIN)
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=$(SUPP) $(BIN) $(ARGS)

$(BIN) : $(OBJ_FILES) $(DEPS) $(LIB)
	@- mkdir -p bin
	$(CC) -o $@ $(OBJ_FILES) $(LIB) $(CFLAGS)

obj/%.o : src/%.cpp $(DEPS)
	@- mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)
	@ echo
	$(STYLECHECKER) $<
	@ echo

clean :
	@ echo "Removing generated files"
	rm -vrf obj
	rm -vrf bin
	rm -vrf cs240utils/lib/
	rm -vrf cs240utils/obj/
