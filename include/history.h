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
    historyNode *tail;
} historyList;

historyList *createHistory();
void addVisitHistory(historyList *list, Patient *patient);
void searchVisitHistoryByName(historyList *list, const char *name);
void freeList(historyList *list);
void showHistory(historyList *list);
void saveHistoryToFile(History *history, const char *filename);
historyList *loadHistoryFromFile(const char *filename);

#endif