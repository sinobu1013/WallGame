/**
 * @file wall.c
 * @author okajima
 * @brief 
 * @version 0.1
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "./../set.h"
#include "game.h"
#include "wall.h"
#include "./../prog/queue.h"
#include "./../prog/print_value.h"

/**
 * @brief wallのタグ名から情報を取得
 * 
 * @param s タグ名
 * @return ACT 取得した情報（壁の設置場所）
 */
ACT coordinate_from_tag_name(char *tag_name){
    int i, j, k;
    char str[N][N];
    ACT ans;
    i = j = k = 0;
    while(tag_name[i]){
        if(tag_name[i] == '_'){
            str[j][k] = '\0';
            j++;
            k = 0;
            i++;
            continue;
        }
        str[j][k] = tag_name[i];
        k++;
        i++;
    }
    str[j][k] = '\0';

    if(str[1][0] == 'w'){
        ans.direction = WHITE_WALL;
    }else if(str[1][0] = 'h'){
        ans.direction = HEIGHT_WALL;
    }
    ans.wall_point.x = atoi(str[2]);
    ans.wall_point.y = atoi(str[3]);

    return ans;
}


/**
 * @brief 現在のプレイヤーの位置からゴールまでの最短距離を探索
 * 
 * @param game_data ゲーム情報
 * @return int ゴールまでの最短距離
 */
int shortest_distance(const GAME_DATE game_data){
    int i, j;
    SEARCH_NODE *now_player = (SEARCH_NODE*)malloc(sizeof(SEARCH_NODE));
    QUEUE queue = CreateQueue();    // キュー
    int check[5] = {UP, RIGHT, DOWN, LEFT};
    int **check_board;
    check_board = (int **)malloc(SUM_CELL_H * sizeof(int*));
    rep(i, SUM_CELL_H) check_board[i] = (int *)malloc(SUM_CELL_W * sizeof(int));
    rep(i, SUM_CELL_H){
        rep(j, SUM_CELL_W) check_board[i][j] = 0;
    }
    now_player->now_point = game_data.player[game_data.main_player].position;    //プレイヤーの現在位置を格納
    now_player->deep = 0;    // 最短距離は0で初期化
    check_board[now_player->now_point.y][now_player->now_point.x]++;
    EnQueue(&queue, now_player, sizeof(SEARCH_NODE*));
    SEARCH_NODE *node = (SEARCH_NODE*)DeQueue(&queue, sizeof(SEARCH_NODE*));

    do{
        int i;
        rep(i, 4){
            POINT next;
            POINT action = act_conversion(check[i]);
            next.x = node->now_point.x + action.x;
            next.y = node->now_point.y + action.y;
            if(outside_player(next)){ // 盤内か判定}
                continue;     
            }
            if(player_check(next, game_data)){  // プレイヤーがいないか判定
                continue;     
            }
            if(check_board[next.y][next.x]) continue;

            // 終了判定
            if(next.y == game_data.player[game_data.main_player].goal_h){
                int ans = node->deep + 1;
                free(node);
                return ans;
            }

            if(check_NotWall_way(&game_data, node->now_point, next, check[i])){ // 壁がないか判定
                continue;     
            }

            SEARCH_NODE *now_data = (SEARCH_NODE*)malloc(sizeof(SEARCH_NODE));
            now_data->deep = node->deep + 1;
            now_data->now_point = next;
            check_board[next.y][next.x] = now_data->deep;
            EnQueue(&queue, now_data, sizeof(SEARCH_NODE*));
        }
        free(node);
        node = (SEARCH_NODE*)DeQueue(&queue, sizeof(SEARCH_NODE*));
    }while(node != NULL);

    return 0;   // ゴール不可
}
