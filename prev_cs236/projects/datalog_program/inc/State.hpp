#ifndef STATE_H
#define STATE_H

#include <string>

/**
 * The states of the finite state machine defined in an enumerated type.
 */
enum State { Comma, Period, Q_Mark, Left_Paren, Right_Paren, SawColon,
            Colon_Dash, Multiply, Add, PossiblySawSchemes, PossiblySawFacts,
            PossiblySawRules, PossiblySawQueries, ProcessingID, SawAQuote,
            ProcessingString, PossibleEndOfString, Comment, CommentStartGeneric,
            CommentSingleLine, CommentMultiLine, WhiteSpace,
            Undefined, Start, End };

    /**
     * Converts a state to a string.
     * 
     * Parameters: state -- the state to be converted to a string.
     * PreCondition: none
     * Postcondition: result = the string representation of the state which
     *                         looks exactly like its State name.
     */
    std::string StateToString(State s);
#endif
