ARGS=-I ./ede_utils/inc -I ../../lab5/Student_Code/

.PHONY: run build clean

run: build
	./test.bin

build:
	g++ $(ARGS) -o test.bin *.cpp *.cxx

clean:
	rm -f ./test.bin
