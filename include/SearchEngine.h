#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include "Document.h"
#include "DataStructures/LinkedList.h"
#include "Index.h"

using namespace std;

class SearchEngine {
private:
    LinkedList documents;
    Index index;
    int nextDocID;

public:
    SearchEngine();
    void addDocument(const string& title, const string& content);
    void removeDocument(int id);
    Document* findDocumentById(int id);
    void updateDocument(int id, const string& newContent);
    void displayAllDocuments();
    void search(const string& keyword);
    LinkedList tokenizeQuery(const string& query);
    LinkedList intersect(LinkedList& a, LinkedList& b);
    void searchMultiple(const string& query);
    void displayDocuments(LinkedList& ids);
};

#endif