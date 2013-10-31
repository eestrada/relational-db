#if !defined(_MAIN_HPP_)
#define _MAIN_HPP_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
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
    typename std::vector<T>::const_iterator iter;

    for(iter = v.begin(); iter != v.end(); ++iter)
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

    typename std::vector<T>::iterator iter;

    for(iter = v.begin(); iter != v.end(); ++iter)
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
    //char input[1024];
    std::string input;

    //rand_seq(test);

    if(argc)
    {
        input = argv[1];
    }
    else
    {
        std::cout << "Please enter the file to read in: " << std::flush;
        std::cin >> input;
    }
    std::ifstream in(input.c_str());
    std::ofstream out("OUTPUT.txt");
    std::ofstream hout("HASH_OUTPUT.txt");

    huffman h(in);

    h.output(out);
    h.hash_output(hout);

    return EXIT_SUCCESS;
}

}

#endif // Defined _MAIN_HPP_
