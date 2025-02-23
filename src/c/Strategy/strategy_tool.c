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
        int sub_WallFlag = False;
        if(outside_player(activity.wall_point)) return False;
        if(activity.direction == WHITE_WALL){
            if(game_date.board.wall_w[y][x] == WALL) return False;
            game_date.board.wall_w[y][x] = WALL;
            POINT point = {x + 1, y};
            if(game_date.board.wall_w[y][x+1] != WALL){
                if(!outside_player(point)){
                    game_date.board.wall_w[y][x+1] = WALL;
                    sub_WallFlag = True;
                }
            }
    
            // 迷路探索(設置可能場所か探索)
            int deep = check_wall(game_date);
            if(!deep){
                game_date.board.wall_w[y][x] = SPACE;
                if(sub_WallFlag){
                    game_date.board.wall_w[y][x+1] = SPACE;
                }
                return False;
            }
            game_date.board.wall_w[y][x] = SPACE;
            if(sub_WallFlag){
                game_date.board.wall_w[y][x+1] = SPACE;
            }
        // 縦方向の壁設置の場合
        }else if(activity.direction == HEIGHT_WALL){
            if(game_date.board.wall_h[y][x] == WALL) return False;
            game_date.board.wall_h[y][x] = WALL;
            POINT point = {x, y + 1};
            if(game_date.board.wall_h[y+1][x] != WALL){
                if(!outside_player(point)){
                    game_date.board.wall_h[y+1][x] = WALL;
                    sub_WallFlag = True;
                }
            }
            
            // 迷路探索(設置可能場所か探索)
            int deep = check_wall(game_date);
            if(!deep){
                game_date.board.wall_h[y][x] = SPACE;
                if(sub_WallFlag){
                    game_date.board.wall_h[y+1][x] = SPACE;
                }
                return False;
            }
            game_date.board.wall_h[y][x] = SPACE;
            if(sub_WallFlag){
                game_date.board.wall_h[y+1][x] = SPACE;
            }
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
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            activity.direction = HEIGHT_WALL;
            activity.wall_point.x = x;
            activity.wall_point.y = y;
            if(check_action(game_date, activity, player)){
                next_action.next_action[now_count] = activity;
                now_count++;
                next_action.sum++;
            }
            activity.direction = WHITE_WALL;
            if(check_action(game_date, activity, player)){
                next_action.next_action[now_count] = activity;
                now_count++;
                next_action.sum++;
            }
        }
    }

    return next_action;
}


/**
 * @brief 現時点での得点を計算
 * 
 * @param game_date ゲーム情報
 * @param player プレイヤー
 * @return int 得点
 */
int  GetScore(const GAME_DATE game_date, int player){
    return shortest_distance(game_date, player);
}


/**
 * @brief その行動時の得点を計算
 * 
 * @details
 * GAME_DATEの中身は更新されない。
 * しかし、内部的には変更を行なっている（行なった後、元に戻している）
 * 
 * @param game_date ゲーム情報
 * @param player プレイヤー
 * @param activity 行動
 * @return int 得点
 */
int calculate_score(GAME_DATE game_date, int player, ACT activity){

    if(activity.type == MOVE){
        POINT action = act_conversion(activity.move);
        POINT now = {
            game_date.player[player].position.x,
            game_date.player[player].position.y
        };
        POINT next = {
            game_date.player[player].position.x + action.x,
            game_date.player[player].position.y + action.y
        };
        game_date.board.player[now.y][now.x] = SPACE;
        game_date.board.player[next.y][next.x] = player;
        game_date.player[player].position = next;
        int score = GetScore(game_date, player);
        game_date.board.player[now.y][now.x] = player;
        game_date.board.player[next.y][next.x] = SPACE;
        game_date.player[player].position = now;
        return score;
    }else if(activity.type == CREATE){
        BOOL sub_WallFlag = False;
        int y = activity.wall_point.y;
        int x = activity.wall_point.x;
        if(activity.direction == WHITE_WALL){
            game_date.board.wall_w[y][x] = WALL;
            POINT point = {x+1, y};
            if(game_date.board.wall_w[y][x+1] != WALL){
                if(!outside_player(point)){
                    game_date.board.wall_w[y][x+1] = WALL;
                    sub_WallFlag = True;
                }
            }

            int score = GetScore(game_date, player);
            game_date.board.wall_w[y][x] = SPACE;
            if(sub_WallFlag){
                game_date.board.wall_w[y][x+1] = SPACE;
            }
            return score;
        
        }else if(activity.direction == HEIGHT_WALL){
            game_date.board.wall_h[y][x] = WALL;
            POINT point = {x, y+1};
            if(game_date.board.wall_h[y+1][x] != WALL){
                if(!outside_player(point)){
                    game_date.board.wall_h[y+1][x] = WALL;
                    sub_WallFlag = True;
                }
            }

            int score = GetScore(game_date, player);
            game_date.board.wall_h[y][x] = SPACE;
            if(sub_WallFlag){
                game_date.board.wall_h[y+1][x] = SPACE;
            }
            return score;
        }
    }
}


/**
 * @brief 次の手の得点を全て計算する（結果はNEXT_ACTIONに格納）
 * 
 * @param game_date ゲーム情報
 * @param player プレイヤー
 * @param next_action 次の手をまとめたもの
 */
void calculate_all_next_action(GAME_DATE game_date, int player, NEXT_ACTION *next_action){
    int i;
    int sum = next_action->sum;

    rep(i, sum){
        next_action->score[i] = calculate_score(game_date, player, next_action->next_action[i]);
    }
}


/**
 * @brief 得点が最大の行動を探索
 * 
 * @param next_action 次の行動のまとめ
 * @return ACT 
 */
ACT max_score_action(NEXT_ACTION next_action){
    int i;
    int max = INF;
    int index = INF;

    rep(i, next_action.sum){
        if(max > next_action.score[i]){
            max = next_action.score[i];
            index = i;
        }
    }

    return next_action.next_action[index];
}