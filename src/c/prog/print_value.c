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
#include "./../Strategy/strategy_tool.h"
#include "print_value.h"

char game_data_filename[N] = "game_data.txt";
char All_next_action_filename[N] = "src/c/prog/debug/All_next_action.txt";

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

/**
 * @brief ゲーム情報を表示ファイルの初期化
 * 
 */
void game_data_show_init(void){
    FILE *f;
    f = fopen(game_data_filename, "w");
    fprintf(f, "game_data information\n");
    fclose(f);
}

/**
 * @brief ゲーム情報をテキストファイルに書き出す
 * 
 * @param game_data ゲーム情報
 */
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

/**
 * @brief ゲーム情報をテキストファイルに書き出す（簡略化バージョン）
 * 
 * @param game_date ゲーム情報
 */
void try_print_game_date(const GAME_DATE game_date){
    game_data_show_init();
    game_data_showTextFile(game_date);
}

/**
 * @brief 次の手をすべてテキストファイルに出力する
 * 
 * @param next_action 次の手
 * @param player プレイヤー
 */
void print_next_action(NEXT_ACTION next_action, int player){
    FILE *f;
    f = fopen(All_next_action_filename, "w");

    fprintf(f, "All Next Action\n");

    if(player == WHITE_PLAYER){
        fprintf(f, "player : White Player\n");
    }else if(player == BLACK_PLAYER){
        fprintf(f, "player : Black Player\n");
    }
    fprintf(f, "sum : %d\n", next_action.sum);

    fprintf(f, "\n--------------All action---------------\n");
    int i;
    rep(i, next_action.sum){
        if(next_action.next_action[i].type == MOVE){
            fprintf(f, "MOVE  ");
            if(next_action.next_action[i].move == UP){
                fprintf(f, "UP");
            }else if(next_action.next_action[i].move == RIGHT){
                fprintf(f, "RIGHT");
            }else if(next_action.next_action[i].move == LEFT){
                fprintf(f, "LEFT");
            }else if(next_action.next_action[i].move == DOWN){
                fprintf(f, "DOWN");
            }
            fprintf(f, "   : %d\n", next_action.score[i]);
        }else if(next_action.next_action[i].type == CREATE){
            fprintf(f, "CREATE  ");
            fprintf(f, "wall_");
            if(next_action.next_action[i].direction == WHITE_WALL){
                fprintf(f, "w");
            }else if(next_action.next_action[i].direction == HEIGHT_WALL){
                fprintf(f, "h");
            }
            fprintf(f, "_%d_%d   : %d\n", next_action.next_action[i].wall_point.x, next_action.next_action[i].wall_point.y, next_action.score[i]);
        }
    }
    fclose(f);
}