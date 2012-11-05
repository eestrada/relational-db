# Name phony targets
.PHONY: run dirs test build clean

# Run test program
run : build
	./bin/test.bin

# Run test program from class
test : 
	./Run_Test_Driver.sh

./bin :
	mkdir -p bin

# Build source program
build : ./bin
	g++ -Wall -o ./bin/test.bin Student_Code/*.cpp Student_Code/*.cxx 

# Clean up files
clean :
	rm -rf bin
	rm -f ./dont_run_me

