# Name phony targets
.PHONY: run build clean

# Run test program
run: build
	./test.bin

# Build source program
build:
	g++ -Wall -o test.bin Student_Code/*.cpp Student_Code/*.cxx

# Clean up files
clean:
	rm -f ./test.bin


