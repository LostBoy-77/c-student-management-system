#include "storage.h"
#include "student.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define TEST_FILE "data/test_students.dat"

static int nearlyEqual(float left, float right)
{
    return fabsf(left - right) < 0.01f;
}

int main(void)
{
    Student students[MAX_STUDENTS] = {0};
    Student loaded[MAX_STUDENTS] = {0};
    Student alice = {1001, "Alice", 88.0f};
    Student bob = {1002, "Bob", 59.0f};
    Student carol = {1003, "Carol", 95.0f};
    Student invalid = {1004, "Invalid", 101.0f};
    StudentStatistics statistics;
    int count = 0;
    int loadedCount = 0;

    assert(addStudentRecord(students, &count, alice) == STUDENT_OK);
    assert(addStudentRecord(students, &count, bob) == STUDENT_OK);
    assert(addStudentRecord(students, &count, carol) == STUDENT_OK);
    assert(count == 3);
    assert(addStudentRecord(students, &count, alice) == STUDENT_DUPLICATE_ID);
    assert(addStudentRecord(students, &count, invalid) == STUDENT_INVALID_DATA);

    assert(findStudentIndexById(students, count, 1002) == 1);
    assert(findStudentIndexById(students, count, 9999) == STUDENT_NOT_FOUND);

    assert(modifyStudentRecord(students, count, 1002, "Bobby", 78.0f) == STUDENT_OK);
    assert(strcmp(students[1].name, "Bobby") == 0);
    assert(nearlyEqual(students[1].score, 78.0f));
    assert(modifyStudentRecord(students, count, 9999, "Nobody", 70.0f) == STUDENT_NOT_FOUND);

    sortStudentsByScore(students, count);
    assert(students[0].id == 1003);
    assert(students[1].id == 1001);
    assert(students[2].id == 1002);

    statistics = calculateStatistics(students, count);
    assert(nearlyEqual(statistics.average, 87.0f));
    assert(nearlyEqual(statistics.highest, 95.0f));
    assert(nearlyEqual(statistics.lowest, 78.0f));
    assert(nearlyEqual(statistics.passRate, 100.0f));

    assert(saveStudents(TEST_FILE, students, count));
    assert(loadStudents(TEST_FILE, loaded, &loadedCount));
    assert(loadedCount == count);
    assert(memcmp(students, loaded, sizeof(Student) * (size_t)count) == 0);
    remove(TEST_FILE);

    assert(deleteStudentRecord(students, &count, 1001) == STUDENT_OK);
    assert(count == 2);
    assert(findStudentIndexById(students, count, 1001) == STUDENT_NOT_FOUND);
    assert(deleteStudentRecord(students, &count, 9999) == STUDENT_NOT_FOUND);

    printf("All student management tests passed.\n");
    return 0;
}
