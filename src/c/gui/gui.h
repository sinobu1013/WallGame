#ifndef GUI_H 
#define GUI_H

static int proc(ClientData ClientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[]);

int *gui_main(Tcl_Interp *interp, int action);

int gui();

#endif