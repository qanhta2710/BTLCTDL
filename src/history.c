#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "history.h"

//Them mot ban ghi kham benh vao danh sach
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

//Hien thi lich su kham 
void showHistory(historyList *list) {
    if (list == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // Open file for writing
    FILE *file = fopen("History.txt", "w");
    if (file == NULL) {
        printf("Failed to create History.txt file\n");
    }
    
    historyNode *current = list->head;
    
    // Print to console
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    printf("| Visited ID             | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    
    // Write to file
    if (file != NULL) {
        fprintf(file, "+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
        fprintf(file, "| Visited ID             | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
        fprintf(file, "+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    }
    
    while (current != NULL) {
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningEndTime));

        // Print to console
        printf("| %-22s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
            current->data.visitedID,
            current->data.name,
            current->data.year,
            arrivalBuffer,
            startBuffer,
            endBuffer);
            
        // Write to file
        if (file != NULL) {
            fprintf(file, "| %-22s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
                current->data.visitedID,
                current->data.name,
                current->data.year,
                arrivalBuffer,
                startBuffer,
                endBuffer);
        }
        
        current = current->next;
    }
    
    // Print to console
    printf("+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    
    // Write to file
    if (file != NULL) {
        fprintf(file, "+------------------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
        fclose(file);
        printf("History data saved to History.txt\n");
    }
}

//Tim va hien thi lich su kham theo ten
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

//Giai phong bo
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
//Luu tru va tra cuu lich su kham benh