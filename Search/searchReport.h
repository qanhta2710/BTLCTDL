#ifndef SEARCH_REPORT_H
#define SEARCH_REPORT_H

#include "Examine/patient.h"  // Gồm định nghĩa struct Patient, Status, PatientNode


// Liệt kê bệnh nhân theo mức độ ưu tiên (1: thấp nhất)
void listPatientsByPriority(PatientList* list);

// Tìm kiếm bệnh nhân theo tên (sử dụng tìm kiếm tuần tự)
void searchByName(PatientList* list, char* name);

// Tìm kiếm bệnh nhân theo ID (sử dụng tim kiem tuan tu)
Patient* searchByID(PatientList* list, char* id);

#endif