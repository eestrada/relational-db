#include "Maze.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>

namespace ede
{

Maze::Maze()
{
    //std::srand(std::time(NULL)); // For more random results
    std::srand(0);
}

Maze::~Maze(){}


/**
 * Create and store a random maze with an entry and exit point. (location [0,0,0] and [7,7,7] must have 1's in those spots.  The rest of the spots can be randomly 0 or 1.
 */
void Maze::createRandomMaze()
{
    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
        {
            for(size_t k = 0; k < DEPTH; ++k)
            {
                int t = std::rand() % 2;

                maze[i][j][k] = bool(t);

            }
        }
    }

    maze[0][0][0] = true;
    maze[HEIGHT - 1][WIDTH - 1][DEPTH - 1] = true;
    return;
}

bool Maze::copyMaze(bool other[HEIGHT][WIDTH][DEPTH])
{
    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
        {
            for(size_t k = 0; k < DEPTH; ++k)
            {
                maze[i][j][k] = other[i][j][k];
            }
        }
    }
    return true;
}

bool Maze::importHelper(const std::string &fileName)
{
    std::ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    bool lmaze[HEIGHT][WIDTH][DEPTH];
    int t;

    file.open(fileName.c_str());

    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
        {
            for(size_t k = 0; k < DEPTH; ++k)
            {
                file >> t;
                lmaze[i][j][k] = bool(t);
            }
        }
    }

    this->copyMaze(lmaze);

    return true;
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
    try
    {
        this->importHelper(fileName);
    }
    catch(std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
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
    std::ostringstream mzstrm;

    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
        {
            for(size_t k = 0; k < DEPTH; ++k)
            {
                mzstrm << maze[i][j][k] << " ";
            }
            mzstrm << "\n";
        }
        mzstrm << "\n";
    }

    return mzstrm.str();
}


}; // End ede namespace

