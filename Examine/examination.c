 #include <stdio.h>
#include <time.h>
#include "Examine/patient.h"
#include "Examine/examination.h"

// Start the examination for a patient
void startExamination(Patient *patient) {
    if (patient == NULL) {
        printf("Error: Invalid patient (NULL).\n");
        return;
    }

    if (patient->status != WAITING) {
        printf("Cannot start examination. Current status of patient %s is not WAITING.\n", patient->name);
        return;
    }

    patient->status = EXAMINING;
    patient->examiningStartTime = time(NULL);

    printf("Examination started for patient %s at %s", 
           patient->name, ctime(&(patient->examiningStartTime)));
}

// Finish the examination for a patient
void finishExamination(Patient *patient) {
    if (patient == NULL) {
        printf("Error: Invalid patient (NULL).\n");
        return;
    }

    if (patient->status != EXAMINING) {
        printf("Cannot finish examination. Current status of patient %s is not EXAMINING.\n", patient->name);
        return;
    }

    patient->status = FINISHED;
    patient->examiningEndTime = time(NULL);

    printf("Examination finished for patient %s at %s", 
           patient->name, ctime(&(patient->examiningEndTime)));
}
