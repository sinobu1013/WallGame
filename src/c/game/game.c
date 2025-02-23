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
#include "wall.h"
#include "game.h"

/**
 * @brief 移動向きから座標の変化値に変換
 * 
 * @param act 移動向き
 * @return POINT 座標の変化値
 */
POINT act_conversion(int act){
    POINT ans = {0, 0};
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
 * @return int 勝者がいる場合は、勝者側を返す。いない場合はFalse
 */
int win_or_loss_decision(GAME_DATE game_date){
    if(game_date.player[WHITE_PLAYER].goal_h == game_date.player[WHITE_PLAYER].position.y) // 自分の勝敗判定
        return WHITE_WIN;
    if(game_date.player[BLACK_PLAYER].goal_h == game_date.player[BLACK_PLAYER].position.y)  // 相手の勝敗判定
        return BLACK_WIN;
    return False;
}


/**
 * @brief ゲームの終了判定
 * 
 * @param game_date ゲーム情報
 * @return int ゲーム終了ならTrue、まだ続くならFalse
 */
int end_decision(const GAME_DATE game_date){
    if(win_or_loss_decision(game_date)) return True;  // 勝敗判定
    if(game_date.turn == SUM_TURN) return True;  // ターン判定
    return False;
}


/**
 * @brief nextの座標に壁がないかの判定
 * 
 * @param game_date ゲーム情報
 * @param next 次に移動する座標
 * @param move_type 移動する向き
 * @return int 移動が可能か（壁がないか）
 */
int check_NotWall_way(const GAME_DATE game_date, POINT now, POINT next, int move_type){
    // 壁の場所をまたいで移動できないように
    if(move_type == UP){
        if(game_date.board.wall_w[next.y][next.x] == WALL)
            return True;
    }else if(move_type == DOWN){
        if(game_date.board.wall_w[now.y][next.x] == WALL)
            return True;
    }else if(move_type == LEFT){
        if(game_date.board.wall_h[next.y][next.x] == WALL)
            return True;
    }else if(move_type == RIGHT){
        if(game_date.board.wall_h[next.y][now.x] == WALL)
            return True;
    }

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
    if(check_NotWall_way(*game_date, game_date->player[game_date->main_player].position, move_position, activity.move)) return False;    // 壁がないかの判定

    game_date->board.player[game_date->player[game_date->main_player].position.y][game_date->player[game_date->main_player].position.x] = SPACE;
    game_date->board.player[move_position.y][move_position.x] = game_date->main_player;
    game_date->player[game_date->main_player].position.x = move_position.x;
    game_date->player[game_date->main_player].position.y = move_position.y;
    if(win_or_loss_decision(*game_date)) return WIN;

    return True;
}


/**
 * @brief 壁を設置
 * 
 * @param game_date ゲーム情報 
 * @param activity 行動情報
 * @return int 設置成功したかどうか
 */
int create_wall(GAME_DATE *game_date, ACT activity){
    if(outside_player(activity.wall_point)) return False;   // 壁設置場所が範囲内か判定
    int x = activity.wall_point.x;
    int y = activity.wall_point.y;
    int sub_WallFlag = False;       // もう一つの壁が設置されていたかどうか
    // 横方向の壁設置の場合
    if(activity.direction == WHITE_WALL){
        if(game_date->board.wall_w[y][x] == WALL) return False;
        game_date->board.wall_w[y][x] = WALL;
        POINT point = {x + 1, y};
        if(game_date->board.wall_w[y][x+1] != WALL){
            if(!outside_player(point)){
                game_date->board.wall_w[y][x+1] = WALL;
                sub_WallFlag =True;
            }
        }

        // 迷路探索(設置可能場所か探索)
        int deep = check_wall(*game_date);
        if(!deep){
            game_date->board.wall_w[y][x] = SPACE;
            if(sub_WallFlag){
                game_date->board.wall_w[y][x+1] = SPACE;
            }
            return False;
        }
    // 縦方向の壁設置の場合
    }else if(activity.direction == HEIGHT_WALL){
        if(game_date->board.wall_h[y][x] == WALL) return False;
        game_date->board.wall_h[y][x] = WALL;
        POINT point = {x, y + 1};
        if(game_date->board.wall_h[y+1][x] != WALL){
            if(!outside_player(point)){
                game_date->board.wall_h[y+1][x] = WALL;
                sub_WallFlag = True;
            }
        }
        
        // 迷路探索(設置可能場所か探索)
        int deep = check_wall(*game_date);
        if(!deep){
            game_date->board.wall_h[y][x] = SPACE;
            if(sub_WallFlag){
                game_date->board.wall_h[y+1][x] = SPACE;
            }
            return False;
        }
    }else{
        return False;
    }

    game_date->board.num_wall++;
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
    int action_flag = False;
    if(activity.type == MOVE){
        action_flag = move(game_date, activity);
        if(action_flag == WIN){
            printf("end\n");
            int white_deep = shortest_distance(*game_date, WHITE_PLAYER);
            printf("White player deep : %d\n", white_deep);
            int black_deep = shortest_distance(*game_date, BLACK_PLAYER);
            printf("Black player deep : %d\n", black_deep);
            if(white_deep < black_deep){
                printf("Winer : White Player!!\n");
            }else if(black_deep < white_deep){
                printf("Winer : Black Player!!\n");
            }else{
                printf("Draw\n");
            }
        }
    }
    if(activity.type == CREATE){
        action_flag = create_wall(game_date, activity);
    }

    if(action_flag) game_date->turn++;  // 行動を起こせた時に、ターンを上げる
    return action_flag;
}