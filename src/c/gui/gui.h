#ifndef GUI_H 
#define GUI_H

static int proc(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

static int proc_init(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

int game_conversion(const GAME_DATE game_date, int *date);

int *gui_main(Tcl_Interp *interp, int action);

int gui();

#endif