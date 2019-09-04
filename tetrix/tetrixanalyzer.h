#ifndef TETRIXANALYZER_H
#define TETRIXANALYZER_H

#include "tetrixmoviment.h"
#include "tetrixpiece.h"
#include "vector"

class TetrixAnalyzer
{
public:
    TetrixAnalyzer(int width, int height);
    void setPiece(TetrixPiece *piece);
    void setBoard(TetrixShape *board);
    std::vector<TetrixMoviment> getMoviments();

private:
    int BoardWidth;
    int BoardHeight;
    TetrixPiece *currentPiece;
    TetrixShape *currentBoard;
    bool tryMove(const TetrixPiece &piece, int newX, int newY);
};

#endif // TETRIXANALYZER_H
