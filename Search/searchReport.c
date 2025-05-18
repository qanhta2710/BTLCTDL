#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Examine/patient.h"

// Helper: convert CaseType to string (lowercase)
const char* caseTypeToString(CaseType type) {
    switch (type) {
        case EMERGENCY: return "Emergency";
        case NORMAL: return "Normal";
        case ROUTINE: return "Routine";
        case CONSULTATION: return "Consultation";
        default: return "Unknown";
    }
}

// Helper: convert Status to string (lowercase)
const char* statusToString(Status status) {
    switch (status) {
        case WAITING: return "Waiting";
        case EXAMINING: return "Examining";
        case FINISHED: return "Finished";
        default: return "Unknown";
    }
}

// List patients sorted by priority (high to low), and within same priority, by earliest arrival time
void listPatientsByPriority(PatientList* list) {
    if (list == NULL || list->head == NULL) {
        printf("The patient list is empty.\n");
        return;
    }

    // Step 1: Copy to array
    int count = 0;
    PatientNode* current = list->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }

    Patient** array = (Patient**)malloc(sizeof(Patient*) * count);
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    current = list->head;
    for (int i = 0; i < count; i++) {
        array[i] = current->patient;
        current = current->next;
    }

    // Step 2: Sort (Bubble sort) by priority and arrivalTime
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            int pri_i = array[i]->caseType;
            int pri_j = array[j]->caseType;

            if (pri_i > pri_j || (pri_i == pri_j && array[i]->arrivalTime > array[j]->arrivalTime)) {
                Patient* temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }

    // Step 3: Print with UI format
    printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
    printf("| ID         | Name                 | Birth Year | Status     | Arrival Time        | Case Type      | Examining Time      | Finished Time       |\n");
    printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");

    for (int i = 0; i < count; i++) {
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&array[i]->arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&array[i]->examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&array[i]->examiningEndTime));

        printf("| %-10s | %-20s | %-10d | %-10s | %-19s | %-14s | %-19s | %-19s |\n",
               array[i]->id,
               array[i]->name,
               array[i]->year,
               statusToString(array[i]->status),
               arrivalBuffer,
               caseTypeToString(array[i]->caseType),
               array[i]->examiningStartTime == 0 ? "Not started" : startBuffer,
               array[i]->examiningEndTime == 0 ? "Not finished" : endBuffer);
    }
    printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");

    free(array);
}

// Search patient by name (print directly with UI format)
void searchByName(PatientList* list, char* name) {
    if (list == NULL || list->head == NULL || name == NULL) {
        printf("Invalid input.\n");
        return;
    }

    int found = 0;
    PatientNode* current = list->head;
    
    while (current != NULL) {
        if (strcmp(current->patient->name, name) == 0) {
            if (!found) {
                printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
                printf("| ID         | Name                 | Birth Year | Status     | Arrival Time        | Case Type      | Examining Time      | Finished Time       |\n");
                printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
            }

            char arrivalBuffer[100], startBuffer[100], endBuffer[100];
            strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->patient->arrivalTime));
            strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->patient->examiningStartTime));
            strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->patient->examiningEndTime));

            printf("| %-10s | %-20s | %-10d | %-10s | %-19s | %-14s | %-19s | %-19s |\n",
                   current->patient->id,
                   current->patient->name,
                   current->patient->year,
                   statusToString(current->patient->status),
                   arrivalBuffer,
                   caseTypeToString(current->patient->caseType),
                   current->patient->examiningStartTime == 0 ? "Not started" : startBuffer,
                   current->patient->examiningEndTime == 0 ? "Not finished" : endBuffer);

            found = 1;
        }
        current = current->next;
    }

    if (found) {
        printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
    } else {
        printf("No patient found with name \"%s\".\n", name);
    }
}

// Search patient by ID (return Patient* if found, NULL otherwise)
Patient* searchByID(PatientList* list, char* id) {
    if (list == NULL || list->head == NULL || id == NULL) {
        return NULL;
    }

    PatientNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->patient->id, id) == 0) {
            return current->patient;
        }
        current = current->next;
    }

    return NULL;
}