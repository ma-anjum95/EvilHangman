#ifndef DICT_H
#define DICT_H

#include <iostream>
#include <string>
#include <vector>

#include "../DictNode/DictNode.h"

using namespace std;

#ifndef ALPHABETS
#define ALPHABETS 27
#endif

class Dict {
    DictNode *root; // the root of the dictionary tree
    int size; // number of words in the dictionary
    bool loaded; // bool storing wether the dictionary has been loaded or not

    /*
    *   The two vectors that will be used in guess the words
    *   from the given word.
    *   The first vector stores all the words from the dictionary whose indexes
    *   are stored in the array of vectors "alphaOccur" which represent individual elements.
    */
    vector<string> *wordArray;
    vector<int> *alphaOccur;

    /*
    *	This method takes in a character and return the correct int location of that character in node branch.
    *	For alphabets a-z & A-Z it returns b/w 0 - 25.
    *	For " ' " 26 is returned.
    */
    int alphaLoc(char ch);

    /*
    *	This method returns a character depending on the int passed in as a parameter.
    *	The int usually returns a character depending upon the index of the branch given.
    */
    char intLoc(int loc);

    /*
    *   It fixes the word passed in as a parameter.
    *   Since the word is passed by reference the original copy of the word is changed.
    *   It removes all the characters from the string which are not alphabets.
    */
    void fixWord(string &word);

    /*
    *	This method loads the dictionary into the memory.
    *	It takes in a parameter the path to the dictionary
    *	It opens the dictionary file takes the individual word and call the "addWord" method on the word.
    */
    bool loadDict(string dictionary);

    /*
    *	This method add an individual word into our tree data structure.
    *	It starts from the root and goes over the word, traversing over the structure.
    *	If a node doesn't exist it also add that node.
    *	At the end of the word the current node's "is_word" boolean is set to true.
    */
    void addWord(string word);

    /*
    *   This method adds the index of the word from the dictionary into
    *   the vector of indiviual alphabets contained in the word.
    */
    void addToOccur(string word, int index);

    /*
    *	This method recursively deletes the nodes of the data structure
    *	The ptr recursively calls on all of its branches and
    *	finally we start deleting the branch.
    *
    */
    void recDel(DictNode *ptr);

    /*
    *   This method recursively finds all the suggestions
    *   that can be formed by the "pre" string given
    *   It takes in a string "pre" marking the string over which it has looped
    *   and the pointer on whose branches it should call recursively.
    *   and toReturn is the pointer to the vector to which we need to add the completed words.
    */
    void recSuggest(string pre, DictNode *ptr, vector<string> *toReturn);

    /*
    *   This method is an overloaded version of the one given above.
    *   It takes in an extra int as a paramter to only suggest words having the given length
    */
    void recSuggest(string pre, DictNode *ptr, vector<string> *toReturn, int len, bool includeQuotes = false);

    /*
    *   This method recursively find all the words that will
    *   contain all the alphabets in the word passed in as a parameter, and
    *   add it to the toReturn vector pointer also passed in as a pointer.
    */
    void recGuess(string word, vector<string> *toReturn);

public:
    /*
    *	The only constructor of the the class "Dict".
    *	It takes in a string to the location of the library to use.
    *	It adds individual word to the data structure as a tree.
    */
    Dict(string dictionary);

    /*
    *	Destructor of the class "Dict" returns all the allocated memory back to the system.
    */
    ~Dict(void);

    /*
    *   Returns a bool the state of the dictionary if it is loaded or not.
    */
    bool isLoaded(void);

    /*
    *	This method returns a boolean
    *	checking whether the word exists in the dictionary
    */
    bool checkWord(string word);

    /*
    *   This method takes in a sequence of words and then it
    *   predicts all the words that can be formed starting
    *   from that combination.
    *   like point can return the following
    *   pointer, pointless, pointy etc
    *
    *   The method returns a vector of all possibilities.
    */
    vector<string> *suggestWords(string pre);

    /*
    *   This method is an overloaded version of the one given above.
    *   It takes in an extra int as a paramter to only suggest words having the given length
    */
    vector<string> *suggestWords(string pre, int len, bool includeQuotes = false);

    /*
    * Guess word function takes in a word and
    *   return a vector of strings containing all the words
    *   that may contain all the alphabets in the given word
    */
    vector<string> *guessWords(string word);


    /*
    *   It is an template based implementation of the Quick Sort Algorithm.
    */
    template <class T> static void quickSort(T *arr, int l, int r){
        T temp;
        int n = r - l + 1; // the size of the array

        if (n <= 1) { // base condition
            return;
        }
        int P_index = rand() % n + l; // the pivot index in the array
        T P = arr[P_index]; // the pivot element

        //swapping pivot to the start of the current array
        temp = arr[l];
        arr[l] = arr[P_index];
        arr[P_index] = temp;

        //now partitioning the array around i with respect to the pivot
        int i = l + 1;
        for (int j = l + 1; j <= r; j++){
            if (arr[j] < P) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
            }
        }

        //finally swaping back the pivot
        temp = arr[l];
        arr[l] = arr[i - 1];
        arr[i - 1] = temp;

        //now pivot is at i-1 location

        // recursively calling the function of the two remaining parts of the unsorted array
        quickSort(arr, l, i - 2);
        quickSort(arr, i, r);
    }
};

#endif
