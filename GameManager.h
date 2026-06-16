#pragma once

#include "Board.h"
#include "Piece.h"
#include "MainMenu.h"

#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <windows.h>

class GameManager{
    public:
    unsigned int score=0;
    std::string uuid;
    bool game_over=0, game_paused=0, menu_requested=0, moved_horizontally=0, add_piece_ready = 1;;
    short unsigned int random_piece;
    Board board;
    MainMenu *menu = NULL;
    Piece temp_piece;
    HANDLE consoleHandle;
    GameManager();

    void RenderGame();
    void AddPiece();
    void MovePiece();
    void GameInput();
    void ManageScore();
    void SaveScore();
    ////////////////////////
    void ManageGameStatus();
    void StartNewGame();
    void ResumeGame();
    ////////////////////////
    void StartMainMenu();
};