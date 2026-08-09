#ifndef STUDENT_H
#define STUDENT_H

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define PASS_SCORE 60.0f

typedef struct
{
    int id;
    char name[NAME_LENGTH];
    float score;
} Student;

typedef struct
{
    float average;
    float highest;
    float lowest;
    float passRate;
} StudentStatistics;

enum StudentResult
{
    STUDENT_OK = 0,
    STUDENT_NOT_FOUND = -1,
    STUDENT_DUPLICATE_ID = -2,
    STUDENT_LIST_FULL = -3,
    STUDENT_INVALID_DATA = -4
};

int findStudentIndexById(const Student students[], int count, int id);
int addStudentRecord(Student students[], int *count, Student student);
int modifyStudentRecord(Student students[], int count, int id, const char *name, float score);
int deleteStudentRecord(Student students[], int *count, int id);
void sortStudentsByScore(Student students[], int count);
StudentStatistics calculateStatistics(const Student students[], int count);

#endif
