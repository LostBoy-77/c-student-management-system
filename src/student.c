#include "student.h"

#include <string.h>

static int isValidStudent(int id, const char *name, float score)
{
    return id > 0 && name != NULL && name[0] != '\0' && score >= 0.0f && score <= 100.0f;
}

int findStudentIndexById(const Student students[], int count, int id)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (students[i].id == id)
        {
            return i;
        }
    }

    return STUDENT_NOT_FOUND;
}

int addStudentRecord(Student students[], int *count, Student student)
{
    if (students == NULL || count == NULL || !isValidStudent(student.id, student.name, student.score))
    {
        return STUDENT_INVALID_DATA;
    }

    if (*count >= MAX_STUDENTS)
    {
        return STUDENT_LIST_FULL;
    }

    if (findStudentIndexById(students, *count, student.id) >= 0)
    {
        return STUDENT_DUPLICATE_ID;
    }

    students[*count] = student;
    (*count)++;
    return STUDENT_OK;
}

int modifyStudentRecord(Student students[], int count, int id, const char *name, float score)
{
    int index;

    if (!isValidStudent(id, name, score))
    {
        return STUDENT_INVALID_DATA;
    }

    index = findStudentIndexById(students, count, id);
    if (index < 0)
    {
        return STUDENT_NOT_FOUND;
    }

    strncpy(students[index].name, name, NAME_LENGTH - 1);
    students[index].name[NAME_LENGTH - 1] = '\0';
    students[index].score = score;
    return STUDENT_OK;
}

int deleteStudentRecord(Student students[], int *count, int id)
{
    int index;
    int i;

    if (students == NULL || count == NULL)
    {
        return STUDENT_INVALID_DATA;
    }

    index = findStudentIndexById(students, *count, id);
    if (index < 0)
    {
        return STUDENT_NOT_FOUND;
    }

    for (i = index; i < *count - 1; i++)
    {
        students[i] = students[i + 1];
    }

    (*count)--;
    return STUDENT_OK;
}

void sortStudentsByScore(Student students[], int count)
{
    int i;
    int j;

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (students[j].score < students[j + 1].score)
            {
                Student temporary = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temporary;
            }
        }
    }
}

StudentStatistics calculateStatistics(const Student students[], int count)
{
    StudentStatistics result = {0.0f, 0.0f, 0.0f, 0.0f};
    float total = 0.0f;
    int passed = 0;
    int i;

    if (count <= 0)
    {
        return result;
    }

    result.highest = students[0].score;
    result.lowest = students[0].score;

    for (i = 0; i < count; i++)
    {
        total += students[i].score;
        if (students[i].score > result.highest)
        {
            result.highest = students[i].score;
        }
        if (students[i].score < result.lowest)
        {
            result.lowest = students[i].score;
        }
        if (students[i].score >= PASS_SCORE)
        {
            passed++;
        }
    }

    result.average = total / count;
    result.passRate = (float)passed * 100.0f / count;
    return result;
}
