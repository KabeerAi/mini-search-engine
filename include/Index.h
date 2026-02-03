#ifndef INDEX_H
#define INDEX_H

#include <string>
#include "DataStructures/LinkedList.h"
#include "DataStructures/IndexNode.h"
#include "Tokenizer.h"

using namespace std;

class Index {
private:
    LinkedList indexList; // IndexNode*

public:
    void addDocument(int docId, const string& text);
    LinkedList searchWord(string const &word);
};

#endif


/*

("python", [1, 3, 5]) -> ("java", [2, 4]) -> ("ai", [1, 2, 3]) -> ("c++", [1, 4])


*/