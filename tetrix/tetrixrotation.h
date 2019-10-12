#ifndef TETRIXROTATION_H
#define TETRIXROTATION_H

#include "vector"

class TetrixRotation
{
public:
    TetrixRotation(std::vector<std::vector<int>> _piece, int _len, int _height) : piece(_piece), len(_len), height(_height) {}
    std::vector<std::vector<int>> piece;
    int len;
    int height;
};

#endif // TETRIXROTATION_H
