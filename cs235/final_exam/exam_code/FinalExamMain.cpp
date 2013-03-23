#include <iostream>
#include <string>
#include "RedBlackTreeFactory.h"
#include "TwoThreeTreeFactory.h"

/* This main is provided to help you test your code. Be aware that the TAs will use a separate
 * test driver that will only test your red black tree code. You may modify this code if you wish,
 * but do not try to modify the main to get your own code to work.
 */


using namespace std;
int getOption(int max, int min);
string getString();
void exitPause();

RedBlackTreeInterface * redBlackTree;
TwoThreeTreeInterface * twoThreeTree;

int main()
{
	redBlackTree = RedBlackTreeFactory::getRedBlackTree();

	if(redBlackTree == NULL) {
		cout << endl;
		cout << "Factory getRedBlackTree() returned NULL!\nExiting Test Driver (press enter to exit)" << endl;

		exitPause();
		return 0;
	}

	twoThreeTree = TwoThreeTreeFactory::getTwoThreeTree();

	cout << "Final Exam Beginning" << endl;
	while(1)
	{
		int choice = 0;
		if(twoThreeTree == NULL) {
			cout<< "Please select an option:"
				<< "\n1. Add a single word to the tree"
				<< "\n2. Add a list of words to the tree"
				<< "\n3. Remove a single word from the tree"
				<< "\n4. Print the tree"
				<< "\n5. Quit Program" << endl;
			choice = getOption(1,5);
		}
		else {
			cout<< "Please select an option:"
				<< "\n1. Add a single word to the red black tree"
				<< "\n2. Add a list of words to the red black tree"
				<< "\n3. Remove a single word from the red black tree"
				<< "\n4. Print the red black tree"
				<< "\n5. Add a single word to the two three tree"
				<< "\n6. Add a list of words to the two three tree"
				<< "\n7. Remove a single word from the two three tree"
				<< "\n8. Print the two three tree"
				<< "\n9. Quit Program" << endl;
			choice = getOption(1,9);
		}
		if(choice == 1)
		{
			//Insert the string that the user passes to the program into the tree
			cout<< "Enter the word to add to the tree (alphabetical characters, no punctuation marks, no spaces)."<<endl;
			string insertToTree;
			insertToTree = getString();
			redBlackTree->add(insertToTree);
		}
		else if(choice == 2)
		{
			//Insert the string that the user passes to the program into the tree
			cout<< "Enter the string to add to the tree."
				<< "\n(alphabetical characters, no punctuation marks, and with white space as the delimiter separating words)" << endl;
			string insertToTree;
			insertToTree = getString();
			redBlackTree->addPhrase(insertToTree);
		}
		else if(choice == 3)
		{
			//Remove the string that the user passes to the program into the tree
			cout << "Enter the word to remove from the tree (alphabetical characters, no punctuation marks, no spaces)."<<endl;
			string removeFromTree;
			removeFromTree = getString();
			redBlackTree->remove(removeFromTree);
		}
		else if(choice == 4)
		{
			cout << "Your tree:" << endl;
			cout << "" << redBlackTree->printTree() << endl;
		}
		else if(choice == 5 && twoThreeTree == NULL)
		{
			break;
		}
		else if(choice == 5 && twoThreeTree != NULL)
		{
			//Insert the string that the user passes to the program into the tree
			cout<< "Enter the word to add to the tree (alphabetical characters, no punctuation marks, no spaces)."<<endl;
			string insertToTree;
			insertToTree = getString();
			twoThreeTree->add(insertToTree);
		}
		else if(choice == 6)
		{
			//Insert the string that the user passes to the program into the tree
			cout<< "Enter the string to add to the tree."
				<< "\n(alphabetical characters, no punctuation marks, and with white space as the delimiter separating words)" << endl;
			string insertToTree;
			insertToTree = getString();
			twoThreeTree->addPhrase(insertToTree);
		}
		else if(choice == 7)
		{
			//Remove the string that the user passes to the program into the tree
			cout << "Enter the word to remove from the tree (alphabetical characters, no punctuation marks, no spaces)."<<endl;
			string removeFromTree;
			removeFromTree = getString();
			twoThreeTree->remove(removeFromTree);
		}
		else if(choice == 8)
		{
			cout << "Your tree:" << endl;
			cout << "" << twoThreeTree->printTree() << endl;
		}
		else
		{
			break;
		}
	}
	cout << "Thanks for Playing!" << endl;

	exitPause();
	return 0;
}

//-------------------------------------------------------------------------------------
int getOption(int min, int max)
{
	int input = 0;
	bool done = false;
	while(!done)
	{
		input = 0;
		cin >> input;
		cin.ignore(1000,'\n');
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Error: Invalid" << endl;
		}
		else if(input < min  ||  input > max)
		{
			cout << "Error: Invalid number" << endl;
		}
		else
		{
			done = true;
		}
	}
	return input;
}

string getString()
{
	string input = "";
	bool done = false;
	while(!done)
	{
		input = "";
		getline(cin, input);
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Error: Invalid name" << endl;
		}
		else
		{
			done = true;
		}
	}
	return input;
}

string getWord()
{
	string input = "";
	bool done = false;
	while(!done)
	{
		input = "";
		getline(cin, input);
		if(cin.fail())
		{
			cin.clear();
			cin.ignore(1000,'\n');
			cout << "Error: Invalid name" << endl;
		}
		else
		{
			done = true;
		}
	}
	return input;
}

void exitPause() {
	#ifdef ON_WINDOWS
		system("pause");
	#else

	#endif
}
