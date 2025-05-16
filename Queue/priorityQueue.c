#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define MAX_PATIENTS 100

typedef enum {
    NOT_EXAMINED,
    EXAMINING,
    EXAMINED
} Status;

typedef enum {
    EMERGENCY = 1,
    NORMAL = 2,
    ROUTINE = 3,
    CONSULTATION = 4
} CaseType;

typedef struct {
    char id[10];
    char name[50];
    int year;
    Status status;
    time_t arrivalTime;
    CaseType caseType;
    time_t examiningStartTime;
    time_t examiningEndTime;
} Patient;

typedef struct {
    Patient* data[MAX_PATIENTS];
    int size;
} PriorityQueue;

void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

int comparePatients(Patient* a, Patient* b) {
    if (a->caseType == b->caseType)
        return a->arrivalTime > b->arrivalTime;
    return a->caseType > b->caseType;
}

void enqueue(PriorityQueue* pq, Patient* p) {
    if (pq->size >= MAX_PATIENTS) {
        printf("Warning: queue is full!\n");
        return;
    }

    pq->data[pq->size++] = p;

    for (int i = pq->size - 1; i > 0 && comparePatients(pq->data[i - 1], pq->data[i]); --i) {
        Patient* temp = pq->data[i];
        pq->data[i] = pq->data[i - 1];
        pq->data[i - 1] = temp;
    }

    printf("Added: %s | Priority: %d | Arrival: %s", p->name, p->caseType, ctime(&(p->arrivalTime)));
}

Patient* dequeue(PriorityQueue* pq) {
    if (pq->size == 0) {
        printf("Warning: queue is empty.\n");
        return NULL;
    }

    Patient* p = pq->data[0];
    for (int i = 1; i < pq->size; ++i) {
        pq->data[i - 1] = pq->data[i];
    }
    pq->size--;

    p->status = EXAMINING;
    p->examiningStartTime = time(NULL);

    printf("\nExamining: %s | Start: %s", p->name, ctime(&(p->examiningStartTime)));

    sleep(2); // simulate

    p->examiningEndTime = time(NULL);
    p->status = EXAMINED;

    printf("Finished: %s\n", ctime(&(p->examiningEndTime)));

    return p;
}

void showQueue(PriorityQueue* pq) {
    printf("\nQueue (%d patients):\n", pq->size);
    for (int i = 0; i < pq->size; ++i) {
        Patient* p = pq->data[i];
        const char* statusStr = p->status == NOT_EXAMINED ? "Not examined" :
                                p->status == EXAMINING ? "Being examined" : "Examined";

        printf("- %s | ID: %s | Priority: %d | Status: %s | Arrival: %s",
               p->name, p->id, p->caseType, statusStr, ctime(&(p->arrivalTime)));
    }
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);

    Patient* p1 = malloc(sizeof(Patient));
    strcpy(p1->id, "BN01");
    strcpy(p1->name, "Nguyen Van A");
    p1->year = 1980;
    p1->status = NOT_EXAMINED;
    p1->caseType = EMERGENCY;
    p1->arrivalTime = time(NULL);
    enqueue(&pq, p1);

    sleep(1);

    Patient* p2 = malloc(sizeof(Patient));
    strcpy(p2->id, "BN02");
    strcpy(p2->name, "Tran Thi B");
    p2->year = 1992;
    p2->status = NOT_EXAMINED;
    p2->caseType = NORMAL;
    p2->arrivalTime = time(NULL);
    enqueue(&pq, p2);

    sleep(1);
    
    Patient* p3 = malloc(sizeof(Patient));
    strcpy(p3->id, "BN03");
    strcpy(p3->name, "Le Van C");
    p3->year = 1985;
    p3->status = NOT_EXAMINED;
    p3->caseType = ROUTINE;
    p3->arrivalTime = time(NULL);
    enqueue(&pq, p3);

    sleep(1);

    Patient* p4 = malloc(sizeof(Patient));
    strcpy(p4->id, "BN04");
    strcpy(p4->name, "Pham Van D");
    p4->year = 2000;
    p4->status = NOT_EXAMINED;
    p4->caseType = CONSULTATION;
    p4->arrivalTime = time(NULL);
    enqueue(&pq, p4);

    showQueue(&pq);

    while (1) {
        Patient* done = dequeue(&pq);
        if (done == NULL) break;
    }

    free(p1);
    free(p2);
    free(p3);
    free(p4);

    return 0;
}
