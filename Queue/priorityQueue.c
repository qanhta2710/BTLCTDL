#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityQueue.h"
#include <stdbool.h>

static const char *getCaseTypeName(CaseType caseType) {
    switch (caseType) {
        case EMERGENCY: 
            return "Emergency";
        case NORMAL:
            return "Normal";
        case ROUTINE:
            return "Routine";
        case CONSULTATION:
            return "Consultation";
        default:
            return "Invalid";
    }
}

static const char *getStatusName(Status status) {
    switch (status) {
        case WAITING:
            return "Waiting";
        case EXAMINING:
            return "Examining";
        case FINISHED:
            return "Finished";
        default:
            return "Invalid";
    }
}

static int compare(Patient* a, Patient* b) {
    if (a->caseType != b->caseType)
        return a->caseType - b->caseType;
    return (int)difftime(a->arrivalTime, b->arrivalTime);
}

static void swap(Patient** a, Patient** b) {
    Patient* tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapifyUp(PriorityQueue* pq, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare(pq->data[idx], pq->data[parent]) < 0) {
            swap(&pq->data[idx], &pq->data[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

static void heapifyDown(PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2*idx + 1;
    int right = 2*idx + 2;

    if (left < pq->size && compare(pq->data[left], pq->data[smallest]) < 0)
        smallest = left;
    if (right < pq->size && compare(pq->data[right], pq->data[smallest]) < 0)
        smallest = right;

    if (smallest != idx) {
        swap(&pq->data[idx], &pq->data[smallest]);
        heapifyDown(pq, smallest);
    }
}

void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

bool isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

void enqueue(PriorityQueue* pq, Patient* p) {
    if (pq->size >= MAX_PATIENTS) {
        printf("Queue is full\n");
        return;
    }
    pq->data[pq->size] = p;
    heapifyUp(pq, pq->size);
    pq->size++;
    printf("Added: %s | ID: %s\n", p->name, p->id);
}

Patient* dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Queue is empty.\n");
        return NULL;
    }
    Patient* top = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    return top;
}

void showQueue(PriorityQueue* pq) {
    printf("%d Patients Waiting:\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        Patient* p = pq->data[i];
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&p->arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&p->examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&p->examiningEndTime));

        printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
        printf("| ID         | Name                 | Birth Year | Status     | Arrival Time        | Case Type      | Examining Time      | Finished Time       |\n");
        printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
        printf("| %-10s | %-20s | %-10d | %-10s | %-19s | %-14s | %-19s | %-19s |\n",
            p->id,
            p->name,
            p->year,
            getStatusName(p->status),
            arrivalBuffer,
            getCaseTypeName(p->caseType),
            p->examiningStartTime == 0 ? "Not started" : startBuffer,
            p->examiningEndTime == 0 ? "Not finished" : endBuffer);
        printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
    }
}