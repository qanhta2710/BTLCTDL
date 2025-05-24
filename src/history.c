#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"

historyList *createHistory() {
    historyList *list = (historyList *)malloc(sizeof(historyList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    return list;
}

void addVisitHistory(historyList *list, Patient *patient) {
    if (list == NULL || patient == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    historyNode *newVisit = (historyNode *)malloc(sizeof(historyNode));
    if (newVisit == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    
    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%Y%m%d%H%M%S", localtime(&patient->arrivalTime));
    sprintf(newVisit->data.visitedID, "%s_%s", patient->id, timeStr);
    
    strcpy(newVisit->data.id, patient->id);
    strcpy(newVisit->data.name, patient->name);
    newVisit->data.year = patient->year;
    newVisit->data.arrivalTime = patient->arrivalTime;
    newVisit->data.examiningStartTime = patient->examiningStartTime;
    newVisit->data.examiningEndTime = patient->examiningEndTime;

    if (list->head == NULL) {
        list->head = newVisit;
        list->tail = newVisit;
    } else {
        list->tail->next = newVisit;
        list->tail = newVisit;
    }
    printf("Added successfully\n");
}

void showHistory(historyList *list) {
    if (list == NULL) {
        printf("List is empty\n");
        return;
    }
    historyNode *current = list->head;
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    printf("| Visited ID             | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    while (current != NULL) {
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningEndTime));

        printf("| %-22s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
            current->data.visitedID,
            current->data.name,
            current->data.year,
            arrivalBuffer,
            startBuffer,
            endBuffer);
        current = current->next;
    }
}
void searchVisitHistoryByName(historyList *list, const char *name) {
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    historyNode *current = list->head;
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    printf("| Visited ID             | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            char arrivalBuffer[100], startBuffer[100], endBuffer[100];
            strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.arrivalTime));
            strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningStartTime));
            strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningEndTime));

            printf("| %-22s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
                current->data.visitedID,
                current->data.name,
                current->data.year,
                arrivalBuffer,
                startBuffer,
                endBuffer);
        }
        current = current->next;
    }
}

void freeList(historyList *list) {
    if (list == NULL) {
        return;
    }
    historyNode *current = list->head;
    while (current != NULL) {
        historyNode *tmp = current;
        current = current->next;
        free(tmp);
    }
    free(list);
}