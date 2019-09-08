#include "tetrixanalyzer.h"
#include <cstdio>
#include <array>

TetrixAnalyzer::TetrixAnalyzer(int width, int height)
{
    BoardWidth = width;
    BoardHeight = height;
    currentBoard = new TetrixShape[width * height];
}

void TetrixAnalyzer::setPiece(TetrixPiece *piece)
{
    currentPiece = piece;
}

void TetrixAnalyzer::setBoard(TetrixShape *board)
{
    
    originalBoard = board;
    for(int i = 0; i < (BoardWidth * BoardHeight); i++)
        currentBoard[i] = originalBoard[i];
    
}

bool TetrixAnalyzer::tryMove(const TetrixPiece &piece, int curX, int curY, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + piece.x(i);
        int y = newY - piece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (currentBoard[(y * BoardWidth) + x] != NoShape)
            return false;
    }
    curX = newX;
    curY = newY;
    return true;
}

void TetrixAnalyzer::dropDown(TetrixPiece curPiece, int curX, int curY)
{
    int newY = curY;
    while (newY > 0) {
        if (!tryMove(curPiece,curX, curY, curX, newY - 1))
            break;
        --newY;
    }
    for (int i = 0; i < 4; ++i) {
        int x = curX + curPiece.x(i);
        int y = curY - curPiece.y(i);
        currentBoard[(y * BoardWidth) + x] = curPiece.shape();
    }


    printf("new dropdown\n");
    for(int i = 0; i < BoardHeight; i++)
    {
        for(int j = 0; j < BoardWidth; j++)
        {
            if(currentBoard[(i * BoardWidth) + j] == NoShape)
                printf("0 ");
            else
                printf("1 ");
        }
        printf("\n");
    }
        

//! [19] //! [20]
}

int TetrixAnalyzer::countLinesCompleted()
{
    int numFullLines=0;

    for (int i = BoardHeight - 1; i >= 0; --i) {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j) {
            if (currentBoard[(i * BoardWidth) + j] == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
//! [24] //! [25]
            ++numFullLines;
        }
//! [26] //! [27]
    }
    return numFullLines;
}

std::vector<TetrixMoviment> TetrixAnalyzer::getMoviments()
{
    int curX, curY;
    int curLinesCompleted;
    int t = -1;
    int q;
    
    std::vector<TetrixMoviment> result;
    TetrixPiece rotatedPiece;
    result.push_back(TetrixMoviment::LEFT);
    for(int i = 1; i <= 4; i++)
    {
        for(int j = 0; j < BoardWidth; j++ )
        {
            rotatedPiece = currentPiece->rotatedLeft(i);
            curX = j;
            curY = BoardHeight - 1 + rotatedPiece.minY();
            // printf("i=%d j=%d curY=%d\n", i,j,curY);
            dropDown(rotatedPiece, curX, curY);
            curLinesCompleted = countLinesCompleted();
            if(t < curLinesCompleted)
                t = curLinesCompleted;
            q=0;
            for(int k = 0; k < (BoardWidth * BoardHeight); k++)
            {
                currentBoard[k] = originalBoard[k];
                if(originalBoard[k] != NoShape)
                    q++;
            }
            // printf("number of pieces: %d\n", q);     
        }
    }
    printf("best value: %d\n", t);
    return result;
}
