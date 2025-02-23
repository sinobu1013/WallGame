/**
 * @file greedy.c
 * @author okajima
 * @brief 貪欲法
 * @version 0.1
 * @date 2025-02-23
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "./../set.h"
#include "strategy_tool.h"
#include "greedy.h"


/**
 * @brief 貪欲法
 * 
 * @param game_date ゲーム情報 
 * @return ACT 次の手
 */
ACT greedy(GAME_DATE game_date){
    NEXT_ACTION next_action = all_next_action(game_date, game_date.main_player);    // 現時点の状況から取り得る手をすべて取得する
    calculate_all_next_action(game_date, game_date.main_player, &next_action);      // 取り得るそれぞれの手の得点を計算
    return max_score_action(next_action);       // 最大の得点の行動を探索
}