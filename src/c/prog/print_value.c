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
            printf("%2d", board[y][x]);
        }
        printf("\n");
    }
}