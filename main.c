#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For string operations like strcmp

#define FILENAME "students.dat" // File to store student records
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100 // Maximum number of students the system can handle in memory

// Structure to hold student information
struct Student {
    int rollNumber;
    char name[MAX_NAME_LENGTH];
    float marks;
    // Add other fields as needed, e.g., char address[100];
};

// Function prototypes
void addStudent();
void displayAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void saveStudentsToFile(struct Student students[], int count);
int loadStudentsFromFile(struct Student students[]);
int getNextRollNumber(struct Student students[], int count); // Helper to assign unique roll numbers

// Global array to store students in memory for faster operations
// In a real-world scenario, for large datasets, you'd want to load/save in smaller chunks
struct Student students[MAX_STUDENTS];
int studentCount = 0; // Current number of students

int main() {
    int choice;

    // Load existing student records from file at startup
    studentCount = loadStudentsFromFile(students);
    if (studentCount == -1) {
        printf("Error loading student data. Starting with an empty record set.\n");
        studentCount = 0;
    } else {
        printf("%d student records loaded successfully from %s.\n", studentCount, FILENAME);
    }


    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Consume the newline character left by scanf
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 0:
                // Save all current records to file before exiting
                saveStudentsToFile(students, studentCount);
                printf("Exiting Student Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

// Function to add a new student record
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum student capacity reached. Cannot add more students.\n");
        return;
    }

    struct Student newStudent;
    newStudent.rollNumber = getNextRollNumber(students, studentCount);

    printf("Enter Student Name: ");
    fgets(newStudent.name, sizeof(newStudent.name), stdin);
    newStudent.name[strcspn(newStudent.name, "\n")] = 0; // Remove trailing newline

    printf("Enter Marks: ");
    scanf("%f", &newStudent.marks);
    while (getchar() != '\n'); // Consume newline

    students[studentCount] = newStudent;
    studentCount++;
    printf("Student added successfully! Roll Number: %d\n", newStudent.rollNumber);
    saveStudentsToFile(students, studentCount); // Save immediately after adding
}

// Function to display all student records
void displayAllStudents() {
    if (studentCount == 0) {
        printf("No student records to display.\n");
        return;
    }

    printf("\n--- All Student Records ---\n");
    printf("%-15s %-30s %-10s\n", "Roll Number", "Name", "Marks");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < studentCount; i++) {
        printf("%-15d %-30s %-10.2f\n", students[i].rollNumber, students[i].name, students[i].marks);
    }
    printf("--------------------------------------------------\n");
}

// Function to search for a student by roll number or name
void searchStudent() {
    int searchChoice;
    printf("Search by:\n");
    printf("1. Roll Number\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);
    while (getchar() != '\n'); // Consume newline

    if (studentCount == 0) {
        printf("No student records to search.\n");
        return;
    }

    int found = 0;
    if (searchChoice == 1) {
        int rollToSearch;
        printf("Enter Roll Number to search: ");
        scanf("%d", &rollToSearch);
        while (getchar() != '\n'); // Consume newline

        for (int i = 0; i < studentCount; i++) {
            if (students[i].rollNumber == rollToSearch) {
                printf("\nStudent Found:\n");
                printf("Roll Number: %d\n", students[i].rollNumber);
                printf("Name: %s\n", students[i].name);
                printf("Marks: %.2f\n", students[i].marks);
                found = 1;
                break;
            }
        }
        if (!found) {
            printf("Student with Roll Number %d not found.\n", rollToSearch);
        }
    } else if (searchChoice == 2) {
        char nameToSearch[MAX_NAME_LENGTH];
        printf("Enter Name to search: ");
        fgets(nameToSearch, sizeof(nameToSearch), stdin);
        nameToSearch[strcspn(nameToSearch, "\n")] = 0; // Remove trailing newline

        printf("\nMatching Students:\n");
        printf("%-15s %-30s %-10s\n", "Roll Number", "Name", "Marks");
        printf("--------------------------------------------------\n");
        for (int i = 0; i < studentCount; i++) {
            // Case-insensitive search using strcasecmp (or implement manually for cross-platform)
            if (strcasestr(students[i].name, nameToSearch) != NULL) { // Using strcasestr for substring search
                printf("%-15d %-30s %-10.2f\n", students[i].rollNumber, students[i].name, students[i].marks);
                found = 1;
            }
        }
        if (!found) {
            printf("No student with name containing '%s' found.\n", nameToSearch);
        }
        printf("--------------------------------------------------\n");
    } else {
        printf("Invalid search choice.\n");
    }
}

// Function to update a student record
void updateStudent() {
    if (studentCount == 0) {
        printf("No student records to update.\n");
        return;
    }

    int rollToUpdate;
    printf("Enter Roll Number of student to update: ");
    scanf("%d", &rollToUpdate);
    while (getchar() != '\n'); // Consume newline

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollToUpdate) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        printf("Student Found (Roll Number: %d, Name: %s, Marks: %.2f)\n",
               students[foundIndex].rollNumber, students[foundIndex].name, students[foundIndex].marks);

        printf("Enter New Name (leave blank to keep current): ");
        char newName[MAX_NAME_LENGTH];
        fgets(newName, sizeof(newName), stdin);
        newName[strcspn(newName, "\n")] = 0; // Remove trailing newline
        if (strlen(newName) > 0) {
            strcpy(students[foundIndex].name, newName);
        }

        printf("Enter New Marks (enter -1 to keep current): ");
        float newMarks;
        scanf("%f", &newMarks);
        while (getchar() != '\n'); // Consume newline
        if (newMarks != -1.0) {
            students[foundIndex].marks = newMarks;
        }

        printf("Student record updated successfully!\n");
        saveStudentsToFile(students, studentCount); // Save immediately after updating
    } else {
        printf("Student with Roll Number %d not found.\n", rollToUpdate);
    }
}

// Function to delete a student record
void deleteStudent() {
    if (studentCount == 0) {
        printf("No student records to delete.\n");
        return;
    }

    int rollToDelete;
    printf("Enter Roll Number of student to delete: ");
    scanf("%d", &rollToDelete);
    while (getchar() != '\n'); // Consume newline

    int foundIndex = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollToDelete) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        // Shift elements to the left to "delete" the record
        for (int i = foundIndex; i < studentCount - 1; i++) {
            students[i] = students[i + 1];
        }
        studentCount--;
        printf("Student with Roll Number %d deleted successfully!\n", rollToDelete);
        saveStudentsToFile(students, studentCount); // Save immediately after deleting
    } else {
        printf("Student with Roll Number %d not found.\n", rollToDelete);
    }
}

// Function to save student records to a file
void saveStudentsToFile(struct Student students[], int count) {
    FILE *fp;
    fp = fopen(FILENAME, "wb"); // Open in binary write mode

    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }

    // Write the number of students first
    fwrite(&count, sizeof(int), 1, fp);

    // Write each student structure
    fwrite(students, sizeof(struct Student), count, fp);

    fclose(fp);
    // printf("Student data saved to %s successfully.\n", FILENAME); // Uncomment for debugging
}

// Function to load student records from a file
int loadStudentsFromFile(struct Student students[]) {
    FILE *fp;
    fp = fopen(FILENAME, "rb"); // Open in binary read mode

    if (fp == NULL) {
        // File might not exist yet, which is fine for the first run
        return 0;
    }

    int count = 0;
    // Read the number of students
    if (fread(&count, sizeof(int), 1, fp) != 1) {
        perror("Error reading student count from file");
        fclose(fp);
        return -1; // Indicate error
    }

    // Read all student structures
    if (fread(students, sizeof(struct Student), count, fp) != count) {
        perror("Error reading student data from file");
        fclose(fp);
        return -1; // Indicate error
    }

    fclose(fp);
    return count; // Return the number of students loaded
}

// Helper function to get the next available roll number
int getNextRollNumber(struct Student students[], int count) {
    if (count == 0) {
        return 1001; // Starting roll number
    }

    int maxRoll = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber > maxRoll) {
            maxRoll = students[i].rollNumber;
        }
    }
    return maxRoll + 1;
}

// Note: For Windows, you might need to include <conio.h> for getch() or use system("cls") for clearing screen.
// For `strcasestr` (case-insensitive substring search) on Windows, you might need `_strnicmp` or a manual implementation.
// On Linux/macOS, `strcasestr` is typically available.