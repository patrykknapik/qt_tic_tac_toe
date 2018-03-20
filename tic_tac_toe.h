//
// Created by Patryk Knapik on 15.06.2017.
//

#ifndef GRA_TIC_TAC_TOE_H
#define GRA_TIC_TAC_TOE_H

#include <vector>
#include "types.h"

class tic_tac_toe {
    field **board;
    result current_result;
     int in_row;
     int board_size;
    bool first_move;
     long int counter;
    result check_board(field ** tmp_board,  int specific_in_row) const;
    move_set get_best_move(field current_sign,int alpha, int beta, int depth = 0);
    result check_stripe(std::vector<field> & stripe,  int specific_in_row) const;
    move_set block_player( int specific_in_row);
     int get_free_spaces();

public:
    void set_sizes( int size,  int in_row_size);

     int get_board_size(){ return board_size;}

    field ** get_board()const{ return board;}

    result move( int x,  int y);
    void computer_move();

    tic_tac_toe():current_result(game_runs), board_size(0), first_move(true), counter(0){}
    ~tic_tac_toe();

};


#endif //GRA_TIC_TAC_TOE_H
