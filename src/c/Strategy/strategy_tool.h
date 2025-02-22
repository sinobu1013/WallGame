#ifndef STRATEGY_TOOL_H
#define STRATEGY_TOOL_H

/**
 * @brief 選択可能な次の手
 * 
 */
typedef struct{
    int sum;                    /**< とれる手のパターン数 */
    ACT next_action[DATE];      /**< 具体的な行動 */
}NEXT_ACTION;

BOOL copy_game_date(GAME_DATE *main, const GAME_DATE sub);

#endif