#include "EvilHangman.h"

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>


EvilHangman::EvilHangman(Dict *dict, int letters, int guesses) {
    this->dict = dict;

    this->letters = letters;
    this->guesses = guesses;
    this->numHashTables = (int)pow(2, this->letters);
    this->arr = new EvilNode*[this->numHashTables];       //setting size to 2^letters

    for (int i = 0; i < this->numHashTables; i++) {
        this->arr[i] = NULL;
    }

    this->displayArray = new char[this->letters + 1]; // plus one for the /0
    for (int i = 0; i < this->letters; i++) {                              //iniatially setting the display array to print dashes
        this->displayArray[i] = '_';
    }
    this->displayArray[this->letters] = '\0'; // marking the end of the character array

    this->wordList = this->dict->suggestWords("", this->letters);                      //a vector that collects the words of given length

    if (this->wordList->size() > 10) {
        // if the size of the word list is greater than we can play else not
        this->is_loaded = true;
    }
    else {
        this->is_loaded = false;
    }

}

EvilHangman::~EvilHangman() {
    delete this->displayArray;
    for (int i = 0; i < this->numHashTables; i++) {
        if (this->arr[i]) {
            this->recDel(this->arr[i]);
            this->arr[i] = NULL;
        }
    }
    //delete this->arr;
}

void EvilHangman::recDel(EvilNode *ptr) {
    if (!ptr) {
        return;
    }
    else {
        this->recDel(ptr->next);
        delete ptr;
    }
}

void EvilHangman::insertInHashTable(string word, char ch) {
    int hash = this->hash(word, ch);

    EvilNode *ptr = this->arr[hash];
    EvilNode *toAdd = new EvilNode;
    toAdd->setItem(word);

    if (!ptr) {
        this->arr[hash] = toAdd;
        this->arr[hash]->setFlag(true); // setting the flag to be true that this hash table has elements
    }
    else {
        while (ptr->next) {
            ptr = ptr->next;
        }
        ptr->next = toAdd;
    }
    // incrementing the count of the root hash node
    this->arr[hash]->incrementCount();
}

char *EvilHangman::returnDisplayArray() {
    return this->displayArray;
}

int EvilHangman::returnGuesses() {
    return this->guesses;
}

vector<char> EvilHangman::returnGuessed() {
    return this->guessed;
}

string EvilHangman::returnFinalWord() {
    if (this->guesses <= 0)
        return this->wordList[0][0]; // returns the first word of the word list
}

bool EvilHangman::winCheck() {
    int k = 0;
    if (this->guesses <= 0)
        return false;

    for (int i = 0; i < this->letters; i++) {
        if (this->displayArray[i] == '_')
            k++;                                                 //chcking if dashes are there or not
    }
    if (k == 0)
        return true;
    else
        return false;
}

void EvilHangman::updateDisplayArray(char ch, int hash) {
    for (int i = this->letters - 1; i >= 0; i--) { // adds the character ch into the displayArray depending upon the hash's character location
        if (hash % 2 == 1) {
            this->displayArray[i] = ch;
        }
        hash /= 2;
    }
}

void EvilHangman::createHashTable(vector<string> *words, char ch) {
    for (int i = 0, n = words->size(); i < n; i++) {
        this->insertInHashTable(words[0][i], ch);
    }
}

int EvilHangman::hash(string word, char ch) {
    int sum = 0;
    for (int i = 0, n = word.length(); i < n; i++) {
        if (word[i] == ch) { // if the character in the string is equal to the given character
            sum += pow(2, n - i - 1); // using the way binary values of characters is given
        }
    }
    return sum;
}

bool EvilHangman::checkAndUpdateWordList(char guess) {
    int max = 0;
    int index = 0;
    bool toReturn = false;
    vector<string> *newWordList = new vector<string>;

    for (int i = 0; i < this->numHashTables; i++) {
        if (this->arr[i] && this->arr[i]->getFlag() && (this->arr[i]->getCount() > max)) {// if the hash table contains elements
            max = this->arr[i]->getCount();
            index = i; // the index of the largest hashtable
        }
    }

    // copying the elements of the largest hashtable into newWordList and setting this->wordList equal to it
    EvilNode *ptr = this->arr[index];
    while (ptr) {
        newWordList->push_back(ptr->getItem());
        ptr = ptr->next;
    }
    delete this->wordList;
    this->wordList = newWordList;

    if (index == 0) {
        this->guesses--;
        toReturn = false;
    }
    else {
        toReturn = true;
    }
    // updating the display array using index as the hash
    this->updateDisplayArray(guess, index);
    return toReturn;
}

bool EvilHangman::evilInterface(char guess) {
    if (!this->is_loaded)
        return false;

    bool toReturn = false;
    if (isalpha(guess) && this->guesses > 0) { // if it is an alphabet
        guess = tolower(guess);
        this->guessed.push_back(guess);
        this->createHashTable(this->wordList, guess);
        toReturn = this->checkAndUpdateWordList(guess);

        // now that the hashtable has served its purpose we delete it
        for (int i = 0; i < this->numHashTables; i++) {
            this->recDel(this->arr[i]);
            this->arr[i] = NULL;
        }
    }
    return toReturn;
}

bool EvilHangman::isLoaded(void) {
    return this->is_loaded;
}
