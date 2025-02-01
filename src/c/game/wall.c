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
