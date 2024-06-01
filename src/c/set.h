#ifndef SET_H
#define SET_H

#define SUM_CELL_W 8
#define SUM_CELL_H 8

#define WHITE_PLAYER 0
#define BLACK_PLAYER 1

#define WALL_SUM_NUMBER 5

#define rep(i, n) for(i=0;i<n;i++)
#define reps(i,s,n) for(i=s;i<n;i++)

/**
 * @brief 座標表示
 * 
 */
typedef struct Point{
    int x;  /**< ｘ座標 */
    int y;  /**< y座標 */
}POINT;

/**
 * @brief ゲームのボード情報
 * 
 */
typedef struct Board{
    int **player;    /**< プレイヤー情報のボード */
    int **wall_w;    /**< 横の壁用 */
    int **wall_h;    /**< 縦の壁用 */
    int num_wall;   /**< 壁の数 */
}BOARD;

/**
 * @brief ゲームの状態
 * 
 */
typedef struct GameDate{
    int turn;           /**< 現在のターン数 */
    BOARD board;        /**< ボード情報 */
    int main_player;    /**< 現ターンのプレイヤー */
    POINT black_player; /**< 黒（プレイヤー）の座標 */
    POINT white_player; /**< 白（プレイヤー）の座標 */
    int black_wall_num; /**< 黒側の残りの壁の枚数 */
    int white_wall_num; /**< 白側の残りの壁の枚数 */
}GAME_DATE;


#endif