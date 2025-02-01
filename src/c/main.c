/**
 * @file main.c
 * @author okajima
 * @brief main関数
 * @version 0.1
 * @date 2024-06-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include "set.h"
#include "./game/init.h"
#include "./prog/print_value.h"
#include "./prog/queue.h"
#include "./game/game.h"
#include "./gui/gui.h"


/**
 * @brief main関数
 * 
 * @return int 実行成功判定
 */
int main(void){
    // gui();
    QUEUE queue = CreateQueue();
    int a[N] = {0};
    int i = 0;
    while(1){
        printf("%d : ", i);
        scanf("%d", &a[i]);
        if(a[i] == -1) break;
        if(a[i] == 0){
            int *x = (int*)DeQueue(&queue, sizeof(int*));
            if(x == NULL) break;
            printf("x : %d\n", *x);
            free(x);
            continue;
        }
        EnQueue(&queue, &a[i], sizeof(int*));
        i++;
    }
    printf("end");
    return 0;
}