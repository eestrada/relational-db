#include "Lex.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if(argc < 2) { return -1; }

    Lex lex(argv[1]);
    cout << lex.toString();
    return 0;
}
