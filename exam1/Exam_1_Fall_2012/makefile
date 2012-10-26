ARGS=-Wall -I ./ede_utils/inc 

.PHONY: run build clean

run: build
	./test.bin

build:
	g++ $(ARGS) -o test.bin *.cpp *.cxx

clean:
	rm -f ./test.bin
