#ifndef PATIENT_H
#define PATIENT_H

#include <time.h>

typedef enum { 
    EMERGENCY = 1, // Cấp cứu khẩn cấp, ưu tiên cao nhất
    NORMAL = 2, // Khám thông thường
    ROUTINE = 3, // Khám định kỳ
    CONSULTATION = 4 // Tư vấn y tế, ưu tiên thấp nhất 
} CaseType;

// Các trạng thái khám bệnh gồm WAITING (chờ khám), EXAMINING (đang khám), FINISHED (hoàn thành)
typedef enum { WAITING, EXAMINING, FINISHED } Status;

// Cấu trúc bệnh nhân
typedef struct Patient {
    char id[10]; // Mã bệnh nhân
    char name[255]; // Họ tên
    int year;      // Năm sinh
    Status status; // Trạng thái khám
    time_t arrivalTime; // Thời gian đến khám
    CaseType caseType; // Mức độ ưu tiên
    time_t examiningStartTime; // Thời gian bắt đầu khám
    time_t examiningEndTime; // Thời gian kết thúc khám
} Patient;

// Danh sách liên kết đơn cho các bệnh nhân
typedef struct PatientNode {
    Patient *patient;
    struct PatientNode *next;
} PatientNode;

typedef struct PatientList {
    PatientNode *head;
} PatientList;

Patient *newPatient(char *name, int year, CaseType caseType);
void addPatient(PatientList *list, Patient *patient);
PatientList *createPatientList();
void freePatientList(PatientList *list);

#endif