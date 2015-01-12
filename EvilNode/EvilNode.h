#ifndef EVIL_NODE_H
#define EVIL_NODE_H

#include <iostream>

using namespace std;

#ifndef ALPHABETS
#define ALPHABETS 27
#endif

class EvilNode {
    /*
    * counts number of elemnents in a bucket of our hash table
    */
    int count;

    /*
    * To check which buckets exist
    */
    bool flag;

    /*
    *	data for the hashtable
    */
    string item;
public:
    /*
    *   Next pointer used in our hashtable datastructure
    */
    EvilNode *next;

    /*
    *	The default constructor of the class Evil_Node.
    *	It also sets each of 'next' pointer to NULL.
    *   Sets the 'flag' to false, also sets the 'count' to 0
    */
    EvilNode(void);

    /*
    *   This method returns the value of 'count'
    */
    int getCount();

    /*
    *   This method increments the 'count' variable by 1
    */
    void incrementCount(void);

    /*
    *   This method returns the value of 'flag'
    */
    bool getFlag();

    /*
    *   This method sets the value of 'flag'
    */
    void setFlag(bool flag);

    /*
    *   This method returns the value of variable 'item'
    */
    string getItem();

    /*
    *   This method sets the value of variable 'item'
    */
    void setItem(string item);
};


#endif // EVIL_NODE_H
