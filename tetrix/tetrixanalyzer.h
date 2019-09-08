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
    TetrixShape *originalBoard;
    int countLinesCompleted();
    bool tryMove(const TetrixPiece &piece, int curX, int curY, int newX, int newY);
    void dropDown(TetrixPiece curPiece, int curX, int curY);
};

#endif // TETRIXANALYZER_H
