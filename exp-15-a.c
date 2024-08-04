//FILE ALLOCATION STRATEGIES - SEQUENTIAL
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int studentNumber;
    char name[25];
    int mark1, mark2, mark3;
} Student;

void display(FILE *file);
int search(FILE *file, int studentNumber);

int main() {
    int i, numberOfRecords, studentNumberKey, option;
    FILE *file;
    Student student;


    printf("How many records? ");
    scanf("%d", &numberOfRecords);

    file = fopen("stud.dat", "wb");
    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    for (i = 0; i < numberOfRecords; i++) {
        printf("Enter the student information %d (studentNumber, Name, Mark1, Mark2, Mark3): ", i + 1);
        scanf("%d %s %d %d %d", &student.studentNumber, student.name, &student.mark1, &student.mark2, &student.mark3);
        fwrite(&student, sizeof(student), 1, file);
    }
    fclose(file);

    file = fopen("stud.dat", "rb");
    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    do {
        printf("1 - DISPLAY\n2 - SEARCH\n3 - EXIT\nYOUR OPTION: ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                printf("\nStudent Records in the file:\n");
                display(file);
                break;
            case 2:
                printf("Enter student number to be searched: ");
                scanf("%d", &studentNumberKey);
                search(file, studentNumberKey);
                break;
            case 3:
                printf("Exit! Press any key.");
                break;
            default:
                printf("Invalid option! Try again.\n");
                break;
        }
    } while (option != 3);

    fclose(file);
    return 0;
}

void display(FILE *file) {
    Student student;
    rewind(file);
    while (fread(&student, sizeof(student), 1, file)) {
        printf("%d\t%s\t%d\t%d\t%d\n", student.studentNumber, student.name, student.mark1, student.mark2, student.mark3);
    }
}

int search(FILE *file, int studentNumberKey) {
    Student student;
    rewind(file);
    while (fread(&student, sizeof(student), 1, file)) {
        if (student.studentNumber == studentNumberKey) {
            printf("Success! Record found in the file.\n");
            printf("%d\t%s\t%d\t%d\t%d\n", student.studentNumber, student.name, student.mark1, student.mark2, student.mark3);
        }
        else {
            printf("Failure! Record %d not found.\n", studentNumberKey);
        }
    }
    return 0;
}
