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
#include "./game/wall.h"
#include "./gui/gui.h"
#include "./Strategy/random.h"
#include "./Strategy/strategy_tool.h"
#include "./Strategy/greedy.h"
#include "./prog/print_value.h"

/**
 * @brief main関数の引数を表示
 * 
 * @param argc main関数の引数の数
 * @param argv main関数の引数
 */
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
    int i;
    rep(i, 30){
        ACT activity;
        if(i%2 == 0){
            game_date.main_player = WHITE_PLAYER;
            activity = greedy(game_date);
        }else{
            game_date.main_player = BLACK_PLAYER;
            activity = greedy(game_date);
        }
        game_main(&game_date, activity);
        if(i == 10){
            game_date.player[WHITE_PLAYER].position.y = 6;
            int deep = shortest_distance(game_date, WHITE_PLAYER);
        }
    }

    return 0;
}