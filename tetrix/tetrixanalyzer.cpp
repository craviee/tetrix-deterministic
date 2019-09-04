#include "tetrixanalyzer.h"

TetrixAnalyzer::TetrixAnalyzer(int width, int height)
{
    BoardWidth = width;
    BoardHeight = height;
}

void TetrixAnalyzer::setPiece(TetrixPiece *piece)
{
    currentPiece = piece;
}

void TetrixAnalyzer::setBoard(TetrixShape *board)
{
    currentBoard = board;
}

bool TetrixAnalyzer::tryMove(const TetrixPiece &piece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + piece.x(i);
        int y = newY - piece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (currentBoard[(x * BoardWidth) + y] != NoShape)
            return false;
    }
    return true;
}

void TetrixAnalyzer::dropDown()
{
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
    }
    pieceDropped();
//! [19] //! [20]
}

std::vector<TetrixMoviment> TetrixAnalyzer::getMoviments()
{
    int curX, curY;
    std::vector<TetrixMoviment> result;
    TetrixPiece rotatedPiece;
    result.push_back(TetrixMoviment::LEFT);
    for(int i = 1; i <= 4; i++)
    {
        rotatedPiece = currentPiece->rotatedLeft(i);
        for(int j = 0; j < BoardWidth; j++ )
        {
            curX = j;
            curY = BoardHeight - 1 + rotatedPiece.minY();
        }
    }
    return result;
}
