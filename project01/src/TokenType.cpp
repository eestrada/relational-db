#include "TokenType.h"

using namespace std;

string TokenTypeToString(TokenType tokenType){
    string result = "";
    switch(tokenType){
        case COMMA:              result = "COMMA"; break;
        case PERIOD:             result = "PERIOD"; break;
        case COLON_DASH:         result = "COLON_DASH"; break;
        case STRING:             result = "STRING"; break;
        case NUL:                result = "NUL"; break;
    }
    return result;
};
