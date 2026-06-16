#pragma once

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#pragma once

#include <stdio.h>
#include <windows.h>


class MainMenu{
    public:
    MainMenu();
    struct score_entry{
        std::string uuid;
        unsigned int score;
    };
    std::vector<score_entry> score_board;
    void RenderMenu();
    void MenuInput();
    int score_board_size=0;
    bool in_menu, new_game_requested, resume_requested, quit_requested, resume_menu, menu_reboot_requested;

    private:
    int color;
    HANDLE consoleHandle;
    int selection, selection_limit;
    void Select();
    void RenderScoreboard();
    void RenderThemeSelect();


};