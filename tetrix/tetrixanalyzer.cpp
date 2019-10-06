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
    
    for(int i = 0; i < BoardHeight; i++)
    {
        
        for(int j = 0; j < BoardWidth; j++)
            currentBoard[i][j] = originalBoard[(i*BoardWidth) +j] == TetrixShape::NoShape ? 0 : 1;

    }

    // for(int i=0; i< BoardHeight; i++)
    // {
    //     for(int j=0; j < BoardWidth; j++)
    //     {
    //         printf("%d",currentBoard[i][j]);
    //     }
    //     printf("\n");
    // }
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
                {1,1,1,0},
                {1,0,0,0},
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
                {0,0,1,0},
                {1,1,1,0},
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

std::vector<TetrixMoviment> TetrixAnalyzer::getMoviments()
{
    std::vector<TetrixMoviment> result;
    result.push_back(TetrixMoviment::LEFT);
    int piece_len;

    for(auto piece : rotationList())
    {
        piece_len=0;
        for(int i=3; i >=0; i--)
        {
            for(int j=0; j < 4; j++)
            {
                if(piece[j][i])
                {
                    piece_len = i;
                    goto found;
                }
            }
        }
        found:;
        for(int position=0; position < (BoardWidth - piece_len); position++)
        {
            clearBoard();
            for(int i=0; i < 4; i++)
            {
                for(int j=0; j <= piece_len; j++)
                {
                    // printf("BoardWidth: %d\n", BoardWidth);
                    // printf("j: %d\n", j);
                    // printf("position: %d\n", position);
                    // printf("position + j: %d\n", position + j);
                    // printf("piece_len: %d\n\n", piece_len);
                    currentBoard[i][j + position] = piece[i][j];
                }
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
    return result;
}
