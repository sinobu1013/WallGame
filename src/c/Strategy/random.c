/**
 * @file random.c
 * @author okajima
 * @brief ランダムな行動メイン
 * @version 0.1
 * @date 2025-02-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./../set.h"
#include "./../game/game.h"
#include "random.h"

/**
 * @brief 適当ランダム
 * 
 * @param game_data ゲーム情報
 * @return ACT 次の手
 */
ACT random_move(GAME_DATE game_data){
    ACT activity;
    int move_type[5] = {UP, RIGHT, DOWN, LEFT};
    int ran = 0;
    srand(time(NULL));
    while(1){
        ran = rand() % 4;
        POINT action = act_conversion(move_type[ran]);
        POINT next = {
            game_data.player[game_data.main_player].position.x + action.x,
            game_data.player[game_data.main_player].position.y + action.y
        };
        if(outside_player(next)) continue;;
        if(check_NotWall_way(&game_data, game_data.player[game_data.main_player].position, next, move_type[ran]))
            continue;
        
        break;
    }

    activity.type = MOVE;
    activity.move = move_type[ran];

    return activity;
}