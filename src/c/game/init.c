/**
 * @file init.c
 * @author okajima
 * @brief ゲームの初期化
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include "../set.h"
#include "init.h"

/**
 * @brief ゲームの初期化（メイン）
 * 
 * @param game_date ゲーム情報
 */
void init(GAME_DATE *game_date){
    game_date->turn = 0;
    game_date->main_player = WHITE_PLAYER;
    game_date->board.num_wall = 0;
    
    game_date->player = (PLAYER*)malloc(sizeof(PLAYER) * (SUM_PLAYER_NUMBER + 1));
    if(game_date->player == NULL){
        perror("Failed to allocate memory for player information");
        exit(EXIT_FAILURE);
    }
    game_date->player[WHITE_PLAYER].position.y = SUM_CELL_H - 1;
    game_date->player[WHITE_PLAYER].position.x = SUM_CELL_W / 2;
    game_date->player[WHITE_PLAYER].goal_h = 0;
    game_date->player[BLACK_PLAYER].position.y = 0;
    game_date->player[BLACK_PLAYER].position.x = SUM_CELL_W / 2;
    game_date->player[BLACK_PLAYER].goal_h = SUM_CELL_H - 1;

    int i, j;

    // プレイヤーボードを初期化
    game_date->board.player = (int**)malloc(sizeof(int*) * SUM_CELL_H);
    if(game_date->board.player == NULL){
        perror("Failed to allocate memory for player board");
        exit(EXIT_FAILURE);
    }
    rep(i, SUM_CELL_H){
        game_date->board.player[i] = (int*)malloc(sizeof(int) * SUM_CELL_W);
        if(game_date->board.player[i] == NULL){
            perror("Failed to allocate memory for player board row");
            while(i-- > 0) free(game_date->board.player[i]);  // 既に確保したメモリの解放
            free(game_date->board.player);
            exit(EXIT_FAILURE);
        }
        rep(j, SUM_CELL_W){
            game_date->board.player[i][j] = 0;
        }
    }

    // 壁の座標情報（縦）を初期化
    game_date->board.wall_h = (int**)malloc(sizeof(int*) * (SUM_CELL_H + 1));
    if(game_date->board.wall_h == NULL){
        perror("Failed to allocate memory for wall_h board");
        exit(EXIT_FAILURE);
    }
    rep(i, SUM_CELL_H + 1){
        game_date->board.wall_h[i] = (int*)malloc(sizeof(int) * SUM_CELL_W);
        if(game_date->board.wall_h[i] == NULL){
            perror("Failed to allocate memory for wall_h board row");
            while(i-- > 0) free(game_date->board.wall_h[i]);  // 既に確保したメモリを解放
            free(game_date->board.wall_h);
            exit(EXIT_FAILURE);
        }
        rep(j, SUM_CELL_W){
            game_date->board.wall_h[i][j] = 0;
        }
    }

    // 壁の座標情報（横）を初期化
    game_date->board.wall_w = (int**)malloc(sizeof(int*) * SUM_CELL_H);
    if(game_date->board.wall_w == NULL){
        perror("Failed to allocate memory for wall_w board");
        exit(EXIT_FAILURE);
    }
    rep(i, SUM_CELL_H){
        game_date->board.wall_w[i] = (int*)malloc(sizeof(int) * (SUM_CELL_W + 1));
        if(game_date->board.wall_w[i] == NULL){
            perror("Failed to allocate memory for wall_w board row");
            while(i-- > 0) free(game_date->board.wall_w[i]);  // 既に確保したメモリを解放
            free(game_date->board.wall_w);
            exit(EXIT_FAILURE);
        }
        rep(j, SUM_CELL_W + 1){
            game_date->board.wall_w[i][j] = 0;
        }
    }

    game_date->board.player[game_date->player[WHITE_PLAYER].position.y][game_date->player[WHITE_PLAYER].position.x] = WHITE_PLAYER;
    game_date->board.player[game_date->player[BLACK_PLAYER].position.y][game_date->player[BLACK_PLAYER].position.x] = BLACK_PLAYER;
}

/**
 * @brief ゲーム中に確保した領域の開放
 * 
 * @param game_date ゲーム情報
 */
void game_free(GAME_DATE *game_date){
    int i;
    rep(i, SUM_CELL_H){
        free(game_date->board.player[i]);
        free(game_date->board.wall_h[i]);
        free(game_date->board.wall_w[i]);
    }
    free(game_date->board.player);
    free(game_date->board.wall_h);
    free(game_date->board.wall_w);
}