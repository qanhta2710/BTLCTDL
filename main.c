#include <stdio.h>
#include <stdlib.h>
#include "UI/UI.h"
int main() {
    PatientList *myList = createPatientList();
    PriorityQueue *myQueue = createPriorityQueue();

    if (myList == NULL || myQueue == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    processUserInput(myList, myQueue);
    
    freePatientList(myList);
    freePriorityQueue(myQueue);
    return 0;
}