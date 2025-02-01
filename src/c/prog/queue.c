/**
 * @file queue.c
 * @author okajima
 * @brief キュー
 * @version 0.1
 * @date 2025-02-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

/**
 * @brief キューを作成用関数（初期化用）
 * 
 * @return QUEUE* 作成したキューを返す
 */
QUEUE CreateQueue(void){
    QUEUE queue;
    queue.top = NULL;
    queue.end = NULL;
    return queue;
}

/**
 * @brief キューのデータを開放する
 * 
 * @param data キューのデータ
 */
void FreeQueue(Qdata *data){
    free(data);
}

/**
 * @brief エンキュー
 * 
 * @param queue キュー本体
 * @param data 入れるデータ
 * @param size 入れるデータのサイズ
 */
void EnQueue(QUEUE *queue, void *data, size_t size){
    Qdata *tmp = (Qdata*)malloc(sizeof(Qdata));
    tmp->data = malloc(size);
    if(tmp->data == NULL){
        perror("Enqueue malloc failed");
        return;
    }
    tmp->data = data;
    tmp->next = NULL;
    if(queue->end == NULL){
        queue->end = tmp;
        queue->top = tmp;
    }else{
        queue->end->next = tmp;
        queue->end = tmp;
    }
}

/**
 * @brief デキュー（戻り値は開放する必要あり）
 * 
 * @param queue キュー本体
 * @param size キューのデータのサイズ（戻り値のサイズ）
 * @return void* キューのデータ
 */
void *DeQueue(QUEUE *queue, size_t size){
    Qdata *tmp = (Qdata*)malloc(size);
    if(tmp->data == NULL){
        perror("Dequeue malloc failed");
        return NULL;
    }
    if(queue->top == NULL){
        queue->end = NULL;
        return NULL;
    }
    *tmp = *queue->top;
    Qdata *tmp_free = queue->top;
    queue->top = tmp_free->next;
    free(tmp_free->data);
    free(tmp_free);
    if(queue->top == NULL) queue->end = NULL;
    return tmp->data;
}
