
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "patient.h"

// Liệt kê toàn bộ bệnh nhân
void listPatients(PatientList* list) {
    if (list == NULL || list->head == NULL) {
        printf("Danh sách bệnh nhân trống.\n");
        return;
    }

    PatientNode* current = list->head;
    while (current != NULL) {
        printf("ID: %s | Tên: %s | Tuổi: %d | Ưu tiên: %d\n",
               current->patient->id,
               current->patient->name,
               current->patient->year,
               current->patient->priority);
        current = current->next;
    }
}

void listPatientsByPriority(PatientList* list) {
    if (list == NULL || list->head == NULL) {
        printf("The patient list is empty.\n");
        return;
    }

    int maxPriority = 3; // Or the highest priority level used in the system
    for (int priority = 0; priority <= maxPriority; priority++) {
        int found = 0;
        PatientNode* current = list->head;
        while (current != NULL) {
            if (current->patient->priority == priority) {
                printf("ID: %s | Name: %s | Age: %d | Priority: %d\n",
                       current->patient->id,
                       current->patient->name,
                       current->patient->year,
                       current->patient->priority);
                found = 1;
            }
            current = current->next;
        }

        if (found) {
            printf("--- End of priority level %d ---\n", priority);
        }
    }
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