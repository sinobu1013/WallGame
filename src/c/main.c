/**
 * @file main.c
 * @author okajima
 * @brief main関数
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tcl.h>
#include "set.h"
#include "./game/init.h"
#include "./prog/queue.h"
#include "./game/game.h"
#include "./gui/gui.h"
#include "./Strategy/random.h"
#include "./Strategy/strategy_tool.h"
#include "./prog/print_value.h"


void print_main(int argc, char *argv[]){
    int i;

    printf("argc : %d\n", argc);
    rep(i, argc){
        printf("argv[%d] = %s\n", i, argv[i]);
    }
}


/**
 * @brief main 関数
 * 
 * @param argc 引数の個数
 * @param argv 値
 * @return int 実効性効果どうか
 */
int main(int argc, char *argv[]){
    print_main(argc,argv);
    
    if(argc != 1){
        if(strcmp(argv[1], "gui") == 0){
            gui();
            return 0;
        }
    }

    GAME_DATE game_date;
    init(&game_date);
    NEXT_ACTION next_action = all_next_action(game_date, WHITE_PLAYER);
    calculate_all_next_action(game_date, WHITE_PLAYER, &next_action);
    print_next_action(next_action, WHITE_PLAYER);
    return 0;
}