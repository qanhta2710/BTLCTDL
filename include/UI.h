#ifndef UI_h
#define UI_h

#include "patient.h"
#include "priorityQueue.h"
#include "history.h"

void displayMenu();
void processUserInput(PatientList *list, PriorityQueue *pq, historyList *history);
void clearScreen();

#endif