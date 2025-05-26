#include <stdio.h>
#include <stdlib.h>
#include "UI.h"
#include "priorityQueue.h"
#include "history.h"

int main() {
    PatientList *myList = loadPatientsFromFile("patients.txt");
    updatePatientsFile(myList, "patients.txt");
    PriorityQueue myQueue;
    initQueue(&myQueue);
    historyList *history = loadHistoryFromFile("history.txt");

    if (myList == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }
    PatientNode *current = myList->head;
    while (current) {
        if (current->patient->status != FINISHED) {
            enqueue(&myQueue, current->patient);
        }
        current = current->next;
    }
    processUserInput(myList, &myQueue, history);
    freePatientList(myList);
    freeList(history);
    return 0;
}