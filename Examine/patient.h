#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

// Cac trang thai cua benh nhan
typedef enum { WAITING, EXAMINING, FINISHED } Status;

// Cau truc cho benh nhan
typedef struct Patient {
    char id[10]; // Ma benh nhan
    char name[50]; // Ho ten
    int year;      // Nam sinh
    Status status; // Trang thai
    time_t arrivalTime; // Thoi gian den kham benh
    int priority; // Muc do uu tien
} Patient;

// Cau truc kieu Node cho benh nhan (danh sach lien ket don)
typedef struct PatientNode {
    Patient *patient;
    struct PatientNode *next;
} PatientNode;

// Cau truc kieu hang doi tro toi phan tu dau tien danh sach
typedef struct PatientList {
    PatientNode *head;
} PatientList;

Patient *newPatient(char *id, char *name, int year, time_t arrivalTime, int priority);
PatientList *createPatientList();
void updatePatientStatus(Patient *Patient, int status);
void freePatientList(PatientList *list);

#endif