#include "Maze.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <ciso646>

namespace ede
{

const ::std::string coord::toString() const
{
    ostringstream out;

    out << "(" << int(this->x) << ", " << int(this->y) << ", " << int(this->z) << ")";
    return out.str();
}

::std::ostream & operator<<(::std::ostream &out, const coord &crd)
{
    return out << crd.toString().c_str();
}

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

                maze[i][j][k] = color(t);

            }
        }
    }

    maze[0][0][0] = BACKGROUND;
    maze[HEIGHT - 1][WIDTH - 1][DEPTH - 1] = BACKGROUND;
    return;
}

bool Maze::copyMaze(color other[HEIGHT][WIDTH][DEPTH])
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
    file.open(fileName.c_str());

    color tmp[HEIGHT][WIDTH][DEPTH];
    int t;

    for(size_t i = 0; i < HEIGHT; ++i)
    {
        for(size_t j = 0; j < WIDTH; ++j)
        {
            for(size_t k = 0; k < DEPTH; ++k)
            {
                file >> t;
                tmp[i][j][k] = color(t);
            }
        }
    }

    this->copyMaze(tmp);

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
        //std::cerr << "Maze could not be imported due to following error: ";
        //std::cerr << e.what() << std::endl;
        return false;
    }

    return true;
}


bool Maze::traverseHelper(color m[HEIGHT][WIDTH][DEPTH], int h, int w, int d)
{
    if(h < 0 or w < 0 or d < 0 or h >= HEIGHT or w >= WIDTH or d >= DEPTH)
    {
        return false; // Out of bounds
    }
    else if (m[h][w][d] != BACKGROUND)
    {
        return false; // Barrier or dead end
    }
    else if (h == HEIGHT-1 and w == WIDTH-1 and d == DEPTH-1)
    {
        m[h][w][d] = PATH; // On path!
        path.push_front( coord(HEIGHT-1, WIDTH-1, DEPTH-1) );
        return true; // Also, is maze exit;
    }
    else
    {
        // Recursively attempt to find a path from each neighbor.
        // Tentatively mark cell as on path.
        m[h][w][d] = PATH;
        if(traverseHelper(m, h-1, w, d)
           or traverseHelper(m, h+1, w, d)
           or traverseHelper(m, h, w-1, d)
           or traverseHelper(m, h, w+1, d)
           or traverseHelper(m, h, w, d-1) 
           or traverseHelper(m, h, w, d+1) )
        {
            // Why did I need to reverse the coords to get this to work?
            path.push_front( coord(d,w,h) );
            return true;
        }
        else
        {
            m[h][w][d] = TEMPORARY; // Dead end.
            return false;
        }
    }
}

/**
 * Traverses the current maze in storage, storing the path taken to solve the maze if the maze was solvable.
 * 
 * @return true if the maze was solvable, false if unsolvable
 */
bool Maze::traverseMaze()
{
    path.clear();

    bool ret = true;

    try
    {
        ret = this->traverseHelper(this->maze, 0, 0, 0);
    }
    catch(std::exception &e)
    {
        //std::cerr << "Could not traverse maze due to following error: ";
        //std::cerr << e.what() << std::endl;
        ret = false;
    }

    //this->getMazePath();

    return ret;
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
    std::deque<coord>::iterator iter = path.begin();
    std::ostringstream out;

    while(iter != path.end())
    {
        out << *iter; ++iter;
        if(iter != path.end()) out << "\n";
    }

    //std::cerr << out.str() << std::endl;

    return out.str();
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

