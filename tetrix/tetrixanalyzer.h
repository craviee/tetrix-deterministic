#ifndef TETRIXANALYZER_H
#define TETRIXANALYZER_H

#include "tetrixmoviment.h"
#include "tetrixpiece.h"
#include "tetrixrotation.h"
#include "vector"

class TetrixAnalyzer
{
public:
    TetrixAnalyzer(int width, int height);
    void setPiece(TetrixPiece *piece);
    void setBoard(TetrixShape *board);
    std::vector<TetrixMoviment> getMoviments();

private:
    std::vector<std::vector<int>> getClearBoard();
    int calculateCompleteLines(std::vector<std::vector<int>> board);
    int calculateHoles(std::vector<std::vector<int>> board);
    double evaluateChoice(int lines, int holes, double height) { return (3*lines - 2*holes + 3*height); }
    std::vector<TetrixRotation> rotationList();

    int BoardWidth;
    int BoardHeight;
    TetrixPiece *currentPiece;
    // std::vector<std::vector<int>> currentBoard;
    std::vector<TetrixShape> reversedBoard;
    
};

#endif // TETRIXANALYZER_H
