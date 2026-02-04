#ifndef RANKNODE_H
#define RANKNODE_H

class RankNode {
public:
    int docId;
    int score;

    RankNode(int d, int s) : docId(d), score(s) {}
};

#endif
