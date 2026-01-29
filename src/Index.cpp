#include "Index.h"
#include "Tokenizer.h"

using namespace std;

LinkedList Index::searchWord(const string& word) {
    Node* current = indexList.head;

    while (current) {
        IndexNode* idx = (IndexNode*) current->data;
        if (idx->word == word) {
            return idx->documentIds;  // FOUND
        }
        current = current->next;
    }

    return LinkedList(); // not found
}

void Index::addDocument(int docId, const string& text) {

    // 1. Tokenize document
    LinkedList tokens = Tokenizer::tokenize(text);

    Node* tokenNode = tokens.head;
    while (tokenNode) {
        string* word = (string*) tokenNode->data;

        // 2. Search word in index
        Node* idxNode = indexList.head;
        IndexNode* found = nullptr;

        while (idxNode) {
            IndexNode* idx = (IndexNode*) idxNode->data;
            if (idx->word == *word) {
                found = idx;
                break;
            }
            idxNode = idxNode->next;
        }

        // 3. If word not found, create new entry
        if (!found) {
            found = new IndexNode(*word);
            indexList.addNode(found);
        }

        // 4. Add document ID
        found->documentIds.addNode(new int(docId));

        tokenNode = tokenNode->next;
    }
}

/*
dry run code by code:

addDocument(1, "hello world")

1. tokenize -> ["hello", "world"]

tokenNode = tokens.head
tokenNode = ["hello", "world"]

word = (string*) tokenNode->data
word = "hello"

idxNode = indexList.head
idxNode = nullptr

found = nullptr

while (idxNode)
    idxNode = nullptr
    loop doesn't run

if (!found)
    found = new IndexNode("hello")
    indexList.addNode(found)

found->documentIds.addNode(new int(1))

tokenNode = tokenNode->next
tokenNode = ["world"]

word = (string*) tokenNode->data
word = "world"

idxNode = indexList.head
idxNode = [IndexNode("hello")]

found = nullptr

while (idxNode)
    idxNode = [IndexNode("hello")]
    idx = (IndexNode*) idxNode->data
    idx = IndexNode("hello")
    if (idx->word == *word)
        if ("hello" == "world")
            false
    idxNode = idxNode->next
    idxNode = nullptr

if (!found)
    found = new IndexNode("world")
    indexList.addNode(found)

found->documentIds.addNode(new int(1))

tokenNode = tokenNode->next
tokenNode = nullptr

loop ends

return

*/