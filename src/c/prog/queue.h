#ifndef QUEUE_H
#define QUEUE_H

/**
 * @brief キューのノード
 * 
 */
typedef struct QueueData{
    void *data;         // データ用のポインタ
    struct QueueData *next;    // 次のデータのポインタ
}Qdata;

/**
 * @brief キュー用の構造体
 * 
 */
typedef struct{
    Qdata *top;         // 取り出すところ
    Qdata *end;         // 入れるところ
}QUEUE;

QUEUE CreateQueue(void);

void FreeQueue(Qdata *data);

void EnQueue(QUEUE *queue, void *data, size_t size);

void *DeQueue(QUEUE *queue, size_t size);


#endif