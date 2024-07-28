/**
 * @file game.c
 * @author okajima
 * @brief ゲームプログラム
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "./../set.h"
#include "game.h"

/**
 * @brief 移動向きから座標の変化値に変換
 * 
 * @param act 移動向き
 * @return POINT 座標の変化値
 */
POINT act_conversion(int act){
    POINT ans;
    if(act == UP){
        ans.x = 0, ans.y = -1;
    }
    if(act == DOWN){
        ans.x = 0, ans.y = 1;
    }
    if(act == RIGHT){
        ans.x = 1, ans.y = 0;
    }
    if(act == LEFT){
        ans.x = -1, ans.y = 0;
    }

    return ans;
}

/**
 * @brief プレイヤーの座標がボードの範囲外かどうかを判定する
 * 
 * @param point プレイヤーの座標
 * @return int 範囲外ならTrue、範囲内ならFalse
 */
int outside_player(POINT point){
    if(point.x < 0 || point.x >= SUM_CELL_W) return True;
    if(point.y < 0 || point.y >= SUM_CELL_H) return True;
    return False;
}

/**
 * @brief 引数の座標にプレイヤーが存在するか判定する
 * 
 * @param point プレイヤーの座標
 * @param game_date ゲーム情報
 * @return int 有：True、無：False
 */
int player_check(POINT point, const GAME_DATE game_date){
    int x = game_date.player[WHITE_PLAYER].position.x;
    int y = game_date.player[WHITE_PLAYER].position.y;
    if(x == point.x && y == point.y) return True;
    
    x = game_date.player[BLACK_PLAYER].position.x;
    y = game_date.player[BLACK_PLAYER].position.y;
    if(x == point.x && y == point.y) return True;
    
    return False;
}

/**
 * @brief 勝敗判定
 * 
 * @param game_date ゲーム情報
 * @return int 勝利したかどうか
 */
int win_or_loss_decision(GAME_DATE game_date){
    if(game_date.player[game_date.main_player].goal_h == game_date.player[game_date.main_player].position.y)
        return True;
    return False;
}

/**
 * @brief プレイヤーの移動関数
 * 
 * @param game_date ゲーム情報
 * @param activity 行動情報
 * @return int 行動成功かどうか
 */
int move(GAME_DATE *game_date, ACT activity){
    POINT move_change = act_conversion(activity.move);
    POINT move_position = {
        move_change.x + game_date->player[game_date->main_player].position.x,
        move_change.y + game_date->player[game_date->main_player].position.y
        };
    if(outside_player(move_position)) return False;     // 範囲内か判定
    if(player_check(move_position, *game_date)) return False;  // プレイヤーが有かの判定

    game_date->board.player[game_date->player[game_date->main_player].position.y][game_date->player[game_date->main_player].position.x] = SPACE;
    game_date->board.player[move_position.y][move_position.x] = game_date->main_player;
    game_date->player[game_date->main_player].position.x = move_position.x;
    game_date->player[game_date->main_player].position.y = move_position.y;
    if(win_or_loss_decision(*game_date)) return WIN;

    return True;
}

/**
 * @brief ゲーム進行関数（メイン）
 * 
 * @param game_date ゲーム情報
 * @param activity 行動
 * @return int 行動成功かどうか
 */
int game_main(GAME_DATE *game_date, ACT activity){
    game_date->turn++;
    if(activity.type == MOVE){
        int move_flag = move(game_date, activity);
        printf("%d\n", move_flag);
        if(move_flag == WIN){
            printf("終了");
        }
    }

    return True;
}