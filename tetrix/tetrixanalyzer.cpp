#include "tetrixanalyzer.h"
#include <cstdio>
#include <array>

TetrixAnalyzer::TetrixAnalyzer(int width, int height)
{
    BoardWidth = width;
    BoardHeight = height;
}

void TetrixAnalyzer::setPiece(TetrixPiece *piece)
{
    currentPiece = piece;
}

std::vector<std::vector<int>>  TetrixAnalyzer::getClearBoard()
{
    std::vector<std::vector<int>> clearBoard;
    clearBoard.resize(BoardHeight, std::vector<int>(BoardWidth));

    for(int i = 0, k = BoardHeight-1; i < BoardHeight; i++,k--)
    {
        for(int j = 0; j < BoardWidth; j++)
        {
            clearBoard[k][j] = reversedBoard[(i*BoardWidth) +j] == TetrixShape::NoShape ? 0 : 1;
        }
    }
    return clearBoard;
}

void TetrixAnalyzer::setBoard(TetrixShape *board)
{
    reversedBoard.resize(BoardHeight*BoardWidth);
    for(int i=0; i< BoardHeight; i++)
    {
        for(int j=0; j < BoardWidth; j++)
        {
            reversedBoard[i*BoardWidth + j] = board[i*BoardWidth + j];
        }  
    }
}

std::vector<TetrixRotation> TetrixAnalyzer::rotationList()
{
    std::vector<TetrixRotation> rotations;

    switch (currentPiece->shape())
    {
        case TetrixShape::SquareShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,0,0},
                    {1,1,0,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    2, 2
                )
            );
            break;
            
        case TetrixShape::ZShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,1,0,0},
                    {1,1,0,0},
                    {1,0,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,0,0},
                    {0,1,1,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            break;

        case TetrixShape::SShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,0,0,0},
                    {1,1,0,0},
                    {0,1,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,1,1,0},
                    {1,1,0,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            break;

        case TetrixShape::LineShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,0,0,0}},
                    1, 4
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,1,1},
                    {0,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    4, 1
                )
            );
            break;

        case TetrixShape::TShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,1,0},
                    {0,1,0,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,1,0,0},
                    {1,1,0,0},
                    {0,1,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,1,0,0},
                    {1,1,1,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,0,0,0},
                    {1,1,0,0},
                    {1,0,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            break;

        case TetrixShape::LShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,0,0},
                    {0,1,0,0},
                    {0,1,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,0,1,0},
                    {1,1,1,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,0,0,0},
                    {1,0,0,0},
                    {1,1,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,1,0},
                    {1,0,0,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            break;

        case TetrixShape::MirroredLShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,0,0},
                    {1,0,0,0},
                    {1,0,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,1,0},
                    {0,0,1,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {0,1,0,0},
                    {0,1,0,0},
                    {1,1,0,0},
                    {0,0,0,0}},
                    2, 3
                )
            );
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,0,0,0},
                    {1,1,1,0},
                    {0,0,0,0},
                    {0,0,0,0}},
                    3, 2
                )
            );
            break;

        case TetrixShape::NoShape:
            rotations.push_back
            (
                TetrixRotation
                ({
                    {1,1,1,1},
                    {1,1,1,1},
                    {1,1,1,1},
                    {1,1,1,1}},
                    4, 4
                )
            );
            break;
    }
    return rotations;
}

int TetrixAnalyzer::calculateCompleteLines(std::vector<std::vector<int>> currentBoard)
{
    int completedLines = 0;
    int sumLine;
    for(int i=BoardHeight-1; i >= 0; i--)
    {
        sumLine = 0;
        for(int j=0; j < BoardWidth; j++)
        {
            sumLine += currentBoard[i][j] ? 1 : 0;
        }
        if(!sumLine)
        {
            return completedLines;
        }
        else if(sumLine == BoardWidth)
        {
            completedLines++;
        }
    }
    return -1;
}

int TetrixAnalyzer::calculateHoles(std::vector<std::vector<int>> currentBoard)
{
    int holes = 0;
    bool foundPiece;
    bool endPiece;
    for(int j=0; j < BoardWidth; j++)
    {
        foundPiece = false;
        endPiece = false;
        for(int i=0; i < BoardHeight; i++)
        {
            if(foundPiece && currentBoard[i][j] && endPiece)
            {
                break;
            }
            else if(foundPiece && !currentBoard[i][j])
            {
                holes++;
                endPiece = true;
            }
            else if(currentBoard[i][j] == 2)
            {
                foundPiece = true;
            }
        }
    }
    return holes;
}

std::vector<TetrixMoviment> TetrixAnalyzer::getMoviments()
{
    std::vector<TetrixMoviment> result;
    double currentBest = -(BoardHeight*BoardWidth);
    auto rotations = rotationList();
    
    for(int index = 0; index < rotations.size(); index++)
    {
        auto piece = rotations[index];

        for(int position=0; position <= (BoardWidth - piece.len); position++)
        {
            auto currentBoard = getClearBoard();
            int linesDown = 0;

            for(int i=0; i < piece.height; i++)
            {
                for(int j=0; j < piece.len; j++)
                {
                    currentBoard[i][j + position] = piece.piece[i][j];
                }
            }

            linesDown=BoardHeight-piece.height;
            for(int j=0; j < piece.len; j++)
            {
                for(int i=piece.height-1; i >= 0; i--)
                {
                    if(currentBoard[i][j + position])
                    {
                        for(int k=piece.height; k < BoardHeight; k++)
                        {
                            if(currentBoard[k][j + position] && (k-i-1 < linesDown))
                            {
                                linesDown = k - i -1;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            for(int j=0; j < piece.len; j++)
            {
                for(int i=piece.height-1; i >= 0; i--)
                {
                    if(currentBoard[i][j + position])
                    {
                        currentBoard[i+linesDown][j + position] = 2;
                        currentBoard[i][j + position] = 0;
                    }
                }
            }

            int lines = calculateCompleteLines(currentBoard);
            int holes = calculateHoles(currentBoard);
            double height = (double)linesDown/10;

            if(evaluateChoice(lines,holes,height) > currentBest)
            {
                result.clear();
                if(index == 3)
                {
                    result.push_back(TetrixMoviment::ROTATE_LEFT);
                }
                else
                {
                    for(int i = 0; i < index; i++)
                    {
                        result.push_back(TetrixMoviment::ROTATE_RIGHT);
                    }
                }
                
                for(int i= 0; i < BoardWidth; i++)
                {
                    result.push_back(TetrixMoviment::LEFT);
                }
                for(int i=0; i < position; i++)
                {
                    result.push_back(TetrixMoviment::RIGHT);
                }

                currentBest = evaluateChoice(lines,holes,height);
            }
        }
    }

    return result;
}
