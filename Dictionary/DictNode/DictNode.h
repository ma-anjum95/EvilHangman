#ifndef DICTNODE_H
#define DICTNODE_H

#include <iostream>

using namespace std;

#ifndef ALPHABETS
#define ALPHABETS 27
#endif

class DictNode {
    /*
    *	The boolean which tells us if the node we are looking at
    *	marks the ending of a word or not.
    *	It is initially set to false by default constructor.
    */
    bool is_word;

public:
    /*
    *	The main component of our data structure and forms a tree of
    *	pointer of objects of same class.
    *	Each of the pointer points to individual alphabets of the word.
    *	The pointers from 0 - 25 point to alphabets a - z whereas, the last 26 index is for the " ' " character.
    */
    DictNode *branch[ALPHABETS];

    /*
    *	The default constructor of the class Node.
    *	Takes no Parameters.
    *	It sets the "is_word" boolean to false indicating that the node
    *	just created is not an ending of a word.
    *	It also sets each of branch pointer to NULL.
    */
    DictNode(void);

    /*
    *	This is a method which returns the current boolean state of "is_word"
    *	If we are traversing the data structure and the word we are checking
    * 	ends on this node, we can check if it is a word.
    */
    bool isWord(void);

    /*
    *	This method is called when we want to convert our node into an
    *	ending for a word.
    *	It only sets the "is_word" boolean to true indicating completion of a word.
    */
    void makeWord(void);
};

#endif
