#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "Examine/patient.h"

// Helper: convert CaseType to string
const char* caseTypeToString(CaseType type) {
    switch (type) {
        case EMERGENCY: return "EMERGENCY";
        case NORMAL: return "NORMAL";
        case ROUTINE: return "ROUTINE";
        case CONSULTATION: return "CONSULTATION";
        default: return "UNKNOWN";
    }
}

// Helper: convert Status to string
const char* statusToString(Status status) {
    switch (status) {
        case WAITING: return "WAITING";
        case EXAMINING: return "EXAMINING";
        case FINISHED: return "FINISHED";
        default: return "UNKNOWN";
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

    // Step 3: Print
    printf("Sorted list by priority (desc) and arrival time (asc):\n");
    printf("ID       | Name                    | Birth Year | Priority       | Arrival Time         | Status\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        char timeStr[26];
        struct tm* tm_info = localtime(&array[i]->arrivalTime);
        strftime(timeStr, 26, "%Y-%m-%d %H:%M:%S", tm_info);

        printf("%-8s | %-23s | %-9d | %-14s | %-20s | %-10s\n",
               array[i]->id,
               array[i]->name,
               array[i]->year,
               caseTypeToString(array[i]->caseType),
               timeStr,
               statusToString(array[i]->status));
    }

    free(array);
}

// Search patient by name (print directly)
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
                printf("Patient(s) with name \"%s\":\n", name);
                printf("ID       | Name                    | Birth Year | Priority       | Arrival Time         | Status\n");
                printf("---------------------------------------------------------------------------------------------------\n");
            }

            char timeStr[26];
            struct tm* tm_info = localtime(&current->patient->arrivalTime);
            strftime(timeStr, 26, "%Y-%m-%d %H:%M:%S", tm_info);

            printf("%-8s | %-23s | %-9d | %-14s | %-20s | %-10s\n",
                   current->patient->id,
                   current->patient->name,
                   current->patient->year,
                   caseTypeToString(current->patient->caseType),
                   timeStr,
                   statusToString(current->patient->status));

            found = 1;
        }

        current = current->next;
    }

    if (!found) {
        printf("No patient found with name \"%s\".\n", name);
    }
}

// Search patient by ID (print directly)
void searchByID(PatientList* list, char* id) {
    if (list == NULL || list->head == NULL || id == NULL) {
        printf("Invalid input.\n");
        return;
    }

    PatientNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->patient->id, id) == 0) {
            printf("Patient with ID \"%s\":\n", id);
            printf("ID       | Name                    | Birth Year | Priority       | Arrival Time         | Status\n");
            printf("---------------------------------------------------------------------------------------------------\n");

            char timeStr[26];
            struct tm* tm_info = localtime(&current->patient->arrivalTime);
            strftime(timeStr, 26, "%Y-%m-%d %H:%M:%S", tm_info);

            printf("%-8s | %-23s | %-9d | %-14s | %-20s | %-10s\n",
                   current->patient->id,
                   current->patient->name,
                   current->patient->year,
                   caseTypeToString(current->patient->caseType),
                   timeStr,
                   statusToString(current->patient->status));
            return;
        }

        current = current->next;
    }

    printf("No patient found with ID \"%s\".\n", id);
}
