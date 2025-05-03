// searchReport.h
// Tác giả: [Tên bạn] - Nhóm DSA CD5
// Mô tả: Header cho module tìm kiếm và liệt kê bệnh nhân

#ifndef SEARCH_REPORT_H
#define SEARCH_REPORT_H

#include "patient.h"  // Gồm định nghĩa struct Patient

// Cấu trúc danh sách bệnh nhân
typedef struct {
    Patient* patients;  // Mảng bệnh nhân
    int size;           // Số lượng bệnh nhân
} PatientList;

// Liệt kê toàn bộ bệnh nhân
void listPatients(PatientList* list);

// Liệt kê bệnh nhân theo mức độ ưu tiên (0: thấp nhất)
void listPatientsByPriority(PatientList* list, int priority);

// Tìm kiếm bệnh nhân theo tên (sử dụng tìm kiếm tuần tự)
Patient* searchByName(PatientList* list, char* name);

#endif
