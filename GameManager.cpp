#include "GameManager.h"

int X=10, Y=20;
const int fps = 12;
int frame_duration = 1000/fps;


GameManager::GameManager(){
    std::thread t1(ManageGameStatus, this);
    t1.join();
};

void GameManager::StartNewGame(){
    board = Board(X,Y);
    temp_piece = Piece();
    score = 0;

    std::thread g1(RenderGame, this);
    std::thread g2(AddPiece, this);
    std::thread g3(MovePiece, this);
    std::thread g4(GameInput, this);
    std::thread g5(ManageScore, this);
    
    g1.join();
    g2.join();
    g3.join();
    g4.join();
    g5.join();

};

void GameManager::ResumeGame(){
    std::thread g1(RenderGame, this);
    std::thread g2(AddPiece, this);
    std::thread g3(MovePiece, this);
    std::thread g4(GameInput, this);
    std::thread g5(ManageScore, this);
    
    g1.join();
    g2.join();
    g3.join();
    g4.join();
    g5.join();
}

void GameManager::RenderGame(){
    COORD cur= {0, 0};
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(consoleHandle, cur);

    while (!game_over && !game_paused)
    {
    board.Draw(board, score);
    board.Preview(random_piece, board);
    std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration));
    cur = {0, 0};
    SetConsoleCursorPosition(consoleHandle, cur);
    }

    if(game_over){
    cur.Y =2*Y/5;
    board.DrawGameOver(consoleHandle, cur);
    }
};

void GameManager::AddPiece(){
    srand((unsigned) time(NULL));
    int random_offset;
    int random_piece_next;
    random_piece = rand() % (piece_list.size() / 4);

    while (!game_over && !game_paused)
    {
    if(add_piece_ready){    
        random_offset = (rand() % (X-3))+1;
        Piece piece = Piece(random_piece, random_offset, board);
        random_piece_next=rand() % (piece_list.size() / 4);
        random_piece=random_piece_next;
        add_piece_ready = 0;
        temp_piece = piece;
    }
    }
};

void GameManager::MovePiece(){
    while (!game_over && !game_paused)
    {
    if(!moved_horizontally){
     std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration));
     temp_piece.Move(temp_piece, board);
     std::this_thread::sleep_for(std::chrono::milliseconds(frame_duration*2));
     if(temp_piece.Paused){add_piece_ready=1;}
    }
    }
};

void GameManager::GameInput(){
    while (!game_over && !game_paused)
    {
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    if(GetAsyncKeyState(VK_RIGHT) & 0x8000){temp_piece.MoveRight(temp_piece, board); moved_horizontally=1; std::this_thread::sleep_for(std::chrono::milliseconds(120));}
    else
    if(GetAsyncKeyState(VK_LEFT) & 0x8000){temp_piece.MoveLeft(temp_piece, board); moved_horizontally=1; std::this_thread::sleep_for(std::chrono::milliseconds(120));}
    else
    if(GetAsyncKeyState(0x45) & 0x8000){temp_piece.RotateCW(temp_piece, board); moved_horizontally=1; std::this_thread::sleep_for(std::chrono::milliseconds(120));}
    else
    if(GetAsyncKeyState(0x51) & 0x8000){temp_piece.RotateAntiCW(temp_piece, board); moved_horizontally=1; std::this_thread::sleep_for(std::chrono::milliseconds(120));}
    else
    if(moved_horizontally==1){moved_horizontally=0;}
    if(GetAsyncKeyState(VK_TAB) & 0x8000){this->random_piece = board.HoldPiece(random_piece, board); std::this_thread::sleep_for(std::chrono::milliseconds(120));}
    if(GetAsyncKeyState(VK_ESCAPE) & 0x8000){this->menu_requested=1; game_paused=1;}
    }
};

void GameManager::ManageScore(){
    while (!game_over && !game_paused)
    {
    if(add_piece_ready){
     int lines_cleared = 0;
     lines_cleared = board.ClearLine(board);
     if(lines_cleared>0){board.combo_lines_cleared += lines_cleared;}else if(lines_cleared==0){board.combo_lines_cleared=1;}
     if(lines_cleared>0) score += lines_cleared*1000*(1 + ((float)((board.combo_lines_cleared)-1))/((float)4));
     game_over = board.CheckGameOver(board, -1);
     if(game_over){std::this_thread::sleep_for(std::chrono::milliseconds(120)); SaveScore(); this->menu_requested=1;}
     
     if(score / (6000 * (Y-board.size_y+1)) >= 1){
     board.size_y--;
     for(int j=0; j<X; j++){
        int pos=board.size_y*10+j;
        board.positions.push_back({pos, 1});
        }
     system("cls");
     }
    }
    }
};

void GameManager::SaveScore(){
    SetConsoleCursorPosition(consoleHandle, {20, 22});
    std::cout<<"UUID"<<std::endl<<"                    ";
    std::cin>>uuid;
    (menu->score_board).push_back({uuid, score});
    menu->score_board_size++;
};

void GameManager::ManageGameStatus(){
    StartMainMenu();
    while (!(menu->quit_requested))
    {
    if(menu->new_game_requested){
        menu->new_game_requested=0;
        this->game_over=0;
        this->game_paused=0;
        std::thread t2(StartNewGame, this);
        t2.join();
    }
    if(menu->resume_requested){
        menu->resume_requested=0;
        this->game_paused=0;
        std::thread t3(ResumeGame, this);
        t3.join();
    }
    if(this->menu_requested){
        this->menu_requested=0;
        if(this->game_paused) menu->resume_menu=1;
        else menu->resume_menu=0;
        std::thread t4(StartMainMenu,this);
        t4.join();
    }
    if(menu->menu_reboot_requested){
        menu->menu_reboot_requested=0;
        std::thread t4(StartMainMenu,this);
        t4.join();
    }
    }
};

///////////////////////////////////////////////////////////////////7

void GameManager::StartMainMenu(){
    if(this->menu == NULL){
    menu = new MainMenu();
    }else{menu->in_menu=1; system("cls");}

    std::thread m1((&MainMenu::RenderMenu), menu);
    std::thread m2((&MainMenu::MenuInput), menu);

    m1.join();
    m2.join();
};
