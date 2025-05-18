#ifndef UI_h
#define UI_h

#include "Examine/patient.h"
#include "Queue/priorityQueue.h"

void displayMenu();
void processUserInput(PatientList *list, PriorityQueue *pq);
void clearScreen();
static const char *getCaseTypeName(CaseType caseType);
static const char *getStatusName(Status status);

#endif