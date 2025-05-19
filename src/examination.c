#include <stdio.h>
#include <time.h>
#include "patient.h"
#include "examination.h"

void startExamination(Patient *patient) {
    if (patient == NULL) {
        printf("Invalid patient\n");
        return;
    }

    if (patient->status != WAITING) {
        printf("Cannot start examination. Current status of patient %s is not WAITING.\n", patient->name);
        return;
    }

    patient->status = EXAMINING;
    patient->examiningStartTime = time(NULL);

    printf("Examination started for patient %s at %s", patient->name, ctime(&(patient->examiningStartTime)));
}

void finishExamination(Patient *patient) {
    if (patient == NULL) {
        printf("Invalid patient\n");
        return;
    }

    if (patient->status != EXAMINING) {
        printf("Cannot finish examination. Current status of patient %s is not EXAMINING.\n", patient->name);
        return;
    }

    patient->status = FINISHED;
    patient->examiningEndTime = time(NULL);

    printf("Examination finished for patient %s at %s", patient->name, ctime(&(patient->examiningEndTime)));
}
