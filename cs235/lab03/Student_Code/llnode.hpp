#ifndef __LLNODE_HPP__
#define __LLNODE_HPP__

class llnode
{
public:
    llnode(int value, llnode *next_ptr = NULL) : data(value), next(next_ptr) {};
    ~llnode(){};

    int data;
    llnode *next;
};
#endif //define __LLNODE_HPP__

