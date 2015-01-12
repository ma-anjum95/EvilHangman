#include "DictNode.h"

#include <iostream>

using namespace std;

DictNode::DictNode(void) {
    this->is_word = false;

    // looping over all the pointers to branches and setting them to point to NULL.
    for (int i = 0; i < ALPHABETS; i++) {
        this->branch[i] = NULL;
    }
}

bool DictNode::isWord(void) {
    return this->is_word;
}

void DictNode::makeWord(void) {
    this->is_word = true;
}
