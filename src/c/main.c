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
#include "set.h"
#include "./game/init.h"
#include "./prog/print_value.h"


/**
 * @brief main関数
 * 
 * @return int 実行成功判定
 */
int main(void){
    GAME_DATE game_date;
    init(&game_date);
    game_free(&game_date);
    display_table(game_date.board.player, SUM_CELL_H, SUM_CELL_W);
    return 0;
}