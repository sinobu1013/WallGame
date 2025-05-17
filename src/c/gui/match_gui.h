#ifndef MATCH_GUI_H
#define MATCH_GUI_H

int *match_gui_main(Tcl_Interp *interp);

int match_gui(ACT (*fStrategy)(GAME_DATE), ACT (*sStrategy)(GAME_DATE));

 #endif