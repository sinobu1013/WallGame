#ifndef SET_H 
#define SET_H

#define SUM_CELL_W 8    /**< 横のマスの数 */
#define SUM_CELL_H 8    /**< 縦のマスの数 */

#define SPACE 0         /**< 空白 */
#define WHITE_PLAYER 1  /**< 白のプレイヤー */
#define BLACK_PLAYER 2  /**< 黒のプレイヤー */
#define WALL 3

#define MOVE 1      /**< 移動 */
#define CREATE 2    /**< 壁の設置 */
#define STAY 0      /**< 滞在 */

#define UP 1        /**< 上 */
#define DOWN 2      /**< 下 */
#define RIGHT 3     /**< 右 */
#define LEFT 4      /**< 左 */

#define WHITE_WALL 1        /**< 横向きの壁 */
#define HEIGHT_WALL 2       /**< 縦向きの壁 */      

#define WIN 999     /**< 勝利 */
#define WHITE_WIN WIN + WHITE_PLAYER    /**< 白の勝利 */
#define BLACK_WIN WIN + BLACK_PLAYER    /**< 黒の勝利 */
#define WALL_SUM_NUMBER 5   /**< 壁の枚数（初期値） */
#define SUM_PLAYER_NUMBER 2 /**< プレイヤー数 */

#define rep(i, n) for(i=0;i<n;i++)
#define reps(i,s,n) for(i=s;i<n;i++)
#define True 1
#define False 0
#define DATE 200

#define SUM_TURN 30

#define N 100

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
 * @brief プレイヤー情報
 * 
 */
typedef struct Player{
    POINT position;     /**< プレイヤーの座標 */
    int wall_num;       /**< 残りの壁の枚数 */
    int goal_h;         /**< ゴールの位置 */
}PLAYER;

/**
 * @brief ゲームの状態
 * 
 */
typedef struct GameDate{
    int turn;           /**< 現在のターン数 */
    BOARD board;        /**< ボード情報 */
    int main_player;    /**< 現ターンのプレイヤー */
    PLAYER *player;     /**< プレイヤー情報 */
}GAME_DATE;

/**
 * @brief 行動情報
 * 
 */
typedef struct Activity{
    int type;           /**< 行動の種類 */
    int move;           /**< 移動する場合の向き */
    POINT wall_point;   /**< 壁を設置する場合の座標 */
    int direction;      /**< 壁を設置する場合の向き */
}ACT;

#endif