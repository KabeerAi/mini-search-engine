#ifndef INDEXNODE_H
#define INDEXNODE_H

#include "LinkedList.h"
#include <string>

class IndexNode {
public:
    std::string word;
    LinkedList documentIds;

    IndexNode(std::string w);
};

#endif