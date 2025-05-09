#ifndef SEARCH_REPORT_H
#define SEARCH_REPORT_H

#include "patient.h"  // Gồm định nghĩa struct Patient, Status, PatientNode

// Cấu trúc nút cho cây nhị phân tìm kiếm (BST)
typedef struct BSTNode {
    char* id;               // ID của bệnh nhân (khóa)
    Patient* patient;       // Con trỏ tới bệnh nhân
    struct BSTNode* left;   // Con trỏ tới nhánh trái
    struct BSTNode* right;  // Con trỏ tới nhánh phải
} BSTNode;

// Cấu trúc danh sách bệnh nhân
typedef struct {
    PatientNode* head;      // Đầu danh sách liên kết
    int size;               // Số lượng bệnh nhân
    BSTNode* bstRoot;       // Gốc của cây BST để tìm kiếm theo ID
} PatientList;

// Liệt kê toàn bộ bệnh nhân
void listPatients(PatientList* list);

// Liệt kê bệnh nhân theo mức độ ưu tiên (0: thấp nhất)
void listPatientsByPriority(PatientList* list, int priority);

// Tìm kiếm bệnh nhân theo tên (sử dụng tìm kiếm tuần tự)
Patient* searchByName(PatientList* list, char* name);

// Tìm kiếm bệnh nhân theo ID (sử dụng tim kiem tuan tu)
Patient* searchByID(PatientList* list, char* id);

#endif
