CXX ?= c++
CXXFLAGS = -Wall -pedantic -std=c++11
# CXXFLAGS = -Wall -pedantic -ansi # uncomment if C++11 is not supported
BIN = RUN_ME.bin

.PHONY: run compile gl3 glut3 glew3

run: compile
	./$(BIN)
	rm ./$(BIN)

compile:
	$(CXX) $(CXXFLAGS) -o $(BIN) main.cpp -lglut -lGLU -lGL -lX11

gl3:
	$(CXX) $(CXXFLAGS) -o gl3.bin gl3.cpp -lGL -lX11

glut3:
	$(CXX) $(CXXFLAGS) -o glut3.bin glut3.cpp -lGL -lX11 -lglut
	
glew3:
	$(CXX) $(CXXFLAGS) -o glew3.bin glew3.cpp -lGL -lX11 -lGLEW -lglut
	
