//
// Created by Patryk Knapik on 15.06.2017.
//

#include <stdexcept>
#include <vector>
#include <thread>
#include <cmath>
#include "tic_tac_toe.h"
#define TIMEOUT 10000000

tic_tac_toe::~tic_tac_toe(){
    for (int i = 0; i < board_size; ++i) {
        delete[] board[i];
    }
    delete[] board;
}

void tic_tac_toe::set_sizes( int size,  int in_row_size) {
    if (size < 3) {
        throw std::logic_error("Board size too small");
    }
    if (in_row_size < 3) {
        throw std::logic_error("Board size too small");
    }
    if (in_row_size > size) {
        throw std::logic_error("in-row parameter too big");
    }
    in_row = in_row_size;
    board = new field *[size];
    board_size = size;
    for (int i = 0; i < size; ++i) {
        board[i] = new field[size];
        for (int j = 0; j < size; ++j) {
            board[i][j] = empty;
        }
    }
}

result tic_tac_toe::move( int x,  int y) {
    if (board_size < 3) {
        throw std::logic_error("Board size too small");
    }
    if (x >= board_size || y >= board_size) {
        throw std::out_of_range("Punkt poza plansza!");
    }
    if (board[x][y] == empty) {
        board[x][y] = X;
    } else {
        throw std::logic_error("Miejsce zajete!");
    }

    if ((current_result = check_board(board, in_row)) == game_runs) {
        computer_move();
    }

    current_result = check_board(board, in_row);
    //std::cout << current_result << '\n';
    return current_result;
}

result tic_tac_toe::check_board(field **tmp_board,  int specific_in_row) const {
    int size = board_size;
    std::vector<field> checking_stripe;
    result stripe_result;

    //horizontal
    for ( int j = 0; j < size; ++j) {
        for ( int i = 0; i < size; ++i) {
            checking_stripe.push_back(tmp_board[j][i]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }
    //vertical
    for ( int j = 0; j < size; ++j) {
        for ( int i = 0; i < size; ++i) {
            checking_stripe.push_back(tmp_board[i][j]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }
    //diagonal/
    for (int k = 0; k < size; ++k) {
        int inc = 0, dec = k;
        for (; dec >= 0; ++inc, --dec) {
            checking_stripe.push_back(tmp_board[dec][inc]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }

    for (int k = 1; k < size; ++k) {
        int inc = k, dec = size - 1;
        for (; inc < size; ++inc, --dec) {
            checking_stripe.push_back(tmp_board[dec][inc]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }
    //diagonal

    for (int k = 0; k < size; ++k) {
        int inc = 0, dec = k;
        for (; dec < size; ++inc, ++dec) {
            checking_stripe.push_back(tmp_board[dec][inc]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }

    for (int k = 0; k < size; ++k) {
        int inc = k, dec = 0;
        for (; inc < size; ++inc, ++dec) {
            checking_stripe.push_back(tmp_board[dec][inc]);
        }
        stripe_result = check_stripe(checking_stripe, specific_in_row);
        if (stripe_result != draw)
            return stripe_result;
        checking_stripe.clear();
    }

    for (int l = 0; l < size; ++l) {
        for (int i = 0; i < size; ++i) {
            if (tmp_board[l][i] == empty)
                return game_runs;
        }
    }
    return draw;
}

result tic_tac_toe::check_stripe(std::vector<field> &stripe,  int specific_in_row) const {
     int x = 0, o = 0;
    field previous = empty;
    for (auto current_field : stripe) {
        if (previous == current_field) {
            switch (current_field) {
                case X:
                    ++x;
                    break;
                case O:
                    ++o;
                    break;
                case empty:
                    break;
            }
        } else {
            x = 0;
            o = 0;
        }
        if (x >= specific_in_row - 1) {
            return player;
        }
        if (o >= specific_in_row - 1) {
            return computer;
        }

        previous = current_field;
    }

    return draw;
}

void tic_tac_toe::computer_move() {
    move_set move;
     int x, y;
    srand(time(NULL));
    if (board_size <= 3)
        first_move = false;
    if (first_move) {
        do {
            x = rand() % board_size;
            y = rand() % board_size;
        } while (board[x][y] != empty);
        board[x][y] = O;
        first_move = false;
    } else {
        if (get_free_spaces() > 10) {
            move = block_player(in_row - 2);
        } else {
            move.x = -1;
        }

        if (move.x >= board_size || move.y >= board_size || move.x < 0 || move.y < 0)
            move = get_best_move(O, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
        board[move.x][move.y] = O;
        //std::cout << "wykonalem ruch " << move.x << "  " << move.y << '\n';

    }
    counter = 0;

}

move_set tic_tac_toe::get_best_move(field current_sign, int alpha, int beta,  int depth) {
    field next_sign;
    move_set best_move;
    move_set tmp_move;

    ++counter;

    if (current_sign == X) {
        next_sign = O;
        best_move.score = std::numeric_limits<int>::max();
    } else {
        next_sign = X;
        best_move.score = std::numeric_limits<int>::min();
    }

    result state = check_board(board, in_row);
    switch (state) {
        case computer:
            return move_set(10);

        case player:
            return move_set(-10);

        case draw:
            return move_set(0);
        default:
            break;

    }


    for ( int i = 0; i < board_size; ++i) {
        for ( int j = 0; j < board_size; ++j) {
            if (board[i][j] == empty) {
                board[i][j] = current_sign;
                tmp_move.x = i;
                tmp_move.y = j;
                tmp_move.score = get_best_move(next_sign, alpha, beta, depth + 1).score;
                if (current_sign == O) {
                    if (tmp_move.score > best_move.score) {
                        best_move = tmp_move;
                    }
                    if (tmp_move.score >= beta) {
                        board[i][j] = empty;
                        //std::cout<<"Ciecie beta\n";
                        return best_move;
                    }
                    if (tmp_move.score > alpha)
                        alpha = tmp_move.score;
                } else {
                    if (tmp_move.score < best_move.score)
                        best_move = tmp_move;
                    if (tmp_move.score <= alpha) {
                        board[i][j] = empty;
                        //std::cout<<"Ciecie alfa\n";
                        return best_move;
                    }
                    if (tmp_move.score < beta)
                        beta = tmp_move.score;

                }
                board[i][j] = empty;
                if (counter > TIMEOUT) {
                    if (board[(int) round(board_size / 2)][(int) round(board_size / 2)] == empty) {
                        best_move.x = best_move.y = (int) round(board_size / 2);
                        return best_move;
                    }
                    if (board[0][board_size - 1] == empty) {
                        best_move.x = 0;
                        best_move.y = board_size - 1;
                        return best_move;
                    }
                    if (board[board_size - 1][board_size - 1] == empty) {
                        best_move.x = board_size - 1;
                        best_move.y = board_size - 1;
                        return best_move;
                    }
                    return best_move;
                }
            }
        }
    }

    return best_move;
}

move_set tic_tac_toe::block_player( int specific_in_row) {
     int x = 0;
    field previous = empty;
    move_set best_move(0);
    bool in_range = true;
    --specific_in_row;

    //horizontal
    for ( int j = 0; j < board_size; ++j) {
        for ( int i = 0; i < board_size; ++i) {
            if (previous == board[j][i] && previous == X) {
                ++x;
            } else {
                x = 0;
            }
            if (x >= specific_in_row) {
                //std::cout<<"blokowanie horyzontalne";
                best_move.x = j;
                best_move.y = i;
                while (board[best_move.x][best_move.y] == X && best_move.y < (board_size - 1))
                    ++best_move.y;

                if (board[best_move.x][best_move.y] == empty) {
                    return best_move;
                } else {
                    --best_move.y;
                    while (board[best_move.x][best_move.y] == X && best_move.y >= 0)
                        --best_move.y;
                }
                if (best_move.y < 0) {
                    in_range = false;
                }
                if (board[best_move.x][best_move.y] == empty && in_range) {
                    return best_move;
                }
            }
            in_range = true;
            previous = board[j][i];
        }
    }
    previous = empty;
    in_range = true;
    //vertical
    for ( int j = 0; j < board_size; ++j) {
        for ( int i = 0; i < board_size; ++i) {
            if (previous == board[i][j] && previous == X) {
                ++x;
            } else {
                x = 0;
            }
            if (x >= specific_in_row) {
                //std::cout<<"blokowanie wertykalne";
                best_move.x = i;
                best_move.y = j;
                while (board[best_move.x][best_move.y] == X && ++best_move.x < (board_size - 1));

                if (board[best_move.x][best_move.y] == empty) {
                    return best_move;
                } else {

                    while (board[best_move.x][best_move.y] == X && --best_move.x >= 0);
                }
                if (best_move.x < 0) {
                    in_range = false;
                }
                if (board[best_move.x][best_move.y] == empty && in_range) {
                    return best_move;
                }
            }
            in_range = true;
            previous = board[i][j];
        }
    }
    best_move.x = -1;
    return best_move;
}

 int tic_tac_toe::get_free_spaces() {
    int free_spaces = 0;

    for ( int j = 0; j < board_size; ++j) {
        for ( int i = 0; i < board_size; ++i) {
            if (board[j][i] == empty)
                ++free_spaces;
        }
    }
    return free_spaces;
}
