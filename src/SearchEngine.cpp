#include "SearchEngine.h"
#include <iostream>
using namespace std;

SearchEngine::SearchEngine() : nextDocID(1) {}

void SearchEngine::addDocument(const string& title, const string& content) {
    Document* doc = new Document(nextDocID++, title, content);
    documents.addNode(doc);
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


