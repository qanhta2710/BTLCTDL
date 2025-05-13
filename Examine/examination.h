#ifndef EXAMINATION_H
#define EXAMINATION_H

#include "patient.h"

void startExamination(Patient *patient); // Thực hiện chuyển trạng thái từ WAITING sang EXAMINING và cập nhật thời gian bắt đầu khám
void finishExamination(Patient *patient); // Thực hiện chuyển trạng thái từ EXAMINING sang FINISHED và cập nhật thời gian kết thúc khám

#endif