CXX ?= c++
CXXFLAGS = -Wall -pedantic -ansi
BIN = gl3

run: compile
	./$(BIN)

compile:
	$(CXX) $(CXXFLAGS) -o $(BIN) gl3.cpp -lGL -lX11

glut:
	$(CXX) $(CXXFLAGS) -o glut3 glut3.cpp -lGL -lX11 -lglut
	
glew:
	$(CXX) $(CXXFLAGS) -o glew3 glew3.cpp -lGL -lX11 -lGLEW -lglut
	
