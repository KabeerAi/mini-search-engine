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

/*
word = ""
text = "hello world"

ch = 'h' -> isalpha(h) -> word = "h"
ch = 'e' -> isalpha(e) -> word = "he"
ch = 'l' -> isalpha(l) -> word = "hel"
ch = 'l' -> isalpha(l) -> word = "hell"
ch = 'o' -> isalpha(o) -> word = "hello"
ch = ' ' -> isalpha( ) is false -> word is not empty -> tokens.addNode("hello") -> word = ""
ch = 'w' -> isalpha(w) -> word = "w"
ch = 'o' -> isalpha(o) -> word = "wo"
ch = 'r' -> isalpha(r) -> word = "wor"
ch = 'l' -> isalpha(l) -> word = "worl"
ch = 'd' -> isalpha(d) -> word = "world"

end of loop
word is not empty -> tokens.addNode("world")

linkedlist = ["hello", "world"]

return tokens

*/