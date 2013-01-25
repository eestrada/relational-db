CC = g++
CFLAGS = -Wall -g -I . -I inc/ -I cs240utils/inc/
SUPP = ./string.supp
ARGS = file:///users/ta/cs240ta/webcrawler/file/student/index.html

#LIB = cs240utils/lib/libcs240utils.a
LIB = cs240utils/obj/CommandRunner.o cs240utils/obj/FileSystem.o cs240utils/obj/HTMLTokenizer.o cs240utils/obj/StringUtil.o cs240utils/obj/FileInputStream.o cs240utils/obj/HTMLToken.o cs240utils/obj/HTTPInputStream.o cs240utils/obj/URLInputStream.o
BIN = bin/crawlmain
OBJ_FILES = obj/main.o
DEPS = inc/parser.hpp inc/pgindex.hpp inc/webpage.hpp inc/word.hpp
STYLECHECKER = ~cs240ta/bin/CppCheckStyle/CppCheckStyle

.PHONY : bin lib test clean memcheck

bin : lib $(BIN)
	@ echo

lib : $(LIB)
	@- mkdir -p cs240utils/lib/
	ar -rcs cs240utils/lib/libcs240utils.a cs240utils/obj/*.o
	@ echo

test : memcheck
	@ echo 'This is a test. Enjoy!'
	@ echo 'The current program arguments are:'
	@ echo $(ARGS)

clean :
	@ echo "Removing generated files"
	rm -rf obj
	rm -rf bin
	rm -rf cs240utils/lib/
	rm -rf cs240utils/obj/
	@ echo

memcheck : bin
	valgrind --tool=memcheck --leak-check=yes --max-stackframe=5000000 \
	--show-reachable=yes --suppressions=$(SUPP) $(BIN) $(ARGS)
	@ echo

cs240utils/obj/%.o : cs240utils/src/%.cpp
	@- mkdir -p cs240utils/obj/
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN) : $(OBJ_FILES) $(DEPS) $(LIB)
	@- mkdir -p bin
	$(CC) -o $@ $(OBJ_FILES) cs240utils/lib/libcs240utils.a $(CFLAGS)

obj/%.o : src/%.cpp $(DEPS)
	@- mkdir -p obj
	$(CC) -c -o $@ $< $(CFLAGS)
	@ echo
	$(STYLECHECKER) $< $(DEPS)
	@ echo


