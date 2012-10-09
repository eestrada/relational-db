# Name phony targets
.PHONY: run build clean

# Run test program
run: build
	./test.bin

# Build source program
build:
	g++ -o test.bin *.cpp *.cxx -Wall

# Clean up files
clean:
	rm -f ./test.bin
