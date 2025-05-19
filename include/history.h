#ifndef HISTORY_H
#define HISTORY_H

#include <time.h>
#include "patient.h"

typedef struct History {
    char visitedID[50];
    char id[10];
    char name[255];
    int year;
    time_t arrivalTime;
    time_t examiningStartTime;
    time_t examiningEndTime;
} History;

typedef struct historyNode {
    History data;
    struct historyNode *next;
} historyNode;

typedef struct historyList {
    historyNode *head;
} historyList;

historyList *createHistory();
void addVisitHistory(historyList *list, Patient *patient);
void showVisitHistoryByName(historyList *list, const char *name);
void freeList(historyList *list);
void showHistory(historyList *list);

#endif