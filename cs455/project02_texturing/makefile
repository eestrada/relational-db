CXX ?= c++
CXXFLAGS = -Wall -pedantic -ansi
BIN = gl3.bin

.PHONY: run gl3 glut3 glew3

run: gl3
	./$(BIN)

gl3:
	$(CXX) $(CXXFLAGS) -o $(BIN) gl3.cpp -lGL -lX11

glut3:
	$(CXX) $(CXXFLAGS) -o glut3.bin glut3.cpp -lGL -lX11 -lglut
	
glew3:
	$(CXX) $(CXXFLAGS) -o glew3.bin glew3.cpp -lGL -lX11 -lGLEW -lglut
	
