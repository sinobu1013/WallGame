#ifndef GAME_H 
#define GAME_H

int end_decision(const GAME_DATE game_date);

int game_main(GAME_DATE *game_date, ACT activity);

int create_wall(GAME_DATE *game_date, ACT activity);

#endif