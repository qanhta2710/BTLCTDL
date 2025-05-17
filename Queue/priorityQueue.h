#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "patient.h"

#define MAX_PATIENTS 100

typedef struct {
    Patient* data[MAX_PATIENTS];
    int size;
} PriorityQueue;

// Khoi tao hang doi
void initQueue(PriorityQueue* pq);

// Kiem tra hang doi rong
int isEmpty(PriorityQueue* pq);

// Them benh nhan vao hang doi
void enqueue(PriorityQueue* pq, Patient* p);

// Lay benh nhan uu tien cao nhat
Patient* dequeue(PriorityQueue* pq);

// Hien thi hang doi hien tai
void showQueue(PriorityQueue* pq);

#endif
