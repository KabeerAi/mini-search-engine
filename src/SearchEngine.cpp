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

void SearchEngine::displayRankedDocuments(LinkedList& ranked) {
    Node* cur = ranked.head;

    while (cur) {
        RankNode* r = (RankNode*) cur->data;
        Document* doc = findDocumentById(r->docId);

        if (doc) {
            std::cout << "Score: " << r->score << "\n";
            std::cout << "ID: " << doc->id << "\n";
            std::cout << "Title: " << doc->title << "\n";
            std::cout << doc->content << "\n";
            std::cout << "-----------------\n";
        }
        cur = cur->next;
    }
}

bool SearchEngine::alreadyRanked(LinkedList& list, int docId) {
    Node* cur = list.head;
    while (cur) {
        RankNode* r = (RankNode*) cur->data;
        if (r->docId == docId) {
            return true;
        }
        cur = cur->next;
    }
    return false;
}

void SearchEngine::updateSearchStats(LinkedList& words) {
    Node* wcur = words.head;

    while (wcur) {
        string* w = (string*) wcur->data;

        Node* scur = searchStats.head;
        bool found = false;

        while (scur) {
            SearchStat* stat = (SearchStat*) scur->data;
            if (stat->word == *w) {
                stat->count++;
                found = true;
                break;
            }
            scur = scur->next;
        }

        if (!found) {
            searchStats.addNode(new SearchStat(*w));
        }

        wcur = wcur->next;
    }
}

void SearchEngine::displaySearchStats() {
    Node* cur = searchStats.head;

    std::cout << "\n--- Search Analytics ---\n";
    while (cur) {
        SearchStat* stat = (SearchStat*) cur->data;
        std::cout << stat->word << " -> " << stat->count << "\n";
        cur = cur->next;
    }
}



void SearchEngine::searchMultiple(const string& query) {

    LinkedList words = tokenizeQuery(query);
    updateSearchStats(words);

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

    LinkedList rankedResults;

    Node* cur = result.head;
    while (cur) {
        int* id = (int*) cur->data;
        Document* doc = findDocumentById(*id);

        if (doc) {
            int score = countWordFrequency(doc->content, words);
            if (!alreadyRanked(rankedResults, *id)) {
                rankedResults.addNode(new RankNode(*id, score));
            }
        }
        cur = cur->next;
    }

    sortByScore(rankedResults);
    displayRankedDocuments(rankedResults);

}


int SearchEngine::countWordFrequency(const string& content, LinkedList& queryWords) {
    int score = 0;
    string word = "";

    for (char c : content) {
        if (isalpha(c)) {
            word += tolower(c);
        } else {
            if (!word.empty()) {
                Node* qcur = queryWords.head;
                while (qcur) {
                    string* q = (string*) qcur->data;
                    if (word == *q) {
                        score++;
                    }
                    qcur = qcur->next;
                }
                word.clear();
            }
        }
    }

    // last word
    if (!word.empty()) {
        Node* qcur = queryWords.head;
        while (qcur) {
            string* q = (string*) qcur->data;
            if (word == *q) {
                score++;
            }
            qcur = qcur->next;
        }
    }

    return score;
}

void SearchEngine::sortByScore(LinkedList& list) {
    if (list.size < 2) return;

    bool swapped;
    do {
        swapped = false;
        Node* cur = list.head;

        while (cur && cur->next) {
            RankNode* a = (RankNode*) cur->data;
            RankNode* b = (RankNode*) cur->next->data;

            if (a->score < b->score) {
                void* temp = cur->data;
                cur->data = cur->next->data;
                cur->next->data = temp;
                swapped = true;
            }
            cur = cur->next;
        }
    } while (swapped);
}

