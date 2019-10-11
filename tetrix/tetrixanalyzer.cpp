#include "tetrixanalyzer.h"
#include <cstdio>
#include <array>

TetrixAnalyzer::TetrixAnalyzer(int width, int height)
{
    BoardWidth = width;
    BoardHeight = height;
    // currentBoard.resize(height);
    // for(auto vector : currentBoard)
    // {
    //     vector.resize(width);
    // }
}

void TetrixAnalyzer::setPiece(TetrixPiece *piece)
{
    currentPiece = piece;
}

void TetrixAnalyzer::clearBoard()
{
    
    for(int i = 0, k = BoardHeight-1; i < BoardHeight; i++,k--)
    {
        
        for(int j = 0; j < BoardWidth; j++)
            currentBoard[k][j] = originalBoard[(i*BoardWidth) +j] == TetrixShape::NoShape ? 0 : 1;

    }

}

void TetrixAnalyzer::setBoard(TetrixShape *board)
{
    originalBoard.resize(BoardHeight*BoardWidth);
    currentBoard.resize(BoardHeight);
    for(int i=0; i< BoardHeight; i++)
    {
        currentBoard[i].resize(BoardWidth);
        for(int j=0; j < BoardWidth; j++)
        {
            originalBoard[i*BoardWidth + j] = board[i*BoardWidth + j];
        }  
        
    }
    // printf("sdadasdasdasd");
    clearBoard();

    // for(int i=0; i< BoardHeight; i++)
    // {
    //     for(int j=0; j < BoardWidth; j++)
    //     {
    //         printf("%d",currentBoard[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");
}

std::vector<std::vector<std::vector<int>>> TetrixAnalyzer::rotationList()
{
    std::vector<std::vector<std::vector<int>>> rotations;
    switch (currentPiece->shape())
    {
        case TetrixShape::SquareShape:
            rotations.push_back
            ({
                {1,1,0,0},
                {1,1,0,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;
            
        case TetrixShape::ZShape:
            rotations.push_back
            ({
                {0,1,0,0},
                {1,1,0,0},
                {1,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,1,0,0},
                {0,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::SShape:
            rotations.push_back
            ({
                {1,0,0,0},
                {1,1,0,0},
                {0,1,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {0,1,1,0},
                {1,1,0,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::LineShape:
            rotations.push_back
            ({
                {1,0,0,0},
                {1,0,0,0},
                {1,0,0,0},
                {1,0,0,0}
            });
            rotations.push_back
            ({
                {1,1,1,1},
                {0,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::TShape:
            rotations.push_back
            ({
                {1,1,1,0},
                {0,1,0,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {0,1,0,0},
                {1,1,0,0},
                {0,1,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {0,1,0,0},
                {1,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,0,0,0},
                {1,1,0,0},
                {1,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::LShape:
            rotations.push_back
            ({
                {1,1,0,0},
                {0,1,0,0},
                {0,1,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {0,0,1,0},
                {1,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,0,0,0},
                {1,0,0,0},
                {1,1,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,1,1,0},
                {1,0,0,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::MirroredLShape:
            rotations.push_back
            ({
                {1,1,0,0},
                {1,0,0,0},
                {1,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,1,1,0},
                {0,0,1,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {0,1,0,0},
                {0,1,0,0},
                {1,1,0,0},
                {0,0,0,0}
            });
            rotations.push_back
            ({
                {1,0,0,0},
                {1,1,1,0},
                {0,0,0,0},
                {0,0,0,0}
            });
            break;

        case TetrixShape::NoShape:
            rotations.push_back
            ({
                {1,1,1,1},
                {1,1,1,1},
                {1,1,1,1},
                {1,1,1,1}
            });
            break;
    }
    return rotations;
}

int TetrixAnalyzer::calculateCompleteLines()
{
    int completedLines = 0;
    int sumLine;
    for(int i=BoardHeight-1; i >= 0; i--)
    {
        sumLine = 0;
        for(int j=0; j < BoardWidth; j++)
        {
            sumLine += currentBoard[i][j] ? 1 : 0;
            // sumLine += currentBoard[i][j];
        }
        if(!sumLine)
            return completedLines;
        else if(sumLine == BoardWidth)
            completedLines++;
    }
    return -1;
}

int TetrixAnalyzer::calculateHoles()
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
                break;
            else if(foundPiece && !currentBoard[i][j])
            {
                holes++;
                endPiece = true;
            }
            else if(currentBoard[i][j] == 2)
                foundPiece = true;
        }
    }
    return holes;
}

int TetrixAnalyzer::calculateRawHeight()
{
    for(int i=0; i < BoardHeight; i++)
    {
        for(int j=0; j < BoardWidth; j++)
        {
            if(currentBoard[i][j])
                return BoardHeight - i;
        }
    }
    return 0;
}

std::vector<TetrixMoviment> TetrixAnalyzer::getMoviments()
{
    std::vector<TetrixMoviment> result;
    result.push_back(TetrixMoviment::ROTATE_LEFT);
    int piece_len, piece_height, piece_down;
    double currentBest = -(BoardHeight*BoardWidth);
    auto rotations = rotationList();
    for(int index = 0; index < rotations.size(); index++)
    // for(auto piece = rotations[index]; index < rotations.size(); piece = rotations[index])
    // for(auto piece : rotationList())
    {
        auto piece = rotations[index];
        piece_len=0;
        piece_height=0;

        for(int i=3; i >=0; i--)
        {
            for(int j=0; j < 4; j++)
            {
                if(piece[j][i])
                {
                    piece_len = i;
                    goto found_len;
                }
            }
        }
        found_len:;
        for(int i=3; i >=0; i--)
        {
            for(int j=0; j < 4; j++)
            {
                if(piece[i][j])
                {
                    piece_height = i;
                    goto found_height;
                }
            }
        }
        found_height:;
        for(int position=0; position < (BoardWidth - piece_len); position++)
        {
            clearBoard();
            for(int i=0; i <= piece_height; i++)
            {
                for(int j=0; j <= piece_len; j++)
                {
                    currentBoard[i][j + position] = piece[i][j];
                }
            }
            piece_down = 0;
            for(int i=piece_height+1; i < BoardHeight; i++)
            {
                for(int j=0; j <= piece_len; j++)
                {
                    if(currentBoard[i][j + position])
                    {
                        piece_down = i;
                        goto found_down;
                    }
                }
            }
            found_down:;

            piece_down=BoardHeight-piece_height-1;
            for(int j=0; j <= piece_len; j++)
            {
                for(int i=piece_height; i >= 0; i--)
                {
                    if(currentBoard[i][j + position])
                    {
                        for(int k=piece_height+1; k < BoardHeight; k++)
                        {
                            // printf("currentBoard[k][j + position]: %d k: %d j+position: %d k-i-1: %d piece_down: %d\n",currentBoard[k][j + position],k, j+position,k-i-1, piece_down);
                            if(currentBoard[k][j + position] && (k-i-1 < piece_down))
                            {
                                // printf("entered here \n");
                                piece_down = k - i -1;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            for(int j=0; j <= piece_len; j++)
            {
                for(int i=piece_height; i >= 0; i--)
                {
                    if(currentBoard[i][j + position])
                    {
                        currentBoard[i+piece_down][j + position] = 2;
                        currentBoard[i][j + position] = 0;
                    }
                }
            }

            int lines = calculateCompleteLines();
            int holes = calculateHoles();
            double height = (double)piece_down/10;
            // int height = calculateRawHeight() - lines;

            printf("lines: %d\n", lines);
            printf("holes: %d\n", holes);
            printf("height: %lf\n", height);
            printf("piece_down: %d\n\n", piece_down);

            printf("eval: %lf\n", evaluateChoice(lines,holes,height));
            printf("currentBest: %lf\n\n", currentBest);

            if(evaluateChoice(lines,holes,height) > currentBest)
            {
                printf("better than current best!\noldValue: %lf\ncurrestBest: %lf\n",currentBest,evaluateChoice(lines,holes,height));
                result.clear();
                if(index == 3)
                {
                    result.push_back(TetrixMoviment::ROTATE_LEFT);
                    printf("ROTATE_LEFT\n");
                }
                else
                {
                    for(int i = 0; i < index; i++)
                    {
                        result.push_back(TetrixMoviment::ROTATE_RIGHT);
                        printf("ROTATE_RIGHT\n");
                    }
                }
                

                for(int i= 0; i < BoardWidth; i++)
                    result.push_back(TetrixMoviment::LEFT);
                // if(position < 6)
                // {
                //     for(int i=position; i < 6; i++)
                //     {
                //         result.push_back(TetrixMoviment::LEFT);
                //         printf("LEFT\n");
                //     }
                // }
                // else if(position > 6)
                // {
                    for(int i=0; i < position; i++)
                    {
                        result.push_back(TetrixMoviment::RIGHT);
                        printf("RIGHT\n");
                    }
                // }

                currentBest = evaluateChoice(lines,holes,height);
            }
                

            for(int i=0; i< BoardHeight; i++)
            {
                for(int j=0; j < BoardWidth; j++)
                {
                    printf("%d",currentBoard[i][j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
    printf("\n\n\nEND\n\n\n");
    // result.clear();
    return result;
}
