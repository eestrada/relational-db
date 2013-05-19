#include "Arena.h"
using namespace::std;
int main(int argc, const char* argv[]){
    //make arena
    Arena* shkoder = new Arena();
    //test arena
    bool testBool1 = shkoder->addFighter("Fumblemore C 100 20 10 100");
    bool testBool2 = shkoder->addFighter("Sanjuan R 10 1 1 10");
    bool testRM = shkoder->removeFighter("Sanjuan");
    
    cout << "testBool1:\t" << testBool1;
    cout << "\ntestBool2:\t" << testBool2;
    cout << "\ntestRM:\t\t" << testRM << endl;
    cout << "shkoder size:\t" << shkoder->getSize() << endl;
    
    FighterInterface* thisOne = shkoder->getFighter("Fumblemore");
    
    thisOne->regenerate();
    thisOne->useAbility();
    thisOne->useAbility();
    thisOne->useAbility();

    
    cout << thisOne->getDamage() << endl;
    thisOne->useAbility();
    thisOne->reset();
    cout << thisOne->getDamage() << endl;
}
