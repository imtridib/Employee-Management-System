#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define MAX_NAME_LEN 50
#define MAX_POST_LEN 50
#define MAX_DEPT_LEN 10

const char* fileName = "Employee.txt";

typedef struct {
    int EmpID;
    char EmpName[MAX_NAME_LEN];
    char Post[MAX_POST_LEN];
    char Department[MAX_DEPT_LEN];
    float Salary;
    float Rating;  // New field for Employee Rating
} Employee;

// Function to calculate GCD (Number Theory)
int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

// Function to get employee ID
int GetID(const Employee* emp) {
    return emp->EmpID;
}

// Function to get employee Department
const char* GetDepartment(const Employee* emp) {
    return emp->Department;
}

void ReadData(Employee* emp) {
    printf("\nEmployee ID: ");
    scanf("%d", &emp->EmpID);
    printf("Employee Name: ");
    getchar(); // consume newline
    fgets(emp->EmpName, MAX_NAME_LEN, stdin);
    emp->EmpName[strcspn(emp->EmpName, "\n")] = 0; // remove newline

    printf("Employee's Post: ");
    fgets(emp->Post, MAX_POST_LEN, stdin);
    emp->Post[strcspn(emp->Post, "\n")] = 0; // remove newline

    printf("Employee's Department: ");
    fgets(emp->Department, MAX_DEPT_LEN, stdin);
    emp->Department[strcspn(emp->Department, "\n")] = 0; // remove newline

    printf("Salary: ");
    scanf("%f", &emp->Salary);

    printf("Rating (0.0 - 5.0): ");  // New input for Rating
    scanf("%f", &emp->Rating);
}

void DisplayRecord(const Employee* emp) {
    printf("\n_______________________________");
    printf("\n%5d%15s%15s%15s%8.2f%8.2f",
           emp->EmpID, emp->EmpName, emp->Post, emp->Department, emp->Salary, emp->Rating);
}

// Function to compare Employees by ID (for Binary Search)
int CompareByID(const void* a, const void* b) {
    return ((Employee*)a)->EmpID - ((Employee*)b)->EmpID;
}

// Function to compare Employees by Salary (for MaxSalaryUnderBudget)
int CompareBySalary(const void* a, const void* b) {
    float diff = ((Employee*)a)->Salary - ((Employee*)b)->Salary;
    return (diff > 0) - (diff < 0);
}

// Binary Search to find Employee by ID
Employee* BinarySearch(Employee* arr, int size, int ID) {
    int low = 0, high = size - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (arr[mid].EmpID == ID) return &arr[mid];
        if (arr[mid].EmpID < ID) low = mid + 1;
        else high = mid - 1;
    }
    return NULL;
}

// Greedy Algorithm to find maximum salary sum under a budget
void MaxSalaryUnderBudget(Employee* employees, int size, float budget) {
    qsort(employees, size, sizeof(Employee), CompareBySalary);
    float total = 0.0;
    printf("\nEmployees under budget %.2f:\n", budget);
    for (int i = 0; i < size; i++) {
        if (total + employees[i].Salary <= budget) {
            total += employees[i].Salary;
            DisplayRecord(&employees[i]);
        }
    }
    printf("\nTotal Salary under budget: %.2f", total);
}

int main() {
    Employee emp, e;
    Employee employees[100]; // For storing all employees temporarily
    int empCount = 0;
    char option, ch, Dept[MAX_NAME_LEN];
    int ID, isFound, recordNo;
    FILE* file;
    FILE* temp;

    do {
        printf("******* Menu ********");
        printf("\nEnter your option");
        printf("\n1 => Add a new record");
        printf("\n2 => Search record from employee ID");
        printf("\n3 => List Employee of particular department");
        printf("\n4 => Display all employees");
        printf("\n5 => Update record of an employee");
        printf("\n6 => Delete record of particular employee");
        printf("\n7 => Find Employees by Rating");
        printf("\n8 => GCD of Employee IDs");
        printf("\n9 => Max Salary under Budget");
        printf("\n10 => Exit from the program\n");
        printf("********************\n");
        scanf(" %c", &option);

        switch (option) {
        case '1':
            ReadData(&emp);
            file = fopen(fileName, "r+b");
            if (!file) {
                file = fopen(fileName, "w+b");
                if (!file) {
                    perror("Error opening file");
                    return 1;
                }
            }
            isFound = 0;
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (GetID(&e) == GetID(&emp)) {
                    printf("This ID already exists... Try another ID");
                    isFound = 1;
                    break;
                }
            }
            if (isFound) {
                fclose(file);
                break;
            }
            fseek(file, 0, SEEK_END);
            fwrite(&emp, sizeof(Employee), 1, file);
            printf("\nNew record has been added successfully...");
            fclose(file);
            break;

        case '2':
            isFound = 0;
            printf("\nEnter ID of an employee to be searched: ");
            scanf("%d", &ID);
            file = fopen(fileName, "rb");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (GetID(&e) == ID) {
                    printf("\nThe record found....\n");
                    printf("\n%5s%15s%15s%15s%8s%8s",
                           "ID", "Name", "Post", "Department", "Salary", "Rating");
                    DisplayRecord(&e);
                    isFound = 1;
                    break;
                }
            }
            if (!isFound) printf("\nData not found for employee ID #%d", ID);
            fclose(file);
            break;

        case '3':
            isFound = 0;
            printf("Enter department name to list employees within it: ");
            getchar(); // consume newline
            fgets(Dept, MAX_NAME_LEN, stdin);
            Dept[strcspn(Dept, "\n")] = 0; // remove newline

            file = fopen(fileName, "rb");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (strcmp(GetDepartment(&e), Dept) == 0) {
                    printf("\nThe record found for this department\n");
                    printf("\n%5s%15s%15s%15s%8s%8s",
                           "ID", "Name", "Post", "Department", "Salary", "Rating");
                    DisplayRecord(&e);
                    isFound = 1;
                }
            }
            if (!isFound) printf("\nData not found for department %s", Dept);
            fclose(file);
            break;

        case '4':
            printf("\nRecord for employees");
            file = fopen(fileName, "rb");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            int counter = 0;
            printf("\n%5s%15s%15s%15s%8s%8s",
                   "ID", "Name", "Post", "Department", "Salary", "Rating");
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (counter < 100) {
                    employees[counter++] = e; // Store employee for further operations
                }
                DisplayRecord(&e);
            }
            empCount = counter;
            printf("\n%d records found......", counter);
            fclose(file);
            break;

        case '5':
            printf("\nFile is being modified....");
            printf("\nEnter employee ID to be updated: ");
            scanf("%d", &ID);
            isFound = 0;
            file = fopen(fileName, "r+b");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (GetID(&e) == ID) {
                    printf("\nThe old record of this employee ID is as follows");
                    printf("\n%5s%15s%15s%15s%8s%8s",
                           "ID", "Name", "Post", "Department", "Salary", "Rating");
                    DisplayRecord(&e);

                    printf("\nEnter new data of the record\n");
                    ReadData(&emp);

                    fseek(file, -(long)sizeof(Employee), SEEK_CUR);
                    fwrite(&emp, sizeof(Employee), 1, file);
                    isFound = 1;
                    printf("\nRecord updated successfully...");
                    break;
                }
            }
            if (!isFound) printf("\nNo record found for employee ID #%d", ID);
            fclose(file);
            break;

        case '6':
            printf("\nDeleting record from the file....");
            printf("\nEnter employee ID to be deleted: ");
            scanf("%d", &ID);
            isFound = 0;
            file = fopen(fileName, "rb");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            temp = fopen("temp.txt", "wb");
            if (!temp) {
                perror("Error opening temp file");
                fclose(file);
                return 1;
            }
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (GetID(&e) == ID) {
                    printf("The following record will be deleted:\n");
                    DisplayRecord(&e);
                    isFound = 1;
                } else {
                    fwrite(&e, sizeof(Employee), 1, temp);
                }
            }
            fclose(file);
            fclose(temp);
            remove(fileName);
            rename("temp.txt", fileName);
            if (isFound) printf("\nRecord deleted successfully...");
            else printf("\nNo record found for employee ID #%d", ID);
            break;

        case '7':
            printf("\nFinding Employees by Rating...");
            float minRating, maxRating;
            printf("\nEnter minimum rating: ");
            scanf("%f", &minRating);
            printf("Enter maximum rating: ");
            scanf("%f", &maxRating);

            file = fopen(fileName, "rb");
            if (!file) {
                perror("Error opening file");
                return 1;
            }
            isFound = 0;
            while (fread(&e, sizeof(Employee), 1, file)) {
                if (e.Rating >= minRating && e.Rating <= maxRating) {
                    DisplayRecord(&e);
                    isFound = 1;
                }
            }
            if (!isFound) printf("\nNo employees found within rating range %.2f - %.2f", minRating, maxRating);
            fclose(file);
            break;

        case '8':
            printf("\nCalculating GCD of Employee IDs...");
            int id1, id2;
            printf("\nEnter first employee ID: ");
            scanf("%d", &id1);
            printf("Enter second employee ID: ");
            scanf("%d", &id2);

            printf("GCD of %d and %d is: %d", id1, id2, GCD(id1, id2));
            break;

        case '9':
            printf("\nMax Salary under Budget...");
            float budget;
            printf("\nEnter your budget: ");
            scanf("%f", &budget);

            MaxSalaryUnderBudget(employees, empCount, budget);
            break;

        case '10':
            exit(0);

        default:
            printf("\nInvalid option... Please try again.");
        }

        printf("\nDo you want to continue with the program (Y/N): ");
        scanf(" %c", &ch);

    } while (ch == 'y' || ch == 'Y');

    return 0;
}
