#if !defined(_HUFFMAN_HPP_)
#define _HUFFMAN_HPP_

#include "hash_map.hpp"
#include "pqueue.hpp"
#include <map>
#include <iostream>
#include <sstream>
#include <fstream>

namespace ede
{

struct hnode
{
    char symbol;
    size_t count;
    hnode *lchild, *rchild;

    hnode(char s='\0', size_t c=0, hnode *l=NULL, hnode *r=NULL ) : 
        symbol(s), count(c), lchild(l), rchild(r) {}

    hnode(const hnode &other) : symbol(other.symbol), count(other.count), 
        lchild(other.lchild), rchild(other.rchild) {}

    ~hnode(){}

    bool operator<(const hnode &other) const
    {
        return this->count < other.count;
    }
    bool operator>(const hnode &other) const
    {
        return this->count > other.count;
    }
};


class huffman
{
public:
    huffman(std::istream &in) : pq(), smap()
    {
        std::stringstream mycp;

        char c;
        for(in.get(c); !in.eof(); in.get(c))
        {
            mycp.put(c);
        }

        message = mycp.str();

        process_input(mycp);
        build_tree();
        build_hash();
    }

    void output(std::ostream &out)
    {
        out << "Original:" << message << "\n";
        out << "Encoded:";
        encoded_message(out);

        out << "Decoded:";

        std::ostringstream tmp;
        encoded_message(tmp);
        std::string dstr = decode(tmp.str());
        out << dstr << "\n";

        out << "Matches:";
        out << std::boolalpha << (dstr == message) << "\n";
    }

    void hash_output(std::ostream &out)
    {
        std::cerr << "hash_output implemented with std::map class, not custom hash table class!\n";
        std::ostringstream sout;

        hnode *n = new hnode(pq.top());
        hash_output(out, std::string(), n);
    }
private: // Private Member functions
    std::string decode(std::string encoded)
    {
        std::istringstream sin(encoded);
        std::ostringstream out;

        std::string codestr;

        while(!sin.eof())
        {
            char c;
            sin.get(c);
            codestr += c;

            if(r_huffenc.count(codestr))
            {
                out << r_huffenc[codestr] << std::flush;
                codestr = "";
            }

        }

        return out.str();
    }

    void encoded_message(std::ostream &out)
    {
        std::istringstream sin(message);

        char c;
        for(sin.get(c); !sin.eof(); sin.get(c)) { out << huffenc[c]; }
        out << "\n";
    }

    void hash_output(std::ostream &out, std::string code, hnode *node)
    {
        if(node == NULL) return;
        else if(node->symbol == '\0')
        {
            //out << "\n\nEncountered empty node. Parse children!\n\n";
            hash_output(out, code + "0", node->lchild);
            hash_output(out, code + "1", node->rchild);
        }
        else
        {
            if(node->symbol == ' ')
                out << "' '" << "\t" << smap[node->symbol] << "\t" << code << "\n";
            else if(node->symbol == '\n')
                out << "'\\n'" << "\t" << smap[node->symbol] << "\t" << code << "\n";
            else if(node->symbol == '\t')
                out << "'\\t'" << "\t" << smap[node->symbol] << "\t" << code << "\n";
            else
                out << node->symbol << "\t" << smap[node->symbol] << "\t" << code << "\n";
        }
    }

    void build_hash(std::string code, hnode *node)
    {
        if(node == NULL) return;
        else if(node->symbol == '\0')
        {
            //out << "\n\nEncountered empty node. Parse children!\n\n";
            build_hash(code + "0", node->lchild);
            build_hash(code + "1", node->rchild);
        }
        else
        {
            huffenc[node->symbol] = code;
            r_huffenc[code] = node->symbol;
        }
    }

    void build_hash()
    {
        hnode *n = new hnode(pq.top());
        build_hash(std::string(), n);
    }

    void build_tree()
    {
        while(pq.size() > 1)
        {
            hnode *l = new hnode( pq.top() );
            pq.pop();

            hnode *r = new hnode( pq.top() );
            pq.pop();
            
            size_t size = l->count + r->count;

            hnode p('\0', size, l, r);

            pq.push(p);
        }
    }

    void process_input(std::istream &in)
    {
        char c;
        for(in.get(c); !in.eof(); in.get(c))
        {
            smap[c] += 1;
        }

        std::map<char, size_t>::iterator iter = smap.begin();
        
        for(iter = smap.begin(); iter != smap.end(); ++iter)
        {
            //std::cerr << iter->first << ": " << iter->second << std::endl;
            pq.push(hnode(iter->first, iter->second));
        }

        //std::cerr << "\n\n";
        
        pqueue<hnode> tmp(pq);
        
        while(tmp)
        {
            //std::cerr << tmp.top().symbol << ": " << tmp.top().count << std::endl;
            tmp.pop();
        }
    }
private: // Member variables
    std::string message;
    pqueue<hnode> pq;
    std::map<char, size_t> smap;
    std::map<char, std::string> huffenc;
    std::map<std::string, char> r_huffenc;
};

}

#endif // Defined _HUFFMAN_HPP_
