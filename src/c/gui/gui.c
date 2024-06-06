/**
 * @file gui.c
 * @author okajima
 * @brief guiを表示する
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdio.h>
#include <tcl.h>
#include <tk.h>
#include <stdlib.h>
#include "./../set.h"
#include "gui.h"
#include "./../game/init.h"
#include "./../game/game.h"
#include "./../prog/print_value.h"

/**
 * @brief 独自のコマンド。ゲームの情報を送信する
 * 
 * @param ClinetDate コマンドで使用するメモリ領域
 * @param interp インタプリタ
 * @param argc 引数の個数＋１
 * @param argv 先頭は実行するコマンド、それ以降にコマンドの引数がセットされる
 * @return int 完了コード
 */
static int proc(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]){

    if(argc != 1){
        char *retmsg = "argument:error";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("command: error\n");
        return TCL_ERROR;
    }

    int *list = (int *)ClientData;
    if(list == NULL) printf("\nyabai\n");
    Tcl_Obj *listObj = Tcl_NewListObj(0, NULL);
    int i;
    rep(i, DATE) printf("%d ", list[i]);
    rep(i, DATE){
        Tcl_ListObjAppendElement(interp, listObj, Tcl_NewIntObj(list[i]));
    }

    gui_main(interp);

    Tcl_SetObjResult(interp, listObj);

    return TCL_OK;
}

/**
 * @brief tclファイルに送信するデータを作成
 * 
 * @param game_date ゲーム情報
 * @param date 送信データ
 * @return int データの要素数
 */
int game_conversion(const GAME_DATE game_date, int *date){
    int y, x;
    int i;
    date[0] = game_date.turn;
    date[1] = game_date.main_player;
    date[2] = SUM_CELL_H;
    date[3] = SUM_CELL_W;
    date[4] = SUM_PLAYER_NUMBER;
    rep(i, SUM_PLAYER_NUMBER){
        date[i * 3 + 5] = game_date.player[i+1].position.x;
        date[i * 3 + 6] = game_date.player[i+1].position.y;
        date[i * 3 + 7] = game_date.player[i+1].wall_num;
    }
    date[3 * SUM_PLAYER_NUMBER + 5] = game_date.board.num_wall;
    int num = 3 * SUM_PLAYER_NUMBER + 6;
    rep(y, SUM_CELL_H+1){
        rep(x, SUM_CELL_W){
            date[num] = game_date.board.wall_h[y][x];
            num++;
        }
    }
    rep(y, SUM_CELL_H){
        rep(x, SUM_CELL_W + 1){
            date[num] = game_date.board.wall_w[y][x];
            num++;
        }
    }
    return num;
}

/**
 * @brief ゲームを進める関数
 * 
 * @param interp インタプリタ
 */
void gui_main(Tcl_Interp *interp){
    static GAME_DATE game_date;
    static int count = 0;
    static int date[DATE] = {0};

    if(!count)
        init(&game_date);
    
    game_date.main_player = WHITE_PLAYER;
    ACT activity;
    activity.type = MOVE;
    activity.move = UP;
    
    printf("game date number : %d\n",game_conversion(game_date, date));
    
    game_main(&game_date, activity);
    display_table(game_date.board.player, SUM_CELL_H, SUM_CELL_W);

    //game_free(&game_date);
    count++;
    printf("%d\n",count);
    if(count == 10) game_free(&game_date);
    int i;

    Tcl_CreateObjCommand(interp, "game_proc", proc, (ClientData)date, NULL);
}

/**
 * @brief guiを表示する（メイン）
 * 
 * @param game_date ゲーム情報
 * @return int エラーの場合、-1を返す
 */
int gui(){

    // gui
    Tcl_Interp *interp = Tcl_CreateInterp();  // インタプリタを作成

    if(Tcl_Init(interp) == TCL_ERROR){   // tclを初期化（スタンダードライブラリinit.tclをロード）
        const char *errmsg = Tcl_GetStringResult(interp);  // エラーメッセージを取得
        printf("Interpreter initialization fails : %s\n", errmsg);
        return -1;
    }

    if(Tk_Init(interp) == TCL_ERROR) {  // tkを初期化（ＧＵＩライブラリをロード）
        const char *errmsg = Tcl_GetStringResult(interp);  // エラーメッセージを取得
        printf("GUI initialization fails : %s\n ", errmsg);
        return -1;
    }

    gui_main(interp);

    if(Tcl_EvalFile(interp, "./src/c/gui/game.tcl") == TCL_ERROR){  // インタプリタを実行
        const char *errmsg = Tcl_GetStringResult(interp);  // エラーメッセージを取得
        printf("Execution Failure: Error Description : %s\n", errmsg);
        return -1;
    }else{
        const char *errmsg = Tcl_GetStringResult(interp);
        printf("success! : %s\n", errmsg);
    }

    Tk_MainLoop();
    Tcl_DeleteInterp(interp);  // インタプリタを片付ける

}