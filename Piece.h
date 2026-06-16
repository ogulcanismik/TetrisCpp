#pragma once

#include "Board.h"
#include "PieceList.h"

#include <iostream>
#include <map>

class Piece{
public:
bool Paused=0;
int rotation_limit=3;

Piece();
Piece(int piece_id, int pos_id, Board& target_board);
void Move(Piece &piece, Board &target_board);
void MoveLeft(Piece& piece, Board& target_board);
void MoveRight(Piece &piece, Board &target_board);
void RotateCW(Piece &piece, Board &target_board);
void RotateAntiCW(Piece &piece, Board &target_board);

private:
short int inst_piece_id, inst_pos_id;
bool L_EdgeCollision=0, R_EdgeCollision=0;

};