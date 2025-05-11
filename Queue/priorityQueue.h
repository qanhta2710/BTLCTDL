#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Examine/patient.h"
typedef struct PriorityQueue {
    Patient **patient;
    int size; // Kích thước hiện tại 
    int capacity; // Kích thước tối đa
} PriorityQueue;

#endif