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
#include "match_gui.h"

int match_gui(void){

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
