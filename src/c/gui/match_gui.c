/**
 * @file match_gui.c
 * @author okajima
 * @brief CPU vs CPUのGUI対戦用
 * @version 0.1
 * @date 2025-05-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <tcl.h>
#include <tk.h>
#include "./../set.h"
#include "./../game/game.h"
#include "./../game/init.h"
#include "match_gui.h"
#include "gui.h"

ACT (*firstStrategy)(GAME_DATE);
ACT (*secondStrategy)(GAME_DATE);

/**
 * @brief ゲームの初期化用のコマンド
 * 
 * @param ClientData コマンドで使用するメモリ領域
 * @param interp インタプリタ
 * @param argc 引数の個数＋１
 * @param argv 先頭は実行するコマンド、それ以降にコマンドの引数がセットされる
 * @return int 完了コード
 */
static int match_gui_init(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]){
    if(argc != 1) {
        char *retmsg = "match gui : argument : error(init)";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("match gui : match_gui_init : command : error\n");
        return TCL_ERROR;
    }

    // 初期化用のデータを作成
    int data[DATE] = {0};
    GAME_DATE game_data;
    init(&game_data);
    game_conversion(game_data, data);

    int i;
    int *list = data;
    Tcl_Obj *listObj = Tcl_NewListObj(0, NULL);
    rep(i, DATE) {
        Tcl_ListObjAppendElement(interp, listObj, Tcl_NewIntObj(list[i]));
    }
    
    Tcl_SetObjResult(interp, listObj);
    return TCL_OK;
}


/**
 * @brief ゲーム情報用のコマンド
 * 
 * @param ClientData 
 * @param interp 
 * @param argc 
 * @param argv 
 * @return int 
 */
static int match_gui_data(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]){
    if(argc != 1) {
        char *retmsg = "match gui : argument : error(init)";
        Tcl_SetResult(interp, retmsg, TCL_VOLATILE);
        printf("match gui : match_gui_init : command : error\n");
        return TCL_ERROR;
    }

    // 初期化用のデータを作成
    int *data = match_gui_main(interp);

    int i;
    int *list = data;
    Tcl_Obj *listObj = Tcl_NewListObj(0, NULL);
    rep(i, DATE) {
        Tcl_ListObjAppendElement(interp, listObj, Tcl_NewIntObj(list[i]));
    }
    
    Tcl_SetObjResult(interp, listObj);
    return TCL_OK;
}


/**
 * @brief CPU vs CPUの対戦を進める関数（中心）
 * 
 * @param interp インタプリタ
 * @return int* ゲーム情報を配列に変換して返却
 */
int *match_gui_main(Tcl_Interp *interp) {
    static GAME_DATE game_data;
    static int data[DATE] = {0};
    static int turn = 0;
    static int after_flag = True;

    // ゲームの初期化
    if(!turn) {
        init(&game_data);
        game_data.main_player = BLACK_PLAYER;
    }

    // ゲーム
    if(!end_decision(game_data)) {
        if(after_flag) {
            ACT action;
            if(game_data.main_player == BLACK_PLAYER) {
                game_data.main_player = WHITE_PLAYER;
                action = firstStrategy(game_data);
            } else if(game_data.main_player == WHITE_PLAYER) {
                game_data.main_player = BLACK_PLAYER;
                action = secondStrategy(game_data);
            }
            after_flag = game_main(&game_data, action);
        } else {    // ゲーム失敗（戦略の開発ミス）
            printf("BAGU!!!!!!!!!!!!!!!!\n");
        }
    }

    game_conversion(game_data, data);
    turn++;
    Tcl_CreateObjCommand(interp, "match_data", match_gui_data, NULL, NULL);
    return data;
}


 /**
  * @brief CPU vs CPUの対戦用関数（GUIバージョン）
  * 
  * @param fStrategy 先手の戦略アルゴリズム
  * @param sStrategy 後手の戦略アルゴリズム
  * @return int 成功かどうかのフラグ（使用していない）
  */
int match_gui(ACT (*fStrategy)(GAME_DATE), ACT (*sStrategy)(GAME_DATE)){
    firstStrategy = fStrategy;
    secondStrategy = sStrategy;

    // gui
    Tcl_Interp *interp = Tcl_CreateInterp();    // インタプリタを作成

    if(Tcl_Init(interp) == TCL_ERROR) {     // tclを初期化（スタンダードライブラリinit.tclをロード）
        const char *errmsg = Tcl_GetStringResult(interp);   // エラーメッセージを取得
        printf("match gui: Interpreter initialization fails : %s\n", errmsg);
        return -1;
    }

    if(Tk_Init(interp) == TCL_ERROR) {      // tkを初期化（GUIライブラリをロード）
        const char *errmsg = Tcl_GetStringResult(interp);   // エラーメッセージを取得
        printf("match gui: GUI initialization fails : %s\n", errmsg);
        return -1;
    }

    // コマンドを作成
    Tcl_CreateObjCommand(interp, "game_init", match_gui_init, NULL, NULL);
    Tcl_CreateObjCommand(interp, "match_data", match_gui_data, NULL, NULL);

    if(Tcl_EvalFile(interp, "c:/WallGame/src/c/gui/match.tcl") == TCL_ERROR) {  // インタプリタを実行
        const char *errmsg = Tcl_GetStringResult(interp);   // エラーメッセージ取得
        printf("match gui : Execution Failure: Error Description : %s\n", errmsg);
        return -1;
    } else {    // 成功！
        const char *errmsg = Tcl_GetStringResult(interp);
        printf("\nsuccess ! : %s\n", errmsg);
    }

    Tk_MainLoop();
    Tcl_DeleteInterp(interp);   // インタプリタを片付ける
}
