#include "Piece.h"

Piece::Piece(){};

Piece::Piece(int piece_id, int pos_id, Board& target_board){
    inst_piece_id=piece_id;
    inst_pos_id=pos_id;
    int index=0;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(piece_list[inst_piece_id][index]==1){
                target_board.positions[(inst_pos_id+i*10+j)].state = true;
            }
            index++;
        }
    }
    target_board.rotation_limit_reached=0;
};

void Piece::Move(Piece& piece, Board& target_board){
    int i, j, index=0;

    if(!piece.Paused){
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=0;    
                }
                index++;
            }
        }

    index=0;    
        
        if(L_EdgeCollision){
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if(target_board.positions[piece.inst_pos_id+(i*10)+j-1].state==0){piece.L_EdgeCollision=0;}
                }
                index++;
            }
        }
        }

    index=0;    
        
        if(R_EdgeCollision){
        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if(target_board.positions[piece.inst_pos_id+(i*10)+j+1].state==0){piece.R_EdgeCollision=0;}
                }
                index++;
            }
        }
        }

    index=0;

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if(target_board.positions[piece.inst_pos_id+(i*10)+j+20].state==1) piece.Paused=1;
                }
                index++;
            }
        }

    index=0;
    piece.inst_pos_id=piece.inst_pos_id+10;

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=1;
                }
                index++;
            }
        }    
    }
};


void Piece::MoveLeft(Piece& piece, Board& target_board){
    int i, j, index=0;

    if(!piece.Paused && !L_EdgeCollision){

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if((piece.inst_pos_id+(i*10)+j) % 10 == 0) return;
                }
                index++;
            }
        }
    
    index=0;

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=0;    
                }
                index++;
            }
        }

    index=0;
    

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if(target_board.positions[piece.inst_pos_id+(i*10)+j-1].state==1){piece.L_EdgeCollision=1;}
                }
                index++;
            }
        }

    index=0;
    piece.inst_pos_id=piece.inst_pos_id-(int)(!piece.L_EdgeCollision);

        for(i = 0; i < 3; i++){
            for(j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=1;
                }
                index++;
            }
        } 
    }
};


void Piece::MoveRight(Piece& piece, Board& target_board){
    int index=0;

    if(!piece.Paused && !R_EdgeCollision){

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if((piece.inst_pos_id+(i*10)+j) % 10 == 9) return;
                }
            index++;
            }
        }

    index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=0;    
                }
            index++;
            }
        }

    index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){             
                    if(target_board.positions[piece.inst_pos_id+(i*10)+j+1].state==1){piece.R_EdgeCollision=1;}
                }
            index++;
            }
        }

    index=0;
    piece.inst_pos_id=piece.inst_pos_id+(int)(!piece.R_EdgeCollision);

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=1;
                }
            index++;
            }
        }
    }
};

void Piece::RotateCW(Piece& piece, Board& target_board){
    if(!piece.Paused && (this->rotation_limit>0)){

    int index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=0;    
                }
                index++;
            }
        }

    if(piece.inst_piece_id<30){
    piece.inst_piece_id += 10;
    }else{piece.inst_piece_id -= 30;}

    index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=1;
                }
                index++;
            }
        }

    this->rotation_limit--;
    }else if(this->rotation_limit == 0){
    target_board.rotation_limit_reached=1;
    }
};

void Piece::RotateAntiCW(Piece& piece, Board& target_board){
    if(!piece.Paused && (this->rotation_limit>0)){

    int index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=0;    
                }
                index++;
            }
        }

    if(piece.inst_piece_id>10){
    piece.inst_piece_id -= 10;
    }else{piece.inst_piece_id += 30;}

    index=0;

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(piece_list[piece.inst_piece_id][index]==1){
                    target_board.positions[piece.inst_pos_id+i*10+j].state=1;
                }
                index++;
            }
        }

    this->rotation_limit--;

    }else if(this->rotation_limit == 0){
    target_board.rotation_limit_reached=1;
    }
};




