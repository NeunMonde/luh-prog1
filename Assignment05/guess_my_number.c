#include "base.h"

int main(void) {
    int number = i_rnd(100);
    while(true){
        int guessed = i_input();
        if (guessed < number){
            printsln("To Small!");
        }
        if (guessed > number){
            printsln("To Large!");
        }
        if (guessed == number){
            printsln("Match");
            break;
        }
    }
    return 0;}
