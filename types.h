//
// Created by Patryk Knapik on 15.06.2017.
//

#ifndef GRA_TYPES_H
#define GRA_TYPES_H

#include <iostream>

enum field {
    empty, O, X
};

enum result {
    draw, player, computer, game_runs
};

struct move_set{
    move_set(){};
    move_set(int tmp_score) : score(tmp_score){};
    int x;
    int y;
    int score;
};

std::ostream& operator <<(std::ostream& stream, const result& tmp_result);
std::ostream& operator <<(std::ostream& stream, const field & tmp_field);


#endif //GRA_TYPES_H
