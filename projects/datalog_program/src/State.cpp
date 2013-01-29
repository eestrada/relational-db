#include "State.h"
#include <string>

using namespace std;

string StateToString(State tokenType){
    string result = "";
    switch(tokenType){
        case Comma:                      result = "Comma"; break;
        case Period:                     result = "Period"; break;
        case Q_Mark:                     result = "Q_Mark"; break;
        case Left_Paren:                 result = "Left_Paren"; break;
        case Right_Paren:                result = "Right_Paren"; break;
        case SawColon:                   result = "SawColon"; break;
        case Colon_Dash:                 result = "Colon_Dash"; break;
        case Multiply:                   result = "Multiply"; break;
        case Add:                        result = "Add"; break;
        case PossiblySawSchemes:         result = "PossiblySawSchemes"; break;
        case PossiblySawFacts:           result = "Facts"; break;
        case PossiblySawRules:           result = "Rules"; break;
        case PossiblySawQueries:         result = "PossiblySawQueries"; break;
        case ProcessingID:               result = "ProcessingID"; break;
        case SawAQuote:                  result = "SawAQuote"; break;
        case ProcessingString:           result = "ProcessingString"; break;
        case PossibleEndOfString:        result = "PossibleEndOfString"; break;
        case Comment:                    result = "Comment"; break;
        case CommentStartGeneric:        result = "CommentStartGeneric"; break;
        case CommentSingleLine:          result = "CommentSingleLine"; break;
        case CommentMultiLine:           result = "CommentMultiLine"; break;
        case WhiteSpace:                 result = "WhiteSpace"; break;
        case Undefined:                  result = "Undefined"; break;
        case Start:                      result = "Start"; break;
        case End:                        result = "End"; break;
    }
    return result;
};

