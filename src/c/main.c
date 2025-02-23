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
#include "./prog/queue.h"
#include "./game/game.h"
#include "./gui/gui.h"
#include "./Strategy/random.h"
#include "./Strategy/strategy_tool.h"
#include "./prog/print_value.h"

/**
 * @brief main関数
 * 
 * @return int 実行成功判定
 */
int main(void){
    gui();
    GAME_DATE game_date;
    init(&game_date);
    NEXT_ACTION next_action = all_next_action(game_date, WHITE_PLAYER);
    calculate_all_next_action(game_date, WHITE_PLAYER, &next_action);
    print_next_action(next_action, WHITE_PLAYER);
    return 0;
}