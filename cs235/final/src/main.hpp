#if !defined(_MAIN_HPP_)
#define _MAIN_HPP_

#include <cstdlib>
#include <iostream>
#include "hash_map.hpp"
#include "pqueue.hpp"
#include "huffman.hpp"

namespace ede
{

/* 
 * Runs program according to arguments.
 *
 * Because we are in a namespace, the compiler won't complain about the
 * function name "main".
 *
 * @param argc
 *      argument count
 * @param argv
 *      argument vector
 * @return
 *      program exit value
 */
int main(int argc, char **argv)
{
    std::cerr << "Smells like testing...\n" << std::flush;
    // Nothing is implemented yet, so return failure for now.
    return EXIT_FAILURE;
}

}

#endif // Defined _MAIN_HPP_
