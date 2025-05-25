#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "history.h"

static const char* statusToString(Status status) {
    switch (status) {
        case WAITING: return "Waiting";
        case EXAMINING: return "Examining";
        case FINISHED: return "Finished";
        default: return "Unknown";
    }
}

static const char* caseTypeToString(CaseType type) {
    switch (type) {
        case EMERGENCY: return "Emergency";
        case NORMAL: return "Normal";
        case ROUTINE: return "Routine";
        case CONSULTATION: return "Consultation";
        default: return "Unknown";
    }
}
static int patient_number = 1;

static void generate_code(char *code) {
    sprintf(code, "P%04d", patient_number++);
}

Patient *newPatient(char *name, int year, CaseType caseType) {
    Patient *patient = (Patient *)malloc(sizeof(Patient));
    if (patient == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }

    generate_code(patient->id);

    strncpy(patient->name, name, sizeof(patient->name) - 1);
    patient->name[sizeof(patient->name) - 1] = '\0';

    patient->year = year;
    patient->status = WAITING;
    patient->arrivalTime = time(NULL);
    patient->examiningStartTime = 0;
    patient->examiningEndTime = 0;
    patient->caseType = caseType;

    return patient;
}

void addPatient(PatientList *list, Patient *patient) {
    PatientNode *newNode = (PatientNode *)malloc(sizeof(PatientNode));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->patient = patient;
    newNode->next = NULL;
    
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    return;
}

PatientList *createPatientList() {
    PatientList *list = (PatientList *)malloc(sizeof(PatientList));
    if (list == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    list->head = NULL;
    list->tail = NULL;
    return list;
}

void freePatientList(PatientList *list) {
    if (list == NULL) {
        return;
    }
    PatientNode *current = list->head;
    while (current != NULL) {
        PatientNode *tmp = current;
        current = current->next;
        free(tmp->patient);
        free(tmp);
    }
    list->head = NULL;
    list->tail = NULL;
    free(list);
}

PatientList *loadPatientsFromFile(const char *filename) {
    PatientList *list = createPatientList();
    if (!list) return NULL;

    FILE *file = fopen(filename, "r");
    if (!file) {
        return list;
    }

    char line[256];
    char id[10] = "", name[50] = "";
    int year = 0, status = 0, caseType = 0;
    long arrivalTime = 0, examiningStartTime = 0, examiningEndTime = 0;
    int fields_read = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0) {
            if (fields_read == 8 && status != FINISHED) { // Chỉ thêm nếu không phải FINISHED
                Patient *patient = (Patient *)malloc(sizeof(Patient));
                if (patient) {
                    strncpy(patient->id, id, sizeof(patient->id) - 1);
                    patient->id[sizeof(patient->id) - 1] = '\0';
                    strncpy(patient->name, name, sizeof(patient->name) - 1);
                    patient->name[sizeof(patient->name) - 1] = '\0';
                    patient->year = year;
                    patient->status = (Status)status;
                    patient->caseType = (CaseType)caseType;
                    patient->arrivalTime = (time_t)arrivalTime;
                    patient->examiningStartTime = (time_t)examiningStartTime;
                    patient->examiningEndTime = (time_t)examiningEndTime;
                    addPatient(list, patient);
                    int id_num = atoi(id + 1);
                    if (id_num >= patient_number) {
                        patient_number = id_num + 1;
                    }
                }
            }
            fields_read = 0;
            continue;
        }

        if (strncmp(line, "id: ", 4) == 0) {
            strncpy(id, line + 4, sizeof(id));
            id[sizeof(id) - 1] = '\0';
            fields_read++;
        } else if (strncmp(line, "name: ", 6) == 0) {
            strncpy(name, line + 6, sizeof(name));
            name[sizeof(name) - 1] = '\0';
            fields_read++;
        } else if (strncmp(line, "year: ", 6) == 0) {
            year = atoi(line + 6);
            fields_read++;
        } else if (strncmp(line, "status: ", 8) == 0) {
            if (strncmp(line + 8, "Waiting", 7) == 0) status = WAITING;
            else if (strncmp(line + 8, "Examining", 9) == 0) status = EXAMINING;
            else if (strncmp(line + 8, "Finished", 8) == 0) status = FINISHED;
            else status = atoi(line + 8); 
            fields_read++;
        } else if (strncmp(line, "caseType: ", 10) == 0) {
            if (strncmp(line + 10, "Emergency", 9) == 0) caseType = EMERGENCY;
            else if (strncmp(line + 10, "Normal", 6) == 0) caseType = NORMAL;
            else if (strncmp(line + 10, "Routine", 7) == 0) caseType = ROUTINE;
            else if (strncmp(line + 10, "Consultation", 12) == 0) caseType = CONSULTATION;
            else caseType = atoi(line + 10); 
            fields_read++;
        } else if (strncmp(line, "arrivalTime: ", 13) == 0) {
            if (strncmp(line + 13, "N/A", 3) == 0) arrivalTime = 0;
            else arrivalTime = atol(line + 13);
            fields_read++;
        } else if (strncmp(line, "examiningStartTime: ", 20) == 0) {
            if (strncmp(line + 20, "N/A", 3) == 0) examiningStartTime = 0;
            else examiningStartTime = atol(line + 20);
            fields_read++;
        } else if (strncmp(line, "examiningEndTime: ", 18) == 0) {
            if (strncmp(line + 18, "N/A", 3) == 0) examiningEndTime = 0;
            else examiningEndTime = atol(line + 18);
            fields_read++;
        }
    }

    if (fields_read == 8 && status != FINISHED) {
        Patient *patient = (Patient *)malloc(sizeof(Patient));
        if (patient) {
            strncpy(patient->id, id, sizeof(patient->id) - 1);
            patient->id[sizeof(patient->id) - 1] = '\0';
            strncpy(patient->name, name, sizeof(patient->name) - 1);
            patient->name[sizeof(patient->name) - 1] = '\0';
            patient->year = year;
            patient->status = (Status)status;
            patient->caseType = (CaseType)caseType;
            patient->arrivalTime = (time_t)(arrivalTime > 0 ? arrivalTime : time(NULL));
            patient->examiningStartTime = (time_t)(examiningStartTime > 0 ? examiningStartTime : 0);
            patient->examiningEndTime = (time_t)(examiningEndTime > 0 ? examiningEndTime : 0);
            addPatient(list, patient);
            int id_num = atoi(id + 1);
            if (id_num >= patient_number) {
                patient_number = id_num + 1;
            }
        }
    }

    fclose(file);
    return list;
}

void savePatientToFile(Patient *patient, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    char arrivalStr[32], startStr[32], endStr[32];
    if (patient->arrivalTime > 0) {
        strftime(arrivalStr, sizeof(arrivalStr), "%d-%m-%Y %H:%M:%S", localtime(&patient->arrivalTime));
    } else {
        strcpy(arrivalStr, "N/A");
    }
    if (patient->examiningStartTime > 0) {
        strftime(startStr, sizeof(startStr), "%d-%m-%Y %H:%M:%S", localtime(&patient->examiningStartTime));
    } else {
        strcpy(startStr, "N/A");
    }
    if (patient->examiningEndTime > 0) {
        strftime(endStr, sizeof(endStr), "%d-%m-%Y %H:%M:%S", localtime(&patient->examiningEndTime));
    } else {
        strcpy(endStr, "N/A");
    }

    fprintf(file, "id: %s\n", patient->id);
    fprintf(file, "name: %s\n", patient->name);
    fprintf(file, "year: %d\n", patient->year);
    fprintf(file, "status: %d\n", patient->status);
    fprintf(file, "caseType: %d\n", patient->caseType);
    fprintf(file, "arrivalTime: %s\n", arrivalStr);
    fprintf(file, "examiningStartTime: %s\n", startStr);
    fprintf(file, "examiningEndTime: %s\n", endStr);
    fprintf(file, "\n");

    fclose(file);
}

void updatePatientsFile(PatientList *list, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    char arrivalStr[32], startStr[32], endStr[32];
    PatientNode *current = list->head;
    while (current) {
        Patient *p = current->patient;
        strftime(arrivalStr, sizeof(arrivalStr),"%d-%m-%Y %H:%M:%S", localtime(&p->arrivalTime));
        if (p->examiningStartTime > 0) {
            strftime(startStr, sizeof(startStr), "%d-%m-%Y %H:%M:%S", localtime(&p->examiningStartTime));
        } else {
            strcpy(startStr, "N/A");
        }
        if (p->examiningEndTime > 0) {
            strftime(endStr, sizeof(endStr), "%d-%m-%Y %H:%M:%S", localtime(&p->examiningEndTime));
        } else {
            strcpy(endStr, "N/A");
        }

        fprintf(file, "id: %s\n", p->id);
        fprintf(file, "name: %s\n", p->name);
        fprintf(file, "year: %d\n", p->year);
        fprintf(file, "status: %d // %s\n", p->status, statusToString(p->status));
        fprintf(file, "caseType: %d // %s\n", p->caseType, caseTypeToString(p->caseType));
        fprintf(file, "arrivalTime: %ld // %s\n", p->arrivalTime, arrivalStr);
        fprintf(file, "examiningStartTime: %ld // %s\n", p->examiningStartTime, startStr);
        fprintf(file, "examiningEndTime: %ld // %s\n", p->examiningEndTime, endStr);
        fprintf(file, "\n");
        current = current->next;
    }

    fclose(file);
}