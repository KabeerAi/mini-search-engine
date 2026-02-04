#include "Index.h"
#include "Tokenizer.h"

using namespace std;

LinkedList Index::searchWord(const string& word) {
    Node* current = indexList.head;

    while (current) {
        IndexNode* idx = (IndexNode*) current->data;
        if (idx->word == word) {
            // Return a deep copy of the list to avoid memory issues
            LinkedList copy;
            Node* idNode = idx->documentIds.head;
            while(idNode) {
                int* id = (int*) idNode->data;
                copy.addNode(new int(*id));
                idNode = idNode->next;
            }
            return copy;
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