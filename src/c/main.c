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
#include <tcl.h>
#include "set.h"
#include "./game/init.h"
#include "./prog/print_value.h"
#include "./prog/queue.h"
#include "./game/game.h"
#include "./gui/gui.h"
#include "./Strategy/random.h"
#include "./Strategy/strategy_tool.h"


/**
 * @brief main関数
 * 
 * @return int 実行成功判定
 */
int main(void){
    // gui();
    GAME_DATE game_date;
    init(&game_date);
    game_date.turn = 1000;
    game_date.board.wall_h[3][2] = 1999;
    GAME_DATE try;
    init(&try);
    copy_game_date(&try, game_date);
    try_print_game_date(try);
    return 0;
}