#include "include/SearchEngine.h"

int main() {
    SearchEngine engine;

    engine.addDocument("AI", "AI is the future");
    engine.addDocument("Search", "Search engines use indexing");

    engine.displayAllDocuments();

    engine.updateDocument(1, "AI will change the world");
    engine.removeDocument(2);

    engine.displayAllDocuments();

    return 0;
}
