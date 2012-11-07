# variables

BINDIR = bin
BIN = $(BINDIR)/test.bin

# Name phony targets
.PHONY: run drvr235 mkdirs build clean

# Run test program
run : build
	./$(BIN)

drvr235 :
	./Run_Test_Driver.sh

mkdirs : 
	mkdir -p bin

# Build source program
build : mkdirs
	g++ -Wall -o ./$(BIN) Student_Code/*.cpp Student_Code/*.cxx

# Clean up files
clean :
	@-rm -vrf $(BINDIR)
	@-rm -vf ./dont_run_me


