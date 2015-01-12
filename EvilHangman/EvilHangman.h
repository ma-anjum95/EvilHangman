#ifndef EVILHANGMAN_H
#define EVILHANGMAN_H


#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <stdlib.h>
#include <fstream>

#include "../EvilNode/EvilNode.h"
#include "../Dictionary/Dict/Dict.h"

using namespace std;

class EvilHangman {
    Dict *dict; // our pointer to the dictionary
    EvilNode **arr; // our hashtable array

    bool is_loaded; // bool that stores whether the wordList is loaded

    int letters;    // the number of letters of our game
    int guesses;    // the number of guesses the user is allowed to have
    int numHashTables;  // the number of hashtables
    char *displayArray; // our display array which shows the word to be guessed

    vector<char> guessed;   // our vector to store the already guessed characters temporarily
    vector<string> *wordList;   // our vector to store the words of required length

    /*
    *   This method recursively deletes the nodes
    *   It calls recursively to the next pointer
    */
    void recDel(EvilNode *ptr);

    /*
    *   This method caculates hash of a word depending upon the character 'ch'
    *   It calculates hash like a binary number, the character is like 1 in a binary number
    */
    int hash(string word, char ch);

    /*
    *   This method creates a hash table from the 'word' vector depending upon the character 'ch'
    *   Each words hash is calculated and that word is added to that index of the hashtable
    */
    void createHashTable(vector<string> *words, char ch);

    /*
    *   This method inserts the word into a hashtable that is calculated from the 'word' and the character 'ch'
    *   It is called on each word by the method 'createHashTable'
    */
    void insertInHashTable(string word, char ch);

    /*
    *   This method finds the largest index of hashtable with the max count.
    *   Then we create a vector of string with all the items in that index and then
    *   it updates the 'displayArray'
    *   Then delete the wordList and set it to the new vector just created
    */
    bool checkAndUpdateWordList(char guess);

    /*
    *   This method updates the 'displayArray' char array depending upon the current index of the hashtable
    *   Its like binary number and put all ch in the location where there is 1 in that binary number
    */
    void updateDisplayArray(char ch, int hash);
public:
    /*
    *   The parametric method which we pass the pointer to the dictionary
    *   This dict pointer will be used to get all the words with the length of 'letters'.
    *   The guesses are the number of 'guesses'
    */
    EvilHangman(Dict *dict, int letters, int guesses);

    /*
    *	Destructor
    *	calls the recDel function for removing the allocated space
    */
    ~EvilHangman();

    /*
    *	Consructs the entire interface
    *	calls the display array function, arr reset function, word family function
    *	contains check for winning
    */
    bool evilInterface(char guess);

    /*
    *	displays the array which shows the current status of our word to be guessed
    */
    char *returnDisplayArray();

    /*
    *   This method returns the number of guesses remaining
    */
    int returnGuesses();

    /*
    *   This method returns a bool depending upon if the user has won or not
    *   It method checks if the number of guesses are less than 0 we return false
    *   Then we check if there are any '_' left.
    */
    bool winCheck();

    /*
    *   This method returns the final word which was to show the user which was supposed to guessed
    *   This word is the first word in the wordList but it was never the word the user was supposed to guess.
    */
    string returnFinalWord();

    /*
    *   This method returns a character which have already been guessed.
    */
    vector<char> returnGuessed();

    /*
    *   This method return a boolean which returns whether there is a wordList or not
    */
    bool isLoaded(void);
};

#endif // EVILHANGMAN_H
