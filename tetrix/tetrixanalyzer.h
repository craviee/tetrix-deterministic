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
    void clearBoard();
    TetrixPiece *currentPiece;
    std::vector<std::vector<int>> currentBoard;
    std::vector<TetrixShape> originalBoard;
    std::vector<std::vector<std::vector<int>>> rotationList();
};

#endif // TETRIXANALYZER_H
