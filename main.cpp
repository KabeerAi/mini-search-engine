#include "include/SearchEngine.h"

int main() {
    SearchEngine engine;

    engine.addDocument("Doc1", "AI is the future");
    engine.addDocument("Doc2", "Search engines use AI");
    engine.addDocument("Doc3", "AI is used in search engines");

    engine.search("future");

    return 0;
}
