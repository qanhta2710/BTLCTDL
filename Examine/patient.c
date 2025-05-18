#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Examine/patient.h"

Patient *newPatient(char *id, char *name, int year, CaseType caseType) {
    Patient *patient = (Patient *)malloc(sizeof(Patient));
    if (patient == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    strncpy(patient->id, id, sizeof(patient->id) - 1);
    patient->id[sizeof(patient->id) - 1] = '\0';

    strncpy(patient->name, name, sizeof(patient->name) - 1);
    patient->name[sizeof(patient->name) - 1] = '\0';

    patient->year = year;
    patient->status = WAITING;
    patient->arrivalTime = time(NULL);
    patient->examiningStartTime = 0;
    patient->examiningEndTime = 0;
    patient->caseType = caseType;

    return patient;
}

void addPatient(PatientList *list, Patient *patient) {
    PatientNode *newNode = (PatientNode *)malloc(sizeof(PatientNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->patient = patient;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        PatientNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return;
}

PatientList *createPatientList() {
    PatientList *list = (PatientList *)malloc(sizeof(PatientList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    return list;
}

void freePatientList(PatientList *list) {
    if (list == NULL) {
        return;
    }
    PatientNode *current = list->head;
    while (current != NULL) {
        PatientNode *tmp = current;
        current = current->next;
        free(tmp->patient);
        free(tmp);
    }
    free(list);
    return;
}
