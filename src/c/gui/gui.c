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
#include "./../game/wall.h"
#include "./../Strategy/random.h"
#include "./../Strategy/strategy_tool.h"
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
    if(argc != 2){
        char *retmsg = "argument:error";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("command: error\n");
        return TCL_ERROR;
    }
    
    // 引数からデータを取り出す
    int action = STAY;
    Tcl_GetIntFromObj(interp, argv[1], &action);
    ACT activity;
    activity.type = MOVE;
    activity.move = action;
    int *date = gui_main(interp, activity);

    int *list = date;
    if(list == NULL) printf("\nyabai\n");
    Tcl_Obj *listObj = Tcl_NewListObj(0, NULL);
    int i;
    rep(i, DATE){
        Tcl_ListObjAppendElement(interp, listObj, Tcl_NewIntObj(list[i]));
    }

    Tcl_SetObjResult(interp, listObj);

    return TCL_OK;
}

/**
 * @brief 独自のコマンド。gui初期化用のコマンド
 * 
 * @param ClinetDate コマンドで使用するメモリ領域
 * @param interp インタプリタ
 * @param argc 引数の個数＋１
 * @param argv 先頭は実行するコマンド、それ以降にコマンドの引数がセットされる
 * @return int 完了コード
 */
static int proc_init(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]){
    if(argc != 1){
        char *retmsg = "argument:error(init)";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("command: error\n");
        return TCL_ERROR;
    }
    
    int data[DATE] = {0};
    GAME_DATE game_data;
    init(&game_data);
    game_conversion(game_data, data);
    int *list = data;
    
    int i;
    Tcl_Obj *listObj = Tcl_NewListObj(0, NULL);
    rep(i, DATE){
        Tcl_ListObjAppendElement(interp, listObj, Tcl_NewIntObj(list[i]));
    }

    Tcl_SetObjResult(interp, listObj);

    return TCL_OK;
}

/**
 * @brief 独自のコマンド。壁生成用
 * 
 * @param ClinetDate コマンドで使用するメモリ領域
 * @param interp インタプリタ
 * @param argc 引数の個数＋１
 * @param argv 先頭は実行するコマンド、それ以降にコマンドの引数がセットされる
 * @return int 完了コード
 */
static int proc_createWall(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]){
    if(argc != 3){
        char *retmsg = "argument:error(init)";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("command: error\n");
        return TCL_ERROR;
    }

    // 引数からデータを取り出す
    char **wall_data;
    int len = 0;
    int i;
    rep(i, 2){    
        wall_data[i] = Tcl_GetStringFromObj(argv[i + 1], &len);
    }
    ACT activity = coordinate_from_tag_name(wall_data[0]); 
    activity.type = CREATE;
    gui_main(interp, activity); 
    
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
    date[num] = win_or_loss_decision(game_date);
    num++;
    return num;
}

/**
 * @brief ゲームを進める関数
 * 
 * @param interp インタプリタ
 * @param action 行動（tclからの返却値）
 * @return int ゲーム情報を配列に変換して返却
 */
int *gui_main(Tcl_Interp *interp, ACT activity){
    static GAME_DATE game_date;
    static int date[DATE] = {0};
    static int count = 0;
    static int after_flag = False;

    if(!count)
        init(&game_date);

    if(!end_decision(game_date)){
        if(after_flag){
            game_date.main_player =  BLACK_PLAYER;
            activity = random_move(game_date);
            int flag = game_main(&game_date, activity);
            if(flag) after_flag = False;
        }else{
            game_date.main_player = WHITE_PLAYER;
            after_flag = game_main(&game_date, activity);
        }
        int deep = shortest_distance(game_date, WHITE_PLAYER);
        // printf("deep = %d\n", deep);
    }

    game_data_showTextFile(game_date);

    game_conversion(game_date, date);

    int i;
    count++;

    Tcl_CreateObjCommand(interp, "game_proc", proc, NULL, NULL);
    return date;
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

    Tcl_CreateObjCommand(interp, "game_init", proc_init, NULL, NULL);
    Tcl_CreateObjCommand(interp, "game_proc", proc, NULL, NULL);
    Tcl_CreateObjCommand(interp, "create_wall", proc_createWall, NULL, NULL);


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