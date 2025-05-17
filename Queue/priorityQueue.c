#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priorityqueue.h"

// Ham noi bo: so sanh hai benh nhan theo uu tien (caseType)
// Uu tien: caseType nho hon -> uu tien cao hon
// Neu caseType bang nhau -> benh nhan den som hon uu tien hon
static int compare(Patient* a, Patient* b) {
    if (a->caseType != b->caseType)
        return a->caseType - b->caseType;
    return (int)difftime(a->arrivalTime, b->arrivalTime);
}

// Ham noi bo: doi cho vi tri trong heap
static void swap(Patient** a, Patient** b) {
    Patient* tmp = *a;
    *a = *b;
    *b = tmp;
}

// Ham noi bo: dieu chinh len tren khi them phan tu
static void heapifyUp(PriorityQueue* pq, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (compare(pq->data[idx], pq->data[parent]) < 0) {
            swap(&pq->data[idx], &pq->data[parent]);
            idx = parent;
        } else break;
    }
}

// Ham noi bo: dieu chinh xuong duoi khi lay phan tu ra
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

// Ham public: khoi tao hang doi
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Ham public: kiem tra hang doi rong
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Ham public: them benh nhan vao hang doi
void enqueue(PriorityQueue* pq, Patient* p) {
    if (pq->size >= MAX_PATIENTS) {
        printf("Hang doi day!\n");
        return;
    }
    pq->data[pq->size] = p;
    heapifyUp(pq, pq->size);
    pq->size++;
    printf("Da them: %s | ID: %s\n", p->name, p->id);
}

// Ham public: lay benh nhan uu tien cao nhat ra khoi hang doi
Patient* dequeue(PriorityQueue* pq) {
    if (isEmpty(pq)) {
        printf("Hang doi rong.\n");
        return NULL;
    }
    Patient* top = pq->data[0];
    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;
    heapifyDown(pq, 0);
    printf("Lay ra: %s | ID: %s\n", top->name, top->id);
    return top;
}

// Ham public: hien thi tat ca benh nhan trong hang doi
void showQueue(PriorityQueue* pq) {
    printf("Hang doi (%d benh nhan):\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        Patient* p = pq->data[i];
        const char* statusStr = p->status == NOT_EXAMINED ? "Chua kham"
                                : p->status == EXAMINING ? "Dang kham"
                                : "Da kham";
        printf("- %s | ID: %s | Uu tien: %d | Trang thai: %s | Thoi gian den: %s",
               p->name, p->id, p->caseType, statusStr, ctime(&p->arrivalTime));
    }
}
