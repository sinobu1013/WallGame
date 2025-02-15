#ifndef WALL_H
#define WALL_H

/**
 * @brief 迷路探索用のノード
 * 
 */
typedef struct{
    POINT now_point;    // このノードの表わす座標
    int deep;           // ここまでの最短距離
}SEARCH_NODE;

ACT coordinate_from_tag_name(char *tag_name);

int check_wall(GAME_DATE game_data);

int shortest_distance(const GAME_DATE game_data, int player);

#endif
