#include <stdio.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 20

typedef struct
{
    int id;
    char name[NAME_LENGTH];
    float score;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void showMenu(void)
{
    printf("\n");
    printf("====================================\n");
    printf(" Student Management System\n");
    printf("====================================\n");
    printf("1. Add student\n");
    printf("2. Show all students\n");
    printf("3. Search student\n");
    printf("4. Modify student\n");
    printf("5. Delete student\n");
    printf("6. Sort by score\n");
    printf("7. Show statistics\n");
    printf("0. Exit\n");
    printf("====================================\n");
    printf("Please enter your choice: ");
}

void addStudent(void)
{
    Student newStudent;

    if (studentCount >= MAX_STUDENTS)
    {
        printf("Student list is full.\n");
        return;
    }

    printf("Enter student ID: ");
    if (scanf("%d", &newStudent.id) != 1)
    {
        printf("Invalid student ID.\n");
        clearInputBuffer();
        return;
    }

    printf("Enter student name: ");
    scanf("%19s", newStudent.name);

    printf("Enter student score: ");
    if (scanf("%f", &newStudent.score) != 1)
    {
        printf("Invalid score.\n");
        clearInputBuffer();
        return;
    }

    students[studentCount] = newStudent;
    studentCount++;

    printf("Student added successfully.\n");
}

void showAllStudents(void)
{
    int i;

    if (studentCount == 0)
    {
        printf("No student data available.\n");
        return;
    }

    printf("\n------------------------------------\n");
    printf("%-10s %-15s %-10s\n", "ID", "Name", "Score");
    printf("------------------------------------\n");

    for (i = 0; i < studentCount; i++)
    {
        printf("%-10d %-15s %-10.2f\n",
               students[i].id,
               students[i].name,
               students[i].score);
    }

    printf("------------------------------------\n");
}

int main(void)
{
    int choice;

    do
    {
        showMenu();

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
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
            printf("Search student: to be implemented.\n");
            break;
        case 4:
            printf("Modify student: to be implemented.\n");
            break;
        case 5:
            printf("Delete student: to be implemented.\n");
            break;
        case 6:
            printf("Sort by score: to be implemented.\n");
            break;
        case 7:
            printf("Show statistics: to be implemented.\n");
            break;
        case 0:
            printf("Goodbye.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
