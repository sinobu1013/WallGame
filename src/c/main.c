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
#include "./gui/match_gui.h"
#include "./Strategy/random.h"
#include "./Strategy/strategy_tool.h"
#include "./Strategy/greedy.h"
#include "./Strategy/alphabeta.h"
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
    ACT (*default_fStrategy)(GAME_DATE) = greedy;
    ACT (*default_sStrategy)(GAME_DATE) = greedy;
    print_main(argc,argv);
    
    if(argc != 1){
        
        // プレイヤー vs CPU
        if(strcmp(argv[1], "gui") == 0){
            gui();
            return 0;
        }

        // CPU vs CPU
        if(strcmp(argv[1], "match") == 0) {
            if(argc == 2) {
                GAME_RESULT result = match(default_fStrategy, default_sStrategy, True);
                matchResult_print(result);
            }
        }

        // CPU vs CPU（GUI）
        if(strcmp(argv[1], "match_gui") == 0) {
            if(argc == 2) {
                match_gui(default_fStrategy, default_sStrategy);
            }
        }
    }    
    return 0;
}