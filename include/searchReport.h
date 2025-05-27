#ifndef SEARCH_REPORT_H
#define SEARCH_REPORT_H

#include "patient.h"
#include "history.h"

void searchByIDCard(PatientList* list, char* IDCard);
Patient* searchByID(PatientList* list, char* id);
void showAllPatients(PatientList* list);
void searchVisitHistoryByIDCard(historyList *list, const char *IDCard);

#endif