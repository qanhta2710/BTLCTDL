#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Examine/patient.h"
typedef struct PriorityQueue {
    Patient **patient;
    int size; // kich thuoc hien tai
    int capacity; // kich thuoc toi da
} PriorityQueue;

#endif