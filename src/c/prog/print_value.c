/**
 * @file print_value.c
 * @author okajima
 * @brief データを表示用（視覚化）
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include "./../set.h"
#include "print_value.h"

char game_data_filename[N] = "game_data.txt";

/**
 * @brief 2次元半列をコンソールに表示
 * 
 * @param board 2次元配列
 * @param h 縦の数
 * @param w 横の数
 */
void display_table(int **board, int h, int w){
    int x, y;
    rep(y, h){
        rep(x, w){
            printf("%3d", board[y][x]);
        }
        printf("\n");
    }
}

void game_data_show_init(void){
    FILE *f;
    f = fopen(game_data_filename, "w");
    fprintf(f, "game_data information\n");
    fclose(f);
}

void game_data_showTextFile(const GAME_DATE game_data){
    FILE *f;
    game_data_show_init();
    f = fopen(game_data_filename, "a");
    
    fprintf(f, "turn : %d\n", game_data.turn);
    fprintf(f, "main_player : ");
    if(game_data.main_player == WHITE_PLAYER){
        fprintf(f, "white player\n");
    }else if(game_data.main_player == BLACK_PLAYER){
        fprintf(f, "black player\n");
    }

    int y, x;
    fprintf(f, "\n---------------board infor --------------------\n");
    fprintf(f, "player\n");
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            fprintf(f, "%2d", game_data.board.player[y][x]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "wall_w\n");
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            fprintf(f, "%2d", game_data.board.wall_w[y][x]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "wall_h\n");
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W){
            fprintf(f, "%2d", game_data.board.wall_h[y][x]);
        }
        fprintf(f, "\n");
    }
    fprintf(f, "num_wall : %d\n", game_data.board.num_wall);

    int i;
    fprintf(f, "\n-----------------player--------------------\n");
    reps(i, 1, SUM_PLAYER_NUMBER+1){
        fprintf(f, "player %d\n", i);
        fprintf(f, "Point x:%d, y:%d\n", game_data.player[i].position.x, game_data.player[i].position.y);
        fprintf(f, "wall_num : %d\n", game_data.player[i].wall_num);
        fprintf(f, "goal_h : %d\n", game_data.player[i].goal_h);
        fprintf(f, "\n");
    }

    fclose(f);
}