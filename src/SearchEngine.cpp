#include "SearchEngine.h"
#include <iostream>
using namespace std;

SearchEngine::SearchEngine() : nextDocID(1) {}

void SearchEngine::addDocument(const string& title, const string& content) {
    Document* doc = new Document(nextDocID, title, content);
    documents.addNode(doc);
    index.addDocument(nextDocID, content);
    nextDocID++;

    cout << "Document added successfully!" << endl;
}

Document* SearchEngine::findDocumentById(int id) {
    Node* current = documents.head;
    while (current != nullptr) {
        Document* doc = (Document*) current->data;
        if (doc->id == id) {
            return doc;
        }
        current = current->next;
    }
    return nullptr;
}

void SearchEngine::removeDocument(int id) {
    Document* doc = findDocumentById(id);
    if (!doc) {
        cout << "Document not found.\n";
        return;
    }
    documents.removeNode(doc); // uses your function
    delete doc;                // free memory
}


void SearchEngine::updateDocument(int id, const string& newContent) {
    Document* doc = findDocumentById(id);
    if (!doc) {
        cout << "Document not found.\n";
        return;
    }
    doc->content = newContent;
    doc->updated_at = time(nullptr);
    doc->accessCount++;
    cout << "Document updated successfully!" << endl;
}

void SearchEngine::displayAllDocuments() {
    Node* current = documents.head;
    while (current != nullptr) {
        Document* doc = (Document*)current->data;
        cout << "ID: " << doc->id << "\n";
        cout << "Title: " << doc->title << "\n";
        cout << "Content: " << doc->content << "\n";
        cout << "Access Count: " << doc->accessCount << "\n";
        cout << "-----------------------\n";
        current = current->next;
    }
}

void SearchEngine::search(const string& keyword) {

    // normalize keyword (lowercase)
    string word = "";
    for (char c : keyword) {
        if (isalpha(c)) word += tolower(c);
    }

    LinkedList results = index.searchWord(word);

    if (results.size == 0) {
        cout << "No documents found.\n";
        return;
    }

    Node* cur = results.head;
    while (cur) {
        int* docId = (int*) cur->data;
        Document* doc = findDocumentById(*docId);

        if (doc) {
            doc->accessCount++; // for ranking later
            cout << "ID: " << doc->id << "\n";
            cout << "Title: " << doc->title << "\n";
            cout << "Content: " << doc->content << "\n";
            cout << "---------------------\n";
        }
        cur = cur->next;
    }
}

void SearchEngine::displayDocuments(LinkedList& ids) {
    Node* cur = ids.head;

    while (cur) {
        int* id = (int*) cur->data;
        Document* doc = findDocumentById(*id);

        if (doc) {
            doc->accessCount++;
            cout << "ID: " << doc->id << "\n";
            cout << "Title: " << doc->title << "\n";
            cout << doc->content << "\n";
            cout << "-----------------\n";
        }
        cur = cur->next;
    }
}


LinkedList SearchEngine::tokenizeQuery(const std::string& query) {
    LinkedList tokens;
    string word = "";
    for (char c : query) {
        if (isalpha(c)) {
            word += tolower(c);
        }
        else {
            if (!word.empty()) {
                tokens.addNode(new string(word));
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tokens.addNode(new string(word));
    }

    return tokens;
}

LinkedList SearchEngine::intersect(LinkedList& a, LinkedList& b) {
    LinkedList result;

    Node* curA = a.head;
    while (curA) {
        int* idA = (int*) curA->data;

        Node* curB = b.head;
        while (curB) {
            int* idB = (int*) curB->data;

            if (*idA == *idB) {
                result.addNode(new int(*idA));
                break;
            }
            curB = curB->next;
        }
        curA = curA->next;
    }

    return result;
}


void SearchEngine::searchMultiple(const string& query) {

    LinkedList words = tokenizeQuery(query);

    if (words.size == 0) return;

    // Get first word result as base
    Node* wcur = words.head;
    string* firstWord = (string*) wcur->data;

    LinkedList result = index.searchWord(*firstWord);

    if (result.size == 0) {
        cout << "No documents found.\n";
        return;
    }

    wcur = wcur->next;

    // Intersect with remaining words
    while (wcur) {
        string* word = (string*) wcur->data;
        LinkedList nextList = index.searchWord(*word);

        result = intersect(result, nextList);

        if (result.size == 0) break;

        wcur = wcur->next;
    }

    displayDocuments(result);
}

