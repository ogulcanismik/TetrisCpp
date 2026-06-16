#include "MainMenu.h"

MainMenu::MainMenu(){
    this->color=2;
    this->in_menu=1;
    this->selection=3;
    this->selection_limit=3;
    this->resume_menu=0;
    this->new_game_requested=0;
    this->resume_requested=0;
};

void MainMenu::RenderMenu(){
    COORD cur={0, 8};
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(consoleHandle, cur);
    SetConsoleTextAttribute(consoleHandle, color);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    if(resume_menu){
    this->selection=4;
    this->selection_limit=4;
    }
    while(in_menu)
    {
    if(resume_menu){
    if (selection==4){std::cout<<"           > RESUME <";}
    else{std::cout<<"             RESUME  ";}; 

    std::cout<<std::endl<<std::endl<<std::endl;     
    }

    if(selection==3){std::cout<<"          > NEW GAME <";}
    else{std::cout<<"            NEW GAME  ";};
    
    std::cout<<std::endl<<std::endl<<std::endl;

    if(selection==2){std::cout<<"         > SCOREBOARD <";}
    else{std::cout<<"           SCOREBOARD  ";};

    std::cout<<std::endl<<std::endl<<std::endl;

    if(selection==1){std::cout<<"        > THEME SELECT <";}
    else{std::cout<<"          THEME SELECT  ";};

    std::cout<<std::endl<<std::endl<<std::endl;

    if(selection==0){std::cout<<"            > QUIT <";}
    else{std::cout<<"              QUIT  ";};

    std::this_thread::sleep_for(std::chrono::milliseconds(120));

    cur = {0, 8};
    SetConsoleCursorPosition(consoleHandle, cur);
    }
};

void MainMenu::RenderScoreboard(){
    system("cls");
    std::cout<<"############## SCOREBOARD ##############"<<std::endl<<std::endl;
    for(int i=0; i<score_board_size; i++){
    std::cout<<"          "<<score_board[i].uuid<<"            "<<score_board[i].score<<std::endl;
    }
    while(!in_menu){
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
        this->menu_reboot_requested=1;
        break;
        }
    }
};

void MainMenu::RenderThemeSelect(){
    system("cls");
    while(!in_menu){
        SetConsoleCursorPosition(consoleHandle, {0,0});
        std::cout<<"############## THEME SELECT ##############"<<std::endl<<std::endl;
        std::cout<<"               <- Color ->                ";

        if(GetAsyncKeyState(VK_LEFT) & 0x8000){this->color--; SetConsoleTextAttribute(consoleHandle, color); std::this_thread::sleep_for(std::chrono::milliseconds(125));}
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000){this->color++; SetConsoleTextAttribute(consoleHandle, color); std::this_thread::sleep_for(std::chrono::milliseconds(125));}
        if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){
        this->menu_reboot_requested=1; 
        break;
        }
    }
};

void MainMenu::MenuInput(){
    while(in_menu)
    {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if(this->selection>0 && GetAsyncKeyState(VK_DOWN) & 0x8000){
        this->selection--;
        std::this_thread::sleep_for(std::chrono::milliseconds(125));
    }else if(this->selection<selection_limit && GetAsyncKeyState(VK_UP) & 0x8000){
        this->selection++;
        std::this_thread::sleep_for(std::chrono::milliseconds(125));
    }else if(GetAsyncKeyState(VK_SPACE) & 0x8000){
        SetConsoleCursorPosition(consoleHandle, {0,0});
        Select();
    }
    }
};

void MainMenu::Select(){
    if(this->selection==4){
    this->in_menu=0;
    this->resume_requested=1;
    }
    else if(this->selection==3){
    this->in_menu=0;
    this->new_game_requested=1;
    }
    else if(this->selection==2){
    this->in_menu=0;
    std::thread r1(RenderScoreboard, this);
    r1.join();
    }
    else if(this->selection==1){
    this->in_menu=0;
    std::thread r2(RenderThemeSelect, this);
    r2.join();
    }
    else if(this->selection==0){
    this->in_menu=0;
    this->quit_requested=1;
    } 
};
