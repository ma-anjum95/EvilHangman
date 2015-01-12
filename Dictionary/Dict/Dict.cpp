#include "Dict.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <ctime>

//#include "../DictNode/DictNode.h"

Dict::Dict(string dictionary) {
    this->root = new DictNode;
    this->size = 0;

    this->alphaOccur = new vector<int>[ALPHABETS];
    this->wordArray = new vector<string>;

    // loading the dictionary in the memory
    this->loaded = this->loadDict(dictionary);
}

Dict::~Dict(void) {
    // calling the recursive function to delete all the dynamically allocated memory
    this->recDel(this->root);
}

bool Dict::loadDict(string dictionary) {
    ifstream in;
    in.open(dictionary, ios::in);
    string word;

    if (!in.is_open()) {
        return false;
    }

    while (!in.eof()) {
        in >> word;

        this->addWord(word);
        this->wordArray->push_back(word);
        this->addToOccur(word, this->size);
        this->size++;
    }

    in.close();
    return true;
}

bool Dict::isLoaded(void) {
    return this->loaded;
}

void Dict::addWord(string word) {
    DictNode *ptr = this->root;

    for (size_t i = 0, n = word.length(); i < n; i++) {
        int alphaLoc = this->alphaLoc(word[i]);

        if (!ptr->branch[alphaLoc]) {
            ptr->branch[alphaLoc] = new DictNode;
        }
        ptr = ptr->branch[alphaLoc];
    }

    // now setting the "is_word" boolean of the current pointer to true
    ptr->makeWord();
}

void Dict::addToOccur(string word, int index) {
    bool doesHave[ALPHABETS] = { false };

    for (int i = 0, n = word.length(); i < n; i++) {
        int j = this->alphaLoc(word[i]);
        if (!doesHave[j]) {
            // if the word has not been previously added
            this->alphaOccur[j].push_back(index);
            doesHave[j] = true;
        }
    }
}

bool Dict::checkWord(string word) {
    DictNode *ptr = this->root;

    // fixing the given word
    this->fixWord(word);

    for (size_t i = 0, n = word.length(); i < n; i++) {
        int alphaLoc = this->alphaLoc(word[i]);

        if (!ptr) { // if the current ptr is NULL that means we are on the wrong path
            return false;
        }
        ptr = ptr->branch[alphaLoc];
    }

    if (ptr && ptr->isWord()) { // if the current ptr is not NULL and the node is a word
        return true;
    }
    return false;
}

vector<string> *Dict::suggestWords(string pre) {
    DictNode *ptr = this->root;
    vector<string> *toReturn = new vector<string>; // the vector we will be returning

    // fixing the given word
    this->fixWord(pre);

    // first we loop over the datastructure over the string "pre"
    for (int i = 0, n = pre.length(); i < n; i++) {
        if (!ptr) {
            return NULL;
        }
        int alphaLoc = this->alphaLoc(pre[i]);
        ptr = ptr->branch[alphaLoc];
    }
    if (!ptr) {
        return NULL;
    }
    this->recSuggest(pre, ptr, toReturn);

    return toReturn;
}

vector<string> *Dict::suggestWords(string pre, int len, bool includeQuotes) {
    DictNode *ptr = this->root;
    vector<string> *toReturn = new vector<string>; // the vector we will be returning

    // fixing the given word
    this->fixWord(pre);

    // first we loop over the datastructure over the string "pre"
    int n = pre.length();
    for (int i = 0; i < n; i++) {
        if (!ptr) {
            return NULL;
        }
        int alphaLoc = this->alphaLoc(pre[i]);
        ptr = ptr->branch[alphaLoc];
    }
    if (!ptr) {
        return NULL;
    }
    this->recSuggest(pre, ptr, toReturn, len - n, includeQuotes);

    return toReturn;
}

vector<string> *Dict::guessWords(string word){
    vector<string> *toReturn = new vector<string>;

    // fixing the given word
    this->fixWord(word);

    this->recGuess(word, toReturn);

    return toReturn;
}

int Dict::alphaLoc(char ch) {
    if (ch == '\'') {
        return 26;
    }
    else if (isalpha(ch)){
        return tolower(ch) - 'a';
    }
    else {
        return -1;
    }
}

char Dict::intLoc(int loc) {
    if (loc == 26) {
        return '\'';
    }
    else {
        return 'a' + loc;
    }
}

void Dict::recDel(DictNode *ptr) {
    if (!ptr) {
        return;
    }
    else {
        for (int i = 0; i < ALPHABETS; i++)
            this->recDel(ptr->branch[i]);
        delete ptr;
    }
}

void Dict::fixWord(string &word) {
    string temp;

    for (int i = 0, n = word.length(); i < n; i++) {
        if (isalpha(word[i])) {
            temp += word[i];
        }
    }
    word = temp; // overriding the original word
}

void Dict::recSuggest(string pre, DictNode *ptr, vector<string> *toReturn){
    if (!ptr) {
        return;
    }
    if (ptr->isWord()) { // if pre is word
        toReturn->push_back(pre);
    }
    // loops over all the branches
    for (int i = 0; i < ALPHABETS; i++) {
        this->recSuggest(pre + this->intLoc(i), ptr->branch[i], toReturn);
    }
}

void Dict::recSuggest(string pre, DictNode *ptr, vector<string> *toReturn, int len, bool includeQuotes) {
    if (!ptr || len < 0) {
        return;
    }
    if (ptr->isWord() && len == 0) {
        toReturn->push_back(pre);
    }
    // loops over all the branches
    if (!includeQuotes) { // if i dont want to include the quotations like in the evil hangman game
        for (int i = 0; i < ALPHABETS - 1; i++) {
            this->recSuggest(pre + this->intLoc(i), ptr->branch[i], toReturn, len - 1);
        }
    } else {
        for (int i = 0; i < ALPHABETS; i++) {
            this->recSuggest(pre + this->intLoc(i), ptr->branch[i], toReturn, len - 1);
        }
    }
}

void Dict::recGuess(string word, vector<string> *toReturn) {
    // the main array which will have all the occurences of the alphabets in the word
    vector<int> *mainArray = new vector<int>;

    int n = word.length();

    // combining all the vectors having the alphabets in the words
    for (int i = 0; i < n; i++) {
        int loc = this->alphaLoc(word[i]);
        for (int j = 0, k = this->alphaOccur[loc].size(); j < k; j++){
            mainArray->push_back(this->alphaOccur[loc][j]);
        }
    }

    int *occurArray = mainArray->data();
    int m = mainArray->size();

    Dict::quickSort<int>(occurArray, 0, m - 1);

    int count = 0;
    for (int i = 1; i < m; i++) {
        if (occurArray[i - 1] == occurArray[i]) {
            count++;
        }
        else {
            count = 0;
        }

        if (count == n - 1) {
            string toEnter = this->wordArray[0][occurArray[i]];
            toReturn->push_back(toEnter);
        }
    }
}


