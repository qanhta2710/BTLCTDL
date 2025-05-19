#ifndef SEARCH_REPORT_H
#define SEARCH_REPORT_H

#include "patient.h"

void searchByName(PatientList* list, char* name);
Patient* searchByID(PatientList* list, char* id);
void showAllPatients(PatientList* list);

#endif