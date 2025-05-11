#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <UI/UI.h>

void displayMenu() {
    printf("\n=== Hospital Management System ===\n");
    printf("1. Add new patient\n");
    printf("2. Call next patient for examination\n");
    printf("3. Finish examination for a patient\n");
    printf("4. Search patient by ID\n");
    printf("5. List all patients\n");
    printf("6. List patients by priority\n");
    printf("7. List patients by status\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
}

void clearScreen() {
    printf("\033[H\033[J");
}

void processUserInput(PatientList *list, PriorityQueue *pq) {
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        switch (choice) {
        case 1:
            
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5: 
            break;
        case 6:
            break;
        case 7: 
            break;
        case 8:
            printf("Exiting");
            break;
        default:
            printf("Invalid Option");
            break;
        }
    } while (choice != 8);
    
}