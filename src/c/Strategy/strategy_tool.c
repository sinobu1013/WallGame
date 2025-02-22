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
#include "./../game/game.h"
#include "./../game/wall.h"

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

/**
 * @brief その行動が可能かどうか判定
 * 
 * @param game_date ゲーム情報
 * @param activity 行動
 * @param player 調査するプレイヤー
 * @return BOOL 結果
 */
BOOL check_action(const GAME_DATE game_date, ACT activity, int player){
    POINT now = {
        game_date.player[player].position.x,
        game_date.player[player].position.y
    };
    int i;

    // 移動
    if(activity.type == MOVE){
        POINT action = act_conversion(activity.move);
        POINT next = {
            action.x + now.x,
            action.y + now.y
        };
        if(outside_player(next)) return False;
        if(player_check(next, game_date)) return False;
        if(check_NotWall_way(game_date, now, next, activity.move)) return False;
    }

    // 壁設置
    else if(activity.type == CREATE){
        int x = activity.wall_point.x;
        int y = activity.wall_point.y;
        if(outside_player(activity.wall_point)) return False;
        if(activity.direction == WHITE_WALL){
            game_date.board.wall_w[y][x] = WALL;
            POINT point = {x + 1, y};
            if(!outside_player(point)){
                game_date.board.wall_w[y][x+1] = WALL;
            }
    
            // 迷路探索(設置可能場所か探索)
            int deep = check_wall(game_date);
            if(!deep){
                game_date.board.wall_w[y][x] = SPACE;
                game_date.board.wall_w[y][x+1] = SPACE;
                return False;
            }
            game_date.board.wall_w[y][x] = SPACE;
            game_date.board.wall_w[y][x+1] = SPACE;
        // 縦方向の壁設置の場合
        }else if(activity.direction == HEIGHT_WALL){
            game_date.board.wall_h[y][x] = WALL;
            POINT point = {x, y + 1};
            if(!outside_player(point)){
                game_date.board.wall_h[y+1][x] = WALL;
            }
            
            // 迷路探索(設置可能場所か探索)
            int deep = check_wall(game_date);
            if(!deep){
                game_date.board.wall_h[y][x] = SPACE;
                game_date.board.wall_h[y+1][x] = SPACE;
                return False;
            }
            game_date.board.wall_h[y][x] = SPACE;
            game_date.board.wall_h[y+1][x] = SPACE;
        }else{
            return False;
        }
    }else{
        return False;
    }

    return True;
}

/**
 * @brief 次の手を洗い出す
 * 
 * @param game_date ゲーム情報
 * @param player 対称プレイヤー
 * @return NEXT_ACTION 探索結果
 */
NEXT_ACTION all_next_action(GAME_DATE game_date, int player){
    int move_type[5] = {UP, RIGHT, LEFT, DOWN};
    int now_count = 0;
    NEXT_ACTION next_action;
    next_action.sum = 0;
    int i;

    // 移動
    rep(i, 4){
        ACT activity;
        activity.type = MOVE;
        activity.move = move_type[i];
        if(check_action(game_date, activity, player)){
            next_action.next_action[now_count] = activity;
            now_count++;
            next_action.sum++;
        }
    }

    // 壁
    int x, y;
    ACT activity;
    activity.type = CREATE;
    activity.direction = HEIGHT_WALL;
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            activity.wall_point.x = x;
            activity.wall_point.y = y;
            if(check_action(game_date, activity, player)){
                next_action.next_action[now_count] = activity;
                now_count++;
                next_action.sum++;
            }
        }
    }
    activity.direction = WHITE_WALL;;
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            activity.wall_point.x = x;
            activity.wall_point.y = y;
            if(check_action(game_date, activity, player)){
                next_action.next_action[now_count] = activity;
                now_count++;
                next_action.sum++;
            }
        }
    }

    return next_action;
}