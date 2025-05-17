#ifndef PRINT_VALUE_H
#define PRINT_VALUE_H

void display_table(int **board, int h, int w);

void game_data_showTextFile(const GAME_DATE game_data);

void try_print_game_date(const GAME_DATE game_date);

void print_next_action(NEXT_ACTION next_action, int player);

void matchResult_print(GAME_RESULT result);

#endif