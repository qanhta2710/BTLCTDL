#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Examine/patient.h"
#include <stdbool.h>
#define MAX_PATIENTS 1000 // MAX_SIZE

typedef struct {
    Patient* data[MAX_PATIENTS];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue* pq);
bool isEmpty(PriorityQueue* pq);
void enqueue(PriorityQueue* pq, Patient* p);
Patient* dequeue(PriorityQueue* pq);
void showQueue(PriorityQueue* pq);
static const char *getCaseTypeName(CaseType caseType);
static const char *getStatusName(Status status);

#endif