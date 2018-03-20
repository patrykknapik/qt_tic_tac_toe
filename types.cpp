//
// Created by Patryk Knapik on 15.06.2017.
//
#include "types.h"

std::ostream& operator <<(std::ostream& stream, const result& tmp_result){
    switch (tmp_result){
        case draw:
            stream<<"draw";
            break;

        case player:
            stream<<"player";
            break;

        case computer:
            stream<<"computer";
            break;

        case game_runs:
            stream<<"game runs";
            break;
    }
    return stream;
}

std::ostream& operator <<(std::ostream& stream, const field & tmp_field){
    switch (tmp_field){
        case X:
            stream<<'X';
            break;

        case O:
            stream<<'O';
            break;

        case empty:
            stream<<' ';
            break;
    }
    return stream;
}
