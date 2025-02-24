#ifndef STRATEGY_TOOL_H
#define STRATEGY_TOOL_H

/**
 * @brief 選択可能な次の手
 * 
 */
typedef struct{
    int sum;                    /**< とれる手のパターン数 */
    ACT next_action[DATE];      /**< 具体的な行動 */
    int score[DATE];            /**< その手を取った場合の得点 */
}NEXT_ACTION;

int  GetScore(const GAME_DATE game_date, int player);

BOOL copy_game_date(GAME_DATE *main, const GAME_DATE sub);

NEXT_ACTION all_next_action(GAME_DATE game_date, int player);

void calculate_all_next_action(GAME_DATE game_date, int player, NEXT_ACTION *next_action);

ACT max_score_action(NEXT_ACTION next_action);

#endif