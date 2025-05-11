#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Examine/patient.h"
#include <stdbool.h>

typedef struct PriorityQueue {
    Patient **patient;
    int size; // Kích thước hiện tại 
    int capacity; // Kích thước tối đa
} PriorityQueue;

PriorityQueue *createPriorityQueue(); // Tạo với kích thước tối đa mặc định là 1000
void enqueue(PriorityQueue *pq, Patient *patient);
Patient *dequeue(PriorityQueue *pq);
bool isEmpty(PriorityQueue *pq); // Kiểm tra hàng đợi có rỗng không (nếu không dùng đến thì bỏ hàm này)
void freePriorityQueue(PriorityQueue *pq);

// Có ý tưởng gì thì bổ sung thêm đây chỉ là các hàm cơ bản
#endif