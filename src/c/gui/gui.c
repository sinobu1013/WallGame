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
#include <tk.h>
#include <stdlib.h>
#include "./../set.h"


/**
 * @brief guiを表示する（メイン）
 * 
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