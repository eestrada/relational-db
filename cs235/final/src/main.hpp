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

template < typename T >
std::ostream & operator<<(std::ostream &out, ede::pqueue<T> pq)
{
    while(pq)
    {
        out << pq.top() << ", ";
        pq.pop();
    }

    return out;
}

template < typename T >
std::ostream & operator<<(std::ostream &out, const std::vector<T> &v)
{
    for(auto iter = v.cbegin(); iter != v.cend(); ++iter)
    {
        out << *iter << ", ";
    }

    return out;
}

namespace ede
{

template < typename T >
void rand_seq( ede::pqueue<T> &seq )
{
    std::vector<T> v;

    for(int i = -50; i <= 50; ++i)
    {
        v.push_back(i);
    }

    std::random_shuffle( v.begin(), v.end() );

    for(auto iter = v.begin(); iter != v.end(); ++iter)
    {
        seq.push(*iter);
    }

    std::cerr << "\n" << v << std::endl;
    std::cerr << "\n" << seq << std::endl;
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

    return EXIT_SUCCESS;
}

}

#endif // Defined _MAIN_HPP_
