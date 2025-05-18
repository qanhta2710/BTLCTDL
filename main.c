#include <stdio.h>
#include <stdlib.h>
#include "UI/UI.h"
#include "Queue/priorityQueue.h"
int main() {
    PatientList *myList = createPatientList();
    PriorityQueue myQueue;
    initQueue(&myQueue);

    if (myList == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    processUserInput(myList, &myQueue);
    
    freePatientList(myList);
    return 0;
}