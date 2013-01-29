#include "Utils.h"
#include <string>
#include <cstdio>

using namespace std;

string& itoa(string& answer, int i) {
    // A 128bit number in ASCII form is less than 48 characters wide.
    // I figure we will never have a number larger than that.
    char buffer[48]; 
    sprintf(buffer, "%d", i); // Use the low level sprintf() function.
    answer = buffer;
    return answer;
}
