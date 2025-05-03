#include <stdio.h>
#include <string.h>
#include "patient.h"

// Hàm sắp xếp bệnh nhân theo ưu tiên từ cao xuống thấp bằng tìm kiếm tuần tự
void sortPatientsByPriority(PatientList* list) {
    if (list == NULL || list->patients == NULL) return;

    printf("Sắp xếp bệnh nhân theo thứ tự ưu tiên\n");

    // Tìm kiếm tuần tự và hoán đổi để sắp xếp danh sách bệnh nhân theo ưu tiên giảm dần
    for (int i = 0; i < list->size - 1; i++) {
        for (int j = i + 1; j < list->size; j++) {
            if (list->patients[i].priority < list->patients[j].priority) {
                // Hoán đổi bệnh nhân i và j
                Patient temp = list->patients[i];
                list->patients[i] = list->patients[j];
                list->patients[j] = temp;
            }
        }
    }

    // In bảng kết quả với borders
    printf("\n+------------------------+------------+\n");
    printf("| %-22s | %-10s |\n", "Tên", "Ưu tiên");
    printf("+------------------------+------------+\n");
    for (int i = 0; i < list->size; i++) {
        printf("| %-22s | %-10d |\n", list->patients[i].name, list->patients[i].priority);
        if (i < list->size - 1) {  // Không in border dưới hàng cuối
            printf("+------------------------+------------+\n");
        }
    }
    printf("+------------------------+------------+\n");
}

// Liệt kê bệnh nhân theo mức độ ưu tiên
void listPatientsByPriority(PatientList* list, int priority) {
    if (list == NULL || list->patients == NULL) return;

    // Sắp xếp bệnh nhân theo mức độ ưu tiên từ cao đến thấp
    sortPatientsByPriority(list);
/*
    // Liệt kê bệnh nhân có mức độ ưu tiên cụ thể
    printf("\nBệnh nhân có ưu tiên %d (theo thứ tự ưu tiên cao đến thấp):\n", priority);
    printf("\n+------------------------+------------+\n");
    printf("| %-22s | %-10s |\n", "Tên", "Ưu tiên");
    printf("+------------------------+------------+\n");
    for (int i = 0; i < list->size; i++) {
        if (list->patients[i].priority == priority) {
            printf("| %-22s | %-10d |\n", list->patients[i].name, list->patients[i].priority);
            if (i < list->size - 1) {  // Không in border dưới hàng cuối
                printf("+------------------------+------------+\n");
            }
        }
    }
    printf("+------------------------+------------+\n");
*/
}
