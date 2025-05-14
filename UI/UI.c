#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UI.h"
#include "Search/searchReport.h"
#include "Examine/examination.h"

void displayMenu() {
    printf("\n=== Hospital Management System ===\n");
    printf("1. Add new patient to list\n");
    printf("2. Call next patient for examination\n");
    printf("3. Finish examination for a patient\n");
    printf("4. Search patient by ID\n");
    printf("5. Search patient by name\n");
    printf("6. List patients by ID\n");
    printf("7. List patients by priority\n");
    printf("8. List patients by status\n");
    printf("9. Show Queue\n");
    printf("10. Exit\n");
    printf("Enter your choice: ");
}

void clearScreen() {
    printf("\033[H\033[J");
}

const char *getCaseTypeName(CaseType caseType) {
    switch (caseType) {
        case EMERGENCY: 
            return "Emergency";
        case NORMAL:
            return "Normal";
        case ROUTINE:
            return "Routine";
        case CONSULTATION:
            return "Consultation";
        default:
            return "Invalid";
    }
}

const char *getStatusName(Status status) {
    switch (status) {
        case WAITING:
            return "Waiting";
        case EXAMINING:
            return "Examining";
        case FINISHED:
            return "Finished";
        default:
            return "Invalid";
    }
}

void processUserInput(PatientList *list, PriorityQueue *pq) {
    int choice, caseTypeChoice;
    char id[10], name[255];
    int year, caseType;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar();
        
        switch (choice) {
        case 1:
            clearScreen();
            printf("=== Add New Patient ===\n");

            printf("Enter patient ID: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;
            
            printf("Enter patient name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            printf("Enter birth year: ");
            scanf("%d", &year);
            getchar();

            do
            {
                printf("Select case type:\n");
                printf("1. Emergency\n");
                printf("2. Normal\n");
                printf("3. Routine\n");
                printf("4. Consultation\n");
                printf("Enter case type (1-4): ");
                scanf("%d", &caseTypeChoice);
                getchar();
                if (caseTypeChoice < 1 || caseTypeChoice > 4) {
                    printf("Try again\n");
                }
            } while (caseTypeChoice < 1 || caseTypeChoice > 4);
            caseType = (CaseType)caseTypeChoice;

            Patient *myPatient = newPatient(id, name, year, caseType);
            if (myPatient != NULL) {
                if (searchPatientByID(list, id) != NULL) {
                    printf("Patient ID already exists\n");
                    free(myPatient);
                    break;
                } else {
                    addPatient(list, myPatient);
                    enqueue(pq, myPatient);
                    printf("Patient added successfully\n");    
                }
            } else {
                printf("Failed to create patient\n");
            }
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 2:
            clearScreen();
            printf("=== Call Next Patient ===\n");
            if (isEmpty(pq)) {
                printf("Queue is empty\n");
            } else {
                Patient *nextPatient = dequeue(pq);
                startExamination(nextPatient);
                printf("Calling ID: %s\n", nextPatient->id);
                printf("Patient Name: %s\n", nextPatient->name);
            }
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 3:
            clearScreen();
            printf("=== Finish Examination ===\n");
            printf("Enter patient ID: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;
            Patient *finishedPatient = searchByID(list, id); // TODO: Chờ làm xong hàm search
            if (finishedPatient == NULL) {
                printf("Patient not found\n");
            } else if (finishedPatient->status != EXAMINING) {
                printf("Patient is not examined or already finished\n");
            } else {
                finishExamination(finishedPatient);
                printf("Finished examinating for patient: %s\n", finishedPatient->name);
            }
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 4:
            clearscreen();
            printf("=== Search Patient by ID ===\n");
            printf("Enter patient ID: ");
            fgets(id, sizeof(id), stdin);
            id[strcspn(id, "\n")] = 0;
            Patient *targetPatient = searchByID(list, id); // TODO: Chờ hàm searchByID
            if (targetPatient == NULL) {
                printf("Patient not found\n");
            } else {
                char arrivalBuffer[100], startBuffer[100], endBuffer[100];
                strftime(arrivalBuffer, sizeof(arrivalBuffer), "%d-%m-%Y %H:%M:%S", localtime(&targetPatient->arrivalTime));
                strftime(startBuffer, sizeof(startBuffer), "%d-%m-%Y %H:%M:%S", localtime(&targetPatient->examiningStartTime));
                strftime(endBuffer, sizeof(endBuffer), "%d-%m-%Y %H:%M:%S", localtime(&targetPatient->examiningEndTime));

                printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
                printf("| ID         | Name                 | Birth Year | Status     | Arrival Time        | Case Type      | Examining Time      | Finished Time       |\n");
                printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
                printf("| %-10s | %-20s | %-10d | %-10s | %-19s | %-14s | %-19s | %-19s |\n",
                    targetPatient->id,
                    targetPatient->name,
                    targetPatient->year,
                    getStatusName(targetPatient->status),
                    arrivalBuffer,
                    getCaseTypeName(targetPatient->caseType),
                    targetPatient->examiningStartTime == 0 ? "Not started" : startBuffer,
                    targetPatient->examiningEndTime == 0 ? "Not finished" : endBuffer);
                printf("+------------+----------------------+------------+------------+---------------------+----------------+---------------------+---------------------+\n");
            }
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 5:
            clearScreen();
            printf("=== Search Patient by Name ===\n");
            printf("Enter patient name: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0;

            searchByName(list, name); // TODO: Chờ hoàn thành hàm searchByName
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 6:
            clearScreen();
            printf("=== List Patients by ID ===\n");
            listPatientsByID(list); // TODO
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 7: 
            clearscreen();
            printf("=== List Patients by Priority ===\n");
            listPatientsByPriority(list); // TODO
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 8:
            clearScreen();
            printf("=== List Patients by Status ===\n");
            listPatientsByStatus(list); // TODO
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 9:
            clearScreen();
            showQueue(pq); // TODO
            printf("Press any key to continue...\n");
            getchar();
            break;
        case 10:
            clearScreen();
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Option");
        }
    } while (choice != 10);
}