#include "Tokenizer.h"
#include <cctype>

LinkedList Tokenizer::tokenize(const std::string& text) {
    LinkedList tokens;
    std::string word = "";

    for (char ch : text) {
        if (isalpha(ch)) {
            word += tolower(ch);
        } else {
            if (!word.empty()) {
                tokens.addNode(new std::string(word));
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tokens.addNode(new std::string(word));
    }

    return tokens;
}