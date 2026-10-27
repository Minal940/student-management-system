
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int rollNo;
    char name[50];
    float marks;
    struct Student *next;
} Student;

Student *head = NULL;

// Add a new student
void addStudent() {
    Student *newStudent = malloc(sizeof(Student));

    if (newStudent == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter roll number: ");
    if (scanf("%d", &newStudent->rollNo) != 1) {
        printf("Invalid roll number!\n");
        while (getchar() != '\n');
        free(newStudent);
        return;
    }

    Student *temp = head;
    while (temp != NULL) {
        if (temp->rollNo == newStudent->rollNo) {
            printf("Roll number already exists!\n");
            free(newStudent);
            return;
        }
        temp = temp->next;
    }

    printf("Enter student name: ");
    scanf(" %49[^\n]", newStudent->name);

    printf("Enter marks (0-100): ");
    if (scanf("%f", &newStudent->marks) != 1 ||
        newStudent->marks < 0 || newStudent->marks > 100) {
        printf("Invalid marks!\n");
        while (getchar() != '\n');
        free(newStudent);
        return;
    }

    newStudent->next = NULL;

    if (head == NULL) {
        head = newStudent;
    } else {
        temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }

    printf("Student added successfully!\n");
}

// Display all students
void displayStudents() {
    Student *temp = head;

    if (temp == NULL) {
        printf("No student records found.\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    printf("%-10s %-25s %-10s\n",
           "Roll No", "Name", "Marks");

    while (temp != NULL) {
        printf("%-10d %-25s %-10.2f\n",
               temp->rollNo, temp->name, temp->marks);
        temp = temp->next;
    }
}

// Search student by roll number
void searchStudent() {
    int roll;
    printf("Enter roll number to search: ");

    if (scanf("%d", &roll) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    Student *temp = head;

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            printf("Student found!\n");
            printf("Roll No: %d\n", temp->rollNo);
            printf("Name: %s\n", temp->name);
            printf("Marks: %.2f\n", temp->marks);
            return;
        }
        temp = temp->next;
    }

    printf("Student not found.\n");
}

// Delete student by roll number
void deleteStudent() {
    int roll;

    printf("Enter roll number to delete: ");
    if (scanf("%d", &roll) != 1) {
        printf("Invalid input!\n");
        while (getchar() != '\n');
        return;
    }

    Student *temp = head;
    Student *prev = NULL;

    while (temp != NULL && temp->rollNo != roll) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);
    printf("Student deleted successfully!\n");
}

// Sort students by marks (ascending order)
void sortStudents() {
    if (head == NULL || head->next == NULL) {
        printf("Not enough records to sort.\n");
        return;
    }

    int swapped;
    Student *ptr;
    Student *last = NULL;

    do {
        swapped = 0;
        ptr = head;

        while (ptr->next != last) {
            if (ptr->marks > ptr->next->marks) {
                int roll = ptr->rollNo;
                ptr->rollNo = ptr->next->rollNo;
                ptr->next->rollNo = roll;

                char name[50];
                strcpy(name, ptr->name);
                strcpy(ptr->name, ptr->next->name);
                strcpy(ptr->next->name, name);

                float marks = ptr->marks;
                ptr->marks = ptr->next->marks;
                ptr->next->marks = marks;

                swapped = 1;
            }
            ptr = ptr->next;
        }

        last = ptr;
    } while (swapped);

    printf("Students sorted by marks successfully!\n");
}

// Release allocated memory
void freeStudents() {
    Student *temp;

    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int choice;

    do {
        printf("\n===== STUDENT RECORD MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Sort by Marks\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                sortStudents();
                break;
            case 6:
                freeStudents();
                printf("Thank you for using the system!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
