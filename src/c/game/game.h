#ifndef GAME_H 
#define GAME_H

int end_decision(const GAME_DATE game_date);

POINT act_conversion(int act);

int outside_player(POINT point);

int player_check(POINT point, const GAME_DATE game_date);

int check_NotWall_way(const GAME_DATE *game_date, POINT now, POINT next, int move_type);

int game_main(GAME_DATE *game_date, ACT activity);

int create_wall(GAME_DATE *game_date, ACT activity);

#endif