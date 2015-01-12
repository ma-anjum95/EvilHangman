#include "EvilNode.h"

EvilNode::EvilNode(void) {
    this->next = NULL;
    this->flag = false;
    this->count = 0;
}

int EvilNode::getCount() {
    return this->count;
}

void EvilNode::incrementCount(void) {
    this->count++;
}

void EvilNode::setFlag(bool flag) {
    this->flag = flag;
}

bool EvilNode::getFlag() {
    return this->flag;
}

string EvilNode::getItem() {
    return this->item;
}

void EvilNode::setItem(string item) {
    this->item = item;
}
