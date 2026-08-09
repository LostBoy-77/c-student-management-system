#include "storage.h"

#include <stdio.h>

int loadStudents(const char *fileName, Student students[], int *count)
{
    FILE *file;
    int storedCount;

    if (fileName == NULL || students == NULL || count == NULL)
    {
        return 0;
    }

    file = fopen(fileName, "rb");
    if (file == NULL)
    {
        *count = 0;
        return 1;
    }

    if (fread(&storedCount, sizeof(storedCount), 1, file) != 1 ||
        storedCount < 0 || storedCount > MAX_STUDENTS ||
        fread(students, sizeof(Student), (size_t)storedCount, file) != (size_t)storedCount)
    {
        fclose(file);
        *count = 0;
        return 0;
    }

    fclose(file);
    *count = storedCount;
    return 1;
}

int saveStudents(const char *fileName, const Student students[], int count)
{
    FILE *file;

    if (fileName == NULL || students == NULL || count < 0 || count > MAX_STUDENTS)
    {
        return 0;
    }

    file = fopen(fileName, "wb");
    if (file == NULL)
    {
        return 0;
    }

    if (fwrite(&count, sizeof(count), 1, file) != 1 ||
        fwrite(students, sizeof(Student), (size_t)count, file) != (size_t)count)
    {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}
