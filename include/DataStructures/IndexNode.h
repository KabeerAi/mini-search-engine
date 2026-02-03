#ifndef INDEXNODE_H
#define INDEXNODE_H

#include "LinkedList.h"
#include <string>

using namespace std;

class IndexNode {
public:
    string word;
    LinkedList documentIds;

    IndexNode(string w);
};

#endif
