#ifndef STORAGE_H
#define STORAGE_H

#include "student.h"

int loadStudents(const char *fileName, Student students[], int *count);
int saveStudents(const char *fileName, const Student students[], int count);

#endif
