//FILE ALLOCATION STRATEGIES - LINKED
#include <stdio.h>

typedef struct{
    char empName[20];
    int age;
    float salary;
}Person;

void displayRecord(FILE *file, int recordNumber);

int main() {
    Person employee;
    int i, numberOfRecords, recordNumber;
    FILE *file;

    printf("How many records: ");
    scanf("%d", &numberOfRecords);

    file = fopen("PEOPLE.txt", "wb");
    if (file == NULL) {
        printf("Error opening file!");
        return 1;
    }

    for (i = 0; i < numberOfRecords; i++) {
        printf("Enter the employee information %d (EmpName, Age, Salary): ", i + 1);
        scanf("%s %d %f", employee.empName, &employee.age, &employee.salary);
        fwrite(&employee, sizeof(employee), 1, file);
    }
    fclose(file);

    file = fopen("PEOPLE.txt", "rb");
    if (file == NULL) {
        printf("Error opening file!");
        return 1;
    }

    while (recordNumber >= 0) {
        printf("Which record do you want (0 to %d)? ", numberOfRecords-1);
        scanf("%d", &recordNumber);
        displayRecord(file, recordNumber);
    }

    fclose(file);
    return 0;
}

void displayRecord(FILE *file, int recordNumber) {
    Person employee;
    int result;

    fseek(file, recordNumber * sizeof(employee), SEEK_SET);
    result = fread(&employee, sizeof(employee), 1, file);

    if (result == 1) {
        printf("\nRECORD %d\n", recordNumber);
        printf("Given name: %s\n", employee.empName);
        printf("Age: %d years\n", employee.age);
        printf("Current salary: $%8.2f\n\n", employee.salary);
    } else {
        printf("\nRECORD %d not found!\n\n", recordNumber);
    }
}
