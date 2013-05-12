#include "Maze.hpp"
#include <string>
#include <iostream>
#include <sstream>

namespace ede
{

Maze::~Maze()
{

}


/**
 * Create and store a random maze with an entry and exit point. (location [0,0,0] and [7,7,7] must have 1's in those spots.  The rest of the spots can be randomly 0 or 1.
 */
void Maze::createRandomMaze()
{
    return;
}


/**
 * Read from the given file (see maze_sample.txt for format) and store it as a maze
 * 
 * @param fileName The file name of the file to be imported
 * 
 * @return true if the file was successfully read/imported, false if an error occurred when parsing/reading the file
 */
bool Maze::importMaze(std::string fileName)
{
    return bool();
}


/**
 * Traverses the current maze in storage, storing the path taken to solve the maze if the maze was solvable.
 * 
 * @return true if the maze was solvable, false if unsolvable
 */
bool Maze::traverseMaze()
{
    return bool();
}


/**
 * Returns the path from the most recently traversed maze. The string format should be each position taken 
 * separated by newlines (see format on website).
 * 
 * @return the path to the most recent maze traversed
 * 		if no maze has been solved yet, return an empty string
 */
std::string Maze::getMazePath()
{
    return std::string();
}


/**
 * Get the current maze stored in a single string (see website for format)
 * 
 * @return a string representation of your maze
 */
std::string Maze::getMaze()
{
    return std::string();
}


}; // End ede namespace

