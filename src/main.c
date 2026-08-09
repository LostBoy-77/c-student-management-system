#include "storage.h"
#include "student.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATA_FILE "data/students.dat"
#define INPUT_LENGTH 128

static Student students[MAX_STUDENTS];
static int studentCount = 0;

static int readLine(const char *prompt, char *buffer, size_t size)
{
    size_t length;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n')
    {
        buffer[length - 1] = '\0';
    }
    else
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
    }

    return 1;
}

static int readInt(const char *prompt, int *value)
{
    char input[INPUT_LENGTH];
    char *end;
    long parsed;

    if (!readLine(prompt, input, sizeof(input)))
    {
        return 0;
    }

    parsed = strtol(input, &end, 10);
    if (input[0] == '\0' || *end != '\0')
    {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int readFloat(const char *prompt, float *value)
{
    char input[INPUT_LENGTH];
    char *end;
    float parsed;

    if (!readLine(prompt, input, sizeof(input)))
    {
        return 0;
    }

    parsed = strtof(input, &end);
    if (input[0] == '\0' || *end != '\0')
    {
        return 0;
    }

    *value = parsed;
    return 1;
}

static void showMenu(void)
{
    printf("\n====================================\n");
    printf(" Student Management System\n");
    printf("====================================\n");
    printf("1. Add student\n");
    printf("2. Show all students\n");
    printf("3. Search student\n");
    printf("4. Modify student\n");
    printf("5. Delete student\n");
    printf("6. Sort by score\n");
    printf("7. Show statistics\n");
    printf("0. Save and exit\n");
    printf("====================================\n");
}

static void printStudent(const Student *student)
{
    printf("%-10d %-30s %-10.2f\n", student->id, student->name, student->score);
}

static void showAllStudents(void)
{
    int i;

    if (studentCount == 0)
    {
        printf("No student data available.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Score");
    printf("------------------------------------------------------\n");
    for (i = 0; i < studentCount; i++)
    {
        printStudent(&students[i]);
    }
}

static void addStudent(void)
{
    Student student;
    int result;

    if (!readInt("Enter student ID: ", &student.id) || student.id <= 0)
    {
        printf("Invalid ID. It must be a positive integer.\n");
        return;
    }
    if (!readLine("Enter student name: ", student.name, sizeof(student.name)) || student.name[0] == '\0')
    {
        printf("Name cannot be empty.\n");
        return;
    }
    if (!readFloat("Enter score (0-100): ", &student.score))
    {
        printf("Invalid score.\n");
        return;
    }

    result = addStudentRecord(students, &studentCount, student);
    if (result == STUDENT_DUPLICATE_ID)
    {
        printf("This student ID already exists.\n");
    }
    else if (result == STUDENT_LIST_FULL)
    {
        printf("Student list is full.\n");
    }
    else if (result == STUDENT_INVALID_DATA)
    {
        printf("ID, name or score is invalid.\n");
    }
    else
    {
        printf("Student added successfully.\n");
    }
}

static void searchStudent(void)
{
    int id;
    int index;

    if (!readInt("Enter student ID to search: ", &id))
    {
        printf("Invalid ID.\n");
        return;
    }

    index = findStudentIndexById(students, studentCount, id);
    if (index < 0)
    {
        printf("Student not found.\n");
        return;
    }

    printf("\n%-10s %-30s %-10s\n", "ID", "Name", "Score");
    printStudent(&students[index]);
}

static void modifyStudent(void)
{
    int id;
    char name[NAME_LENGTH];
    float score;
    int result;

    if (!readInt("Enter student ID to modify: ", &id) ||
        !readLine("Enter new name: ", name, sizeof(name)) ||
        !readFloat("Enter new score (0-100): ", &score))
    {
        printf("Invalid input.\n");
        return;
    }

    result = modifyStudentRecord(students, studentCount, id, name, score);
    if (result == STUDENT_NOT_FOUND)
    {
        printf("Student not found.\n");
    }
    else if (result == STUDENT_INVALID_DATA)
    {
        printf("Name or score is invalid.\n");
    }
    else
    {
        printf("Student modified successfully.\n");
    }
}

static void deleteStudent(void)
{
    int id;

    if (!readInt("Enter student ID to delete: ", &id))
    {
        printf("Invalid ID.\n");
        return;
    }

    if (deleteStudentRecord(students, &studentCount, id) == STUDENT_NOT_FOUND)
    {
        printf("Student not found.\n");
    }
    else
    {
        printf("Student deleted successfully.\n");
    }
}

static void showStatistics(void)
{
    StudentStatistics statistics;

    if (studentCount == 0)
    {
        printf("No student data available.\n");
        return;
    }

    statistics = calculateStatistics(students, studentCount);
    printf("Average score: %.2f\n", statistics.average);
    printf("Highest score: %.2f\n", statistics.highest);
    printf("Lowest score:  %.2f\n", statistics.lowest);
    printf("Pass rate:     %.2f%%\n", statistics.passRate);
}

int main(void)
{
    int choice;

    if (!loadStudents(DATA_FILE, students, &studentCount))
    {
        printf("Warning: existing data file is invalid. Starting with an empty list.\n");
    }
    else
    {
        printf("Loaded %d student record(s).\n", studentCount);
    }

    for (;;)
    {
        showMenu();
        if (!readInt("Please enter your choice: ", &choice))
        {
            printf("Invalid input. Please enter a menu number.\n");
            continue;
        }

        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            showAllStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            modifyStudent();
            break;
        case 5:
            deleteStudent();
            break;
        case 6:
            sortStudentsByScore(students, studentCount);
            printf("Students sorted by score from high to low.\n");
            showAllStudents();
            break;
        case 7:
            showStatistics();
            break;
        case 0:
            if (saveStudents(DATA_FILE, students, studentCount))
            {
                printf("Data saved. Goodbye.\n");
                return 0;
            }
            printf("Failed to save data. Please check the data directory.\n");
            break;
        default:
            printf("Unknown menu option.\n");
        }
    }
}
