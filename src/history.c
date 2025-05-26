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
    list->tail = NULL;
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
    
    memset(&newVisit->data, 0, sizeof(History));
    newVisit->next = NULL;

    char timeStr[30];
    strftime(timeStr, sizeof(timeStr), "%Y%m%d%H%M%S", localtime(&patient->arrivalTime));
    sprintf(newVisit->data.visitedID, "%s_%s", patient->id, timeStr);
    
    strcpy(newVisit->data.IDCard, patient->IDCard);
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
    printf("Added patient to history successfully\n");
}

void showHistory(historyList *list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    historyNode *current = list->head;
    printf("+------------------------+--------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    printf("| Visited ID             | IDCard       | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
    printf("+------------------------+--------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    while (current != NULL) {
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningEndTime));

        printf("| %-22s | %-12s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
            current->data.visitedID,
            current->data.IDCard,
            current->data.name,
            current->data.year,
            arrivalBuffer,
            startBuffer,
            endBuffer);
        current = current->next;
        printf("+------------------------+--------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    }
}

void searchVisitHistoryByIDCard(historyList *list, const char *IDCard) {
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    historyNode *current = list->head;
    printf("+------------------------+--------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    printf("| Visited ID             | IDCard       | Name                 | Birth Year | Arrival Time        | Examining Time      | Finished Time       |\n");
    printf("+------------------------+--------------+----------------------+------------+---------------------+---------------------+---------------------+\n");
    while (strcmp(current->data.IDCard, IDCard) == 0) {
        char arrivalBuffer[100], startBuffer[100], endBuffer[100];
        strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.arrivalTime));
        strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningStartTime));
        strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&current->data.examiningEndTime));
        printf("| %-22s | %-12s | %-20s | %-10d | %-19s | %-19s | %-19s |\n",
            current->data.visitedID,
            current->data.IDCard,
            current->data.name,
            current->data.year,
            arrivalBuffer,
            startBuffer,
            endBuffer);
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
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

void saveHistoryToFile(History *history, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }
    char arrivalStr[32], startStr[32], endStr[32];
    strftime(arrivalStr, sizeof(arrivalStr),"%d-%m-%Y %H:%M:%S", localtime(&history->arrivalTime));
    strftime(startStr, sizeof(startStr), "%d-%m-%Y %H:%M:%S", localtime(&history->examiningStartTime));
    strftime(endStr, sizeof(endStr), "%d-%m-%Y %H:%M:%S", localtime(&history->examiningEndTime));

    fprintf(file, "visitedID: %s\n", history->visitedID);
    fprintf(file, "IDCard: %s\n", history->IDCard);
    fprintf(file, "name: %s\n", history->name);
    fprintf(file, "year: %d\n", history->year);
    fprintf(file, "arrivalTime: %ld // %s\n", history->arrivalTime, arrivalStr);
    fprintf(file, "examiningStartTime: %ld // %s\n", history->examiningStartTime, startStr);
    fprintf(file, "examiningEndTime: %ld // %s\n", history->examiningEndTime, endStr);
    fprintf(file, "\n");

    fclose(file);
}

static void addHistoryNode(historyList *list, History *h) {
    if (list == NULL || h == NULL) return;
    historyNode *newNode = (historyNode *)malloc(sizeof(historyNode));
    if (!newNode) return;
    newNode->data = *h;
    newNode->next = NULL;
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

historyList *loadHistoryFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return createHistory();

    historyList *list = createHistory();
    char line[256], visitedID[32],IDCard[20], name[100];
    int year = 0;
    long arrivalTime = 0, examiningStartTime = 0, examiningEndTime = 0;
    int fields_read = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) {
            if (fields_read == 7) {
                History h;
                strcpy(h.visitedID, visitedID);
                strcpy(h.IDCard, IDCard);
                strcpy(h.name, name);
                h.year = year;
                h.arrivalTime = arrivalTime;
                h.examiningStartTime = examiningStartTime;
                h.examiningEndTime = examiningEndTime;
                addHistoryNode(list, &h);
            }
            fields_read = 0;
            continue;
        }
        if (strncmp(line, "visitedID: ", 11) == 0) {
            strncpy(visitedID, line + 11, sizeof(visitedID));
            fields_read++;
        } else if (strncmp(line, "IDCard: ", 8) == 0) {
            strncpy(IDCard, line + 8, sizeof(IDCard));
            fields_read++;
        } else if (strncmp(line, "name: ", 6) == 0) {
            strncpy(name, line + 6, sizeof(name));
            fields_read++;
        } else if (strncmp(line, "year: ", 6) == 0) {
            year = atoi(line + 6);
            fields_read++;
        } else if (strncmp(line, "arrivalTime: ", 13) == 0) {
            arrivalTime = atol(line + 13);
            fields_read++;
        } else if (strncmp(line, "examiningStartTime: ", 20) == 0) {
            examiningStartTime = atol(line + 20);
            fields_read++;
        } else if (strncmp(line, "examiningEndTime: ", 18) == 0) {
            examiningEndTime = atol(line + 18);
            fields_read++;
        }
    }
    fclose(file);
    return list;
}