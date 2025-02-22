/**
 * @file strategy_tool.c
 * @author okajima
 * @brief 戦略アルゴリズム開発での共有関数
 * @version 0.1
 * @date 2025-02-22
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include "./../set.h"
#include "strategy_tool.h"

/**
 * @brief ゲーム情報構造体をコピーする（依存関係がない状態で）
 * 
 * @param main コピーする構造体
 * @param sub コピー元
 * @return BOOL 成功
 */
BOOL copy_game_date(GAME_DATE *main, const GAME_DATE sub){
    
    // ターン
    main->turn = sub.turn;
    // メインプレイヤー
    main->main_player = sub.main_player;
    
    // プレイヤー情報
    main->player[WHITE_PLAYER].position.y = sub.player[WHITE_PLAYER].position.y;
    main->player[WHITE_PLAYER].position.x = sub.player[WHITE_PLAYER].position.x;
    main->player[WHITE_PLAYER].goal_h = sub.player[WHITE_PLAYER].goal_h;
    main->player[BLACK_PLAYER].position.y = sub.player[BLACK_PLAYER].position.y;
    main->player[BLACK_PLAYER].position.x = sub.player[BLACK_PLAYER].position.x;
    main->player[BLACK_PLAYER].goal_h = sub.player[BLACK_PLAYER].goal_h;
    main->player[WHITE_PLAYER].wall_num = sub.player[WHITE_PLAYER].wall_num;
    main->player[BLACK_PLAYER].wall_num = sub.player[BLACK_PLAYER].wall_num;

    // 壁情報
    int x, y;
    // 壁の数
    main->board.num_wall = sub.board.num_wall;

    // プレイヤーの位置情報マップ
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            main->board.player[y][x] = sub.board.player[y][x];
        }
    }
    // 壁（縦）
    rep(y, SUM_CELL_H + 1){
        rep(x, SUM_CELL_W){
            main->board.wall_h[y][x] = sub.board.wall_h[y][x];
        }
    }
    //壁（横）
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W + 1){
            main->board.wall_w[y][x] = sub.board.wall_w[y][x];
        }
    }
    return True;
}

BOOL check_action(GAME_DATE game_date, ACT Activity){

}

NEXT_ACTION all_next_action(GAME_DATE game_date){

}