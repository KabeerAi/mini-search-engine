#ifndef SEARCHSTAT_H
#define SEARCHSTAT_H

#include <string>

class SearchStat {
public:
    std::string word;
    int count;

    SearchStat(const std::string& w) : word(w), count(1) {}
};

#endif
