#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

// Cac trang thai cua benh nhan
typedef enum { WAITING, EXAMINING, FINISHED } Status;

// Cau truc cho benh nhan
typedef struct Patient {
    char id[10]; // Ma benh nhan
    char name[50]; // Ten benh nhan
    int age;      // Tuoi benh nhan
    Status status; // Trang thai benh nhan
    time_t arrivalTime; // Thoi gian den kham benh
} Patient;

// Cau truc kieu Node cho benh nhan
typedef struct PatientNode {
    Patient *patient;
    struct PatientNode *next;
} PatientNode;

// Cau truc kieu hang doi tro toi phan tu dau tien danh sach
typedef struct PatientList {
    PatientNode *head;
} PatientList;

#endif