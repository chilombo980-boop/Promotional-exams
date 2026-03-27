/*
========================================================
STUDENT RECORD MANAGEMENT SYSTEM
Course: ICT113 – C Programming
Project Title: Student Record Management System
========================================================

PROGRAM DESCRIPTION:
This is a console-based application written in C that allows
users to manage student academic records. The system is 
menu-driven and provides options to add, view, search, 
calculate results, and save student data to a file.

PROGRAM FEATURES:
1. Add Student
2. View Students
3. Search Student
4. Calculate Results
5. Save Results to File
6. Exit

PROGRAMMING CONCEPTS USED:
- Structures (to store student data)
- Arrays (to store multiple students)
- Functions (modular programming)
- Loops (iteration through records)
- Conditional statements (grading system)
- File handling (saving data to file)

========================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100   // Maximum number of students

/*
--------------------------------------------------------
STRUCTURE DECLARATION
This structure stores all student details
--------------------------------------------------------
*/
struct Student {
    char name[50];
    int studentNo;
    int math, english, computer;
};

/*
Global array to store student records
'count' keeps track of number of students entered
*/
struct Student students[MAX];
int count = 0;

/*
--------------------------------------------------------
FUNCTION PROTOTYPES
--------------------------------------------------------
*/
void addStudent();
void viewStudents();
void searchStudent();
void calculateResults();
void saveToFile();

/*
--------------------------------------------------------
MAIN FUNCTION
Controls menu and user interaction
--------------------------------------------------------
*/
int main() {
    int choice;

    do {
        printf("\n==============================\n");
        printf(" STUDENT MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Calculate Results\n");
        printf("5. Save Results to File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Menu selection using switch
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                calculateResults();
                break;
            case 5:
                saveToFile();
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}

/*
--------------------------------------------------------
FUNCTION: addStudent
Purpose:
Allows user to input student details and store them
--------------------------------------------------------
*/
void addStudent() {
    if(count >= MAX) {
        printf("Student limit reached!\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", students[count].name);

    printf("Enter Student Number: ");
    scanf("%d", &students[count].studentNo);

    printf("Math Marks: ");
    scanf("%d", &students[count].math);

    printf("English Marks: ");
    scanf("%d", &students[count].english);

    printf("Computer Marks: ");
    scanf("%d", &students[count].computer);

    count++;  // Increase student count
    printf("Student added successfully!\n");
}

/*
--------------------------------------------------------
FUNCTION: viewStudents
Purpose:
Displays all stored student records in table format
--------------------------------------------------------
*/
void viewStudents() {
    if(count == 0) {
        printf("No student records available.\n");
        return;
    }

    printf("\n-------------------------------------------------------\n");
    printf("Name\t\tStudent No\tMath\tEnglish\tComputer\n");
    printf("-------------------------------------------------------\n");

    // Loop through all students
    for(int i = 0; i < count; i++) {
        printf("%s\t%d\t\t%d\t%d\t%d\n",
               students[i].name,
               students[i].studentNo,
               students[i].math,
               students[i].english,
               students[i].computer);
    }
}

/*
--------------------------------------------------------
FUNCTION: searchStudent
Purpose:
Searches for a student using student number
--------------------------------------------------------
*/
void searchStudent() {
    int number, found = 0;

    printf("Enter Student Number to search: ");
    scanf("%d", &number);

    // Loop to find matching student
    for(int i = 0; i < count; i++) {
        if(students[i].studentNo == number) {
            printf("\nStudent Found\n");
            printf("Name: %s\n", students[i].name);
            printf("Student Number: %d\n", students[i].studentNo);
            printf("Math: %d\n", students[i].math);
            printf("English: %d\n", students[i].english);
            printf("Computer: %d\n", students[i].computer);
            found = 1;
            break;
        }
    }

    if(!found) {
        printf("Student not found.\n");
    }
}

/*
--------------------------------------------------------
FUNCTION: calculateResults
Purpose:
Calculates total, average and grade for each student
Grading System:
80–100 = A
70–79  = B
60–69  = C
50–59  = D
Below 50 = F
--------------------------------------------------------
*/
void calculateResults() {
    if(count == 0) {
        printf("No student records available.\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        int total = students[i].math + students[i].english + students[i].computer;
        float avg = total / 3.0;
        char grade;

        // Determine grade using conditions
        if(avg >= 80)
            grade = 'A';
        else if(avg >= 70)
            grade = 'B';
        else if(avg >= 60)
            grade = 'C';
        else if(avg >= 50)
            grade = 'D';
        else
            grade = 'F';

        printf("\nName: %s\n", students[i].name);
        printf("Total: %d\n", total);
        printf("Average: %.2f\n", avg);
        printf("Grade: %c\n", grade);
    }
}

/*
--------------------------------------------------------
FUNCTION: saveToFile
Purpose:
Saves all student records into a file (students.txt)
Uses file handling functions:
- fopen()
- fprintf()
- fclose()
--------------------------------------------------------
*/
void saveToFile() {
    FILE *file = fopen("students.txt", "w");

    if(file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for(int i = 0; i < count; i++) {
        int total = students[i].math + students[i].english + students[i].computer;
        float avg = total / 3.0;
        char grade;

        // Determine grade again for saving
        if(avg >= 80)
            grade = 'A';
        else if(avg >= 70)
            grade = 'B';
        else if(avg >= 60)
            grade = 'C';
        else if(avg >= 50)
            grade = 'D';
        else
            grade = 'F';

        fprintf(file, "Name: %s\n", students[i].name);
        fprintf(file, "Student Number: %d\n", students[i].studentNo);
        fprintf(file, "Math: %d English: %d Computer: %d\n",
                students[i].math,
                students[i].english,
                students[i].computer);
        fprintf(file, "Total: %d Average: %.2f Grade: %c\n\n",
                total, avg, grade);
    }

    fclose(file);
    printf("Records saved to students.txt successfully!\n");
}
