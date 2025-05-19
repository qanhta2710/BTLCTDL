#include <stdio.h>
#include <stdlib.h>
#include "UI.h"
#include "priorityQueue.h"
#include "history.h"

int main() {
    PatientList *myList = createPatientList();
    PriorityQueue myQueue;
    initQueue(&myQueue);
    historyList *history = createHistory();

    if (myList == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    processUserInput(myList, &myQueue, history);
    freePatientList(myList);
    freeList(history);
    return 0;
}