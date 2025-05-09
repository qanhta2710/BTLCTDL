#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "patient.h"

// Chuyển enum trạng thái sang chuỗi
const char* getStatusString(Status status) {
    switch (status) {
        case WAITING: return "WAITING";
        case EXAMINING: return "EXAMINING";
        case FINISHED: return "FINISHED";
        default: return "UNKNOWN";
    }
}

// Format thời gian đến thành chuỗi
void formatArrivalTime(time_t rawTime, char* buffer, int bufSize) {
    struct tm* timeinfo = localtime(&rawTime);
    strftime(buffer, bufSize, "%Y-%m-%d %H:%M", timeinfo);
}

// Hàm sắp xếp bệnh nhân theo ưu tiên từ cao xuống thấp bằng cách duyệt danh sách liên kết
void sortPatientsByPriority(PatientList* list) {
    if (list == NULL || list->head == NULL) return;

    printf("Sorting patients by priority order\n");

    PatientNode *i, *j;
    Patient *tempPatient;
    for (i = list->head; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->patient->priority < j->patient->priority) {
                tempPatient = i->patient;
                i->patient = j->patient;
                j->patient = tempPatient;
            }
        }
    }

    // In bảng kết quả
    printf("\n+----------+----------------------+------+" 
           "------------+-------------------+------------+\n");
    printf("| %-8s | %-20s | %-4s | %-10s | %-17s | %-10s |\n",
           "ID", "Name", "Birth Year", "Status", "Arrival Time", "Priority");
    printf("+----------+----------------------+------+" 
           "------------+-------------------+------------+\n");

    PatientNode* current = list->head;
    while (current != NULL) {
        char timeStr[20];
        formatArrivalTime(current->patient->arrivalTime, timeStr, sizeof(timeStr));
        printf("| %-8s | %-20s | %-4d | %-10s | %-17s | %-10d |\n",
               current->patient->id,
               current->patient->name,
               current->patient->year,
               getStatusString(current->patient->status),
               timeStr,
               current->patient->priority);
        current = current->next;
        if (current != NULL) {
            printf("+----------+----------------------+------+" 
                   "------------+-------------------+------------+\n");
        }
    }
    printf("+----------+----------------------+------+" 
           "------------+-------------------+------------+\n");
}

// Tìm kiếm bệnh nhân theo tên (tìm kiếm tuần tự)
Patient* searchByName(PatientList* list, char* name) {
    if (list == NULL || list->head == NULL || name == NULL) return NULL;

    PatientNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->patient->name, name) == 0) {
            return current->patient; // Trả về con trỏ tới bệnh nhân đầu tiên tìm thấy
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}

// Tìm kiếm bệnh nhân theo ID (tìm kiếm tuần tự trên danh sách liên kết)
Patient* searchByID(PatientList* list, char* id) {
    if (list == NULL || list->head == NULL || id == NULL) return NULL;

    PatientNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->patient->id, id) == 0) {
            return current->patient; // Trả về con trỏ tới bệnh nhân đầu tiên tìm thấy
        }
        current = current->next;
    }
    return NULL; // Không tìm thấy
}