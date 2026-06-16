#include "Board.h"

Board::Board(){};
Board::Board(int X, int Y){
    int pos;
    this->size_x = X;
    this->size_y = Y;
    for(int i=-3; i<0; i++){
        for(int j=0; j<X; j++){
        pos=i*10+j;
        positions.push_back({pos, 0});
        };
    };
    for(int i=0; i<Y; i++){
        for(int j=0; j<X; j++){
        pos=i*10+j;
        positions.push_back({pos, 0});
        };
    };
    for(int j=0; j<X; j++){
        pos=Y*10+j;
        positions.push_back({pos, 1});
    };
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        pos=i*10+j;
        preview.push_back({pos, 0});
        };
    };
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
        pos=i*10+j;
        hold.push_back({pos, 0});
        };
    };

};

void Board::Draw(Board& board, unsigned int& score){
    int pos;
    int i, j;
    int index=0;
    for(i=3; i<this->size_y+3; i++){
        if(i==4) std::cout<<"  COMBO   <!";
        else if(i==5){std::cout<<"  "<< std::fixed << std::setprecision(2) << (1 + ((float)((board.combo_lines_cleared)-1))/((float)4))<<"x   <!";}
        else{std::cout<<"          <!";}
        for(j=0; j<this->size_x; j++){
            pos=i*10+j;
            if(board.positions[pos].state==1) std::cout << " #"; 
            else if(board.positions[pos].state==0) std::cout << " .";
        }
        std::cout<<"!>";    
            if(i==4) std::cout<<"   SCORE";
            else if(i==5) std::cout<<"   "<<score;
            else if(i==7) std::cout<<"   PREVIEW";
            else if(i==8 || i==9 || i==10){
                std::cout<<"    ";
                for(int r = 0; r < 3; r++){
                    if(board.preview[index].state==1) std::cout << "# ";
                    else if(board.preview[index].state==0) std::cout << "  ";
                    index++;
                }
            }
            else if(i==12){std::cout<<"    HOLD"; index=0;}
            else if(i==13 || i==14 || i==15){
                std::cout<<"    ";
                for(int r = 0; r < 3; r++){
                    if(board.hold[index].state==1) std::cout << "# ";
                    else if(board.hold[index].state==0) std::cout << "  ";
                    index++;
                }
            }
            std::cout<<std::endl;     
    }
    std::cout<<"          <!";
    for(j=0; j<this->size_x; j++){
    std::cout<<"==";
    } std::cout<<"!>";
    if(this->rotation_limit_reached){
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"           Rotation Limit Reached!";

    }else{
        std::cout<<std::endl;
        std::cout<<std::endl;
        std::cout<<"                                   ";
    }
};

void Board::Preview(unsigned short int& piece_id, Board& board){
    for(int i = 0; i < 9; i++){
        if(piece_list[piece_id][i]==1){
            board.preview[i].state=1;
        }else board.preview[i].state=0;
    }
};

int Board::HoldPiece(unsigned short int& piece_id, Board& board){
    for(int i = 0; i < 9; i++){
        if(piece_list[piece_id][i]==1){
            board.hold[i].state=1;
        }else board.hold[i].state=0;
    }
    int temp = this->held_piece; 
    this->held_piece = piece_id;
    return temp;
};

void Board::DrawGameOver(HANDLE& consoleHandle, COORD& cur){
    std::cout.flush();
    cur.X = 12; 
    SetConsoleCursorPosition(consoleHandle, cur);
    std::cout<<"--------------------";
    cur.X = 12; cur.Y++;
    SetConsoleCursorPosition(consoleHandle, cur);
    std::cout<<"      GAME OVER     ";
    cur.X = 12; cur.Y++;
    SetConsoleCursorPosition(consoleHandle, cur);
    std::cout<<"--------------------";
};

int Board::ClearLine(Board& board){
    int lines_cleared=0;
    for(int i=3; i<board.size_y+3; i++){
        if(CheckLine(board, i)){
            for(int j=0; j<board.size_x; j++){
            board.positions[i*10+j].state=0;
            }
            lines_cleared+=1;
            for(int l=i; l>3; l--){
                for(int j=0; j<board.size_x; j++){
                    if(board.positions[l*10+j].state){
                        board.positions[l*10+j].state=0;
                        board.positions[l*10+j+10].state=1;
                    }
                }
            }
        }
    }
    return lines_cleared;
};

bool Board::CheckLine(Board& board, int line){
    int index=0;
    bool line_full=1;
    for(int j=0; j<board.size_x; j++){
        index=line*10+j;
        if(board.positions[index].state==0) line_full=0;
    }
    return line_full;
};

bool Board::CheckGameOver(Board& board, int line){
    bool is_game_over=0;
    for(int j=0; j<board.size_x; j++){
        if(board.positions[(line*10+j)+40].state==1) is_game_over=1;
    }
    return is_game_over;
};
