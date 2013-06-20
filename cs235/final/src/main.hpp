#if !defined(_MAIN_HPP_)
#define _MAIN_HPP_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "pqueue.hpp"
#include "huffman.hpp"

namespace ede
{

template < typename T >
void rand_seq( ede::pqueue<T> &seq )
{
    std::vector<T> v;

    for(int i = -50; i < 50; ++i)
    {
        v.push_back(i);
    }

    std::random_shuffle( v.begin(), v.end() );

    for(auto iter = v.begin(); iter != v.end(); ++iter)
    {
        seq.push(*iter);
    }
}

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
    ede::pqueue<int> test;

    rand_seq(test);

    std::cerr << "" << std::endl;
    while(test)
    {
        std::cerr << test.top() << ", ";
        test.pop();
    }
    std::cerr << "\n" << std::endl;

    for(int i = 0; i < argc; ++i)
        std::cerr << argv[i] << std::endl;

/*
    char c;
    for(std::cin.get(c); !std::cin.eof(); std::cin.get(c))
        std::cout.put(c);
*/

    return EXIT_SUCCESS;
}

}

#endif // Defined _MAIN_HPP_
