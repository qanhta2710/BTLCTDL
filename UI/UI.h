#ifndef UI_h
#define UI_h

#include "Examine/patient.h"
#include "Queue/priorityQueue.h"
#include "History/history.h"

void displayMenu();
void processUserInput(PatientList *list, PriorityQueue *pq, historyList *history);
void clearScreen();

#endif