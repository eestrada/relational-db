#include "Lex.h"

#include "Input.h"
#include "TokenType.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cctype>

using namespace std;

Lex::Lex() {
	input = new Input();
    generateTokens(input);
}

Lex::Lex(const char* filename) {
    input = new Input(filename);
    generateTokens(input);
}

Lex::Lex(istream& istream) {
    input = new Input(istream);
    generateTokens(input);
}

Lex::Lex(const Lex& lex) {
    input = new Input(*lex.input);
    tokens = new vector<Token*>();

    vector<Token*>::iterator iter;
    for(iter=lex.tokens->begin(); iter != lex.tokens->end(); iter++) {
        Token* newToken = new Token(**iter);
        tokens->push_back(newToken);
    }

    index = lex.index;
    state = lex.state;
}

Lex::~Lex(){
    for (unsigned int i = 0; i < tokens->size(); i++) {
        delete (*tokens)[i];
    }
    delete tokens;
    delete input;
}

bool Lex::operator==(const Lex& lex) {
    bool result = (tokens->size() == lex.tokens->size()) && (index == lex.index);
    if(result) {
        vector<Token*>::iterator iter1;
        vector<Token*>::iterator iter2;
        iter1 = tokens->begin();
        iter2 = lex.tokens->begin();
        while(result && iter1 != tokens->end() && iter2 != lex.tokens->end()) {
            result = **iter1 == **iter2;
            iter1++;
            iter2++;
        }
        result = result && iter1 == tokens->end() && iter2 == lex.tokens->end();
    }
    return result;
}

string Lex::toString() const {
    unsigned int count = 0;
    string result;
    while(count < tokens->size()) {
        Token* token = (*tokens)[count];
        result += token->toString();
        count++;
    }
    result += "Total Tokens = ";
    string countToString;
    result += itoa(countToString, count);
    result += "\n";
    return result;
}

void Lex::generateTokens(Input* input) {
    tokens = new vector<Token*>();
    index = 0;

    state = Start;
    while(state != End) {
        state = nextState();
    }

    emit(END);
}

Token* Lex::getCurrentToken() {
    return (*tokens)[index];
}

void Lex::advance() {
    index++;
}

bool Lex::hasNext() {
    return index < int(tokens->size());
}

State Lex::processKeyword(TokenType t)
{
    State result;
    const static string keywords[] = {"Schemes", "Facts", "Rules", "Queries"};
    int kindex;
    bool isKeyword = true;

    switch(t){
        case SCHEMES:   kindex = 0; break;
        case FACTS:     kindex = 1; break;
        case RULES:     kindex = 2; break;
        case QUERIES:   kindex = 3; break;
        default:    throw logic_error("ERROR: Type given is not keyword.");
        }

    char character = input->getCurrentCharacter();

    size_t j = 1;//Start on the second character since we already know what the first was.
    while(isalnum(character))
    {
        if(j >= keywords[kindex].size() || character != keywords[kindex][j++])
        {
            isKeyword = false;
        }

        input->advance();
        character = input->getCurrentCharacter();
    }

    if(isKeyword && j == keywords[kindex].size()) {emit(t);}
    else {emit(ID);}
    result = getNextState();

    return result;
}

State Lex::nextState() {
    State result;
    char character;

    switch(state) {
        case Start:               result = getNextState(); break;
        case Comma:               emit(COMMA); result = getNextState(); break;
        case Period:              emit(PERIOD); result = getNextState(); break;
        case Q_Mark:              emit(Q_MARK); result = getNextState(); break;
        case Left_Paren:          emit(LEFT_PAREN); result = getNextState(); break;
        case Right_Paren:         emit(RIGHT_PAREN); result = getNextState(); break;
        case SawColon:
            character = input->getCurrentCharacter();
            if(character == '-') {
                result = Colon_Dash;
                input->advance();
            } else { //Every other character
                emit(COLON);
                result = getNextState(); }
            break;
        case Colon_Dash:          emit(COLON_DASH); result = getNextState(); break;
        case Multiply:            emit(MULTIPLY); result = getNextState(); break;
        case Add:                 emit(ADD); result = getNextState(); break;
        case PossiblySawSchemes:  result = this->processKeyword(SCHEMES); break;
        case PossiblySawFacts:    result = this->processKeyword(FACTS); break;
        case PossiblySawRules:    result = this->processKeyword(RULES); break;
        case PossiblySawQueries:  result = this->processKeyword(QUERIES); break;
        case ProcessingID:          
            character = input->getCurrentCharacter();
            if(isalnum(character)){input->advance();}
            else{emit(ID); result = getNextState();}
            break;
        case ProcessingString:  
            character = input->getCurrentCharacter();
            if(character == '\'') { result = PossibleEndOfString; }
            else if(character == -1) { result = Undefined; }
            else { result = ProcessingString; } /*Every other character*/
            input->advance();
            break;
        case PossibleEndOfString:
            if(input->getCurrentCharacter() == '\'') {
                input->advance();
                result = ProcessingString;
            } else { //Every other character
                emit(STRING);
                result = getNextState(); }
            break;
        case CommentStartGeneric:
            character = input->getCurrentCharacter();
            if(character == '|') { input->advance(); result = CommentMultiLine; }
            else { result = CommentSingleLine;}
            break;
        case CommentSingleLine:
            character = input->getCurrentCharacter();
            if(character == '\n' || character == EOF) { result = Comment; }
            else { input->advance(); result = CommentSingleLine; }
            break;
        case CommentMultiLine:
            character = input->getCurrentCharacter();
            if(character == '|')
            { 
                input->advance();
                character = input->getCurrentCharacter();
                if(character == '#')
                {
                    input->advance();
                    emit(COMMENT);
                    result = getNextState();
                }
                else
                {
                    emit(UNDEFINED);
                    result = getNextState();
                }
            }
            else if(character == EOF) { emit(UNDEFINED); result = getNextState(); }
            else { input->advance(); result = CommentMultiLine; }
            break;
        case Comment:
            emit(COMMENT);
            //input->advance();
            result = getNextState(); 
            break;
        case WhiteSpace:  
            character = input->getCurrentCharacter();
            if(!isspace(character)) {
                input->mark();//Mark start of next token. Do not tokenize whitespace.
                result = getNextState();
            } else { //Still parsing white space
                input->advance(); 
                result = WhiteSpace; }
            break;
        case Undefined:           emit(UNDEFINED); result = getNextState(); break;
        case End:
            throw logic_error("ERROR:: in End state:, the Input should be empty once you reach the End state."); 
            break;
        default:
            throw logic_error("ERROR: Hit end of switch statement. Undefined state."); 
    };
    return result;
}

State Lex::getNextState() {
    State result;
    char currentCharacter = input->getCurrentCharacter();

    //The handling of checking for whitespace and setting the result to Whitespace and
    //checking for letters and setting the result to Id will probably best be handled by
    //if statements rather then the switch statement.

    if(currentCharacter == ',') { result = Comma; }
    else if(currentCharacter == '.') { result = Period; }
    else if(currentCharacter == '?') { result = Q_Mark; }
    else if(currentCharacter == '(') { result = Left_Paren; }
    else if(currentCharacter == ')') { result = Right_Paren; }
    else if(currentCharacter == ':') { result = SawColon; }
    else if(currentCharacter == '*') { result = Multiply; }
    else if(currentCharacter == '+') { result = Add; }
    else if(currentCharacter == 'S') { result = PossiblySawSchemes; }
    else if(currentCharacter == 'F') { result = PossiblySawFacts; }
    else if(currentCharacter == 'R') { result = PossiblySawRules; }
    else if(currentCharacter == 'Q') { result = PossiblySawQueries; }
    else if(currentCharacter == '#') { result = CommentStartGeneric; }
    else if(currentCharacter == '\'') { result = ProcessingString; }
    else if(isalpha(currentCharacter)){result = ProcessingID;}
    else if(isspace(currentCharacter)){ result = WhiteSpace; }
    else if(currentCharacter == EOF) { result = End; }
    else { result = Undefined; }

    input->advance();
    return result;
}

void Lex::emit(TokenType tokenType) {
    Token* token = new Token(tokenType,input->getTokensValue(),input->getCurrentTokensLineNumber());
    storeToken(token);
    input->mark();
}

void Lex::storeToken(Token* token) {
    //This section shoud ignore whitespace and comments and change the token 
    //type to the appropriate value if the value of the token is "Schemes", 
    //"Facts", "Rules", or "Queries".
    tokens->push_back(token);
}

