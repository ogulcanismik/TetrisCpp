#pragma once

//#include "CustomVector.h"
#include "PieceList.h"

#include <vector>
#include <random>
#include <iomanip>
#include <iostream>
#include <windows.h>

class Board{
    public:
    Board();
    Board(int X, int Y);
    bool rotation_limit_reached=0;
    int size_x, size_y;
    int held_piece;
    int combo_lines_cleared=1;
    void Draw(Board& board, unsigned int& score);
    void Preview(unsigned short int& piece_id, Board& board);
    int HoldPiece(unsigned short int& piece_id, Board& board);
    void DrawGameOver(HANDLE& consoleHandle, COORD& cur);
    int ClearLine(Board &board);
    bool CheckGameOver(Board& board, int line);
    struct position
    {
        int pos_id;
        bool state;
    };
    std::vector<position> positions;
    std::vector<position> preview;
    std::vector<position> hold;

    private:
    bool CheckLine(Board& board, int line);

};