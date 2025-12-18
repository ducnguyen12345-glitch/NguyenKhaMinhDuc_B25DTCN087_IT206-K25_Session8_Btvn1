#include <stdio.h>
#include <string.h>

// Student struct
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Load students from a plain text file (ID Name Age GPA per line).
// Returns number of students read, or -1 on error.
int loadFromFile(const char *filename, struct Student *students, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    char line[256];
    int count = 0;

    // Optionally skip header
    if (fgets(line, sizeof(line), f)) {
        char first[8];
        if (sscanf(line, "%7s", first) == 1) {
            if (strcmp(first, "ID") == 0 || strcmp(first, "Id") == 0) {
                // header detected, continue to next lines
            } else {
                // first line is data; parse it
                int id, age; float gpa; char name[50];
                if (sscanf(line, "%d %49s %d %f", &id, name, &age, &gpa) == 4) {
                    if (count < max) {
                        students[count].id = id;
                        strncpy(students[count].name, name, sizeof(students[count].name)-1);
                        students[count].name[sizeof(students[count].name)-1] = '\0';
                        students[count].age = age;
                        students[count].gpa = gpa;
                        count++;
                    }
                }
            }
        }
    }

    while (count < max && fgets(line, sizeof(line), f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\n' || *p == '\0') continue;
        int id, age; float gpa; char name[50];
        if (sscanf(p, "%d %49s %d %f", &id, name, &age, &gpa) == 4) {
            students[count].id = id;
            strncpy(students[count].name, name, sizeof(students[count].name)-1);
            students[count].name[sizeof(students[count].name)-1] = '\0';
            students[count].age = age;
            students[count].gpa = gpa;
            count++;
        }
    }

    fclose(f);
    return count;
}

// Read an integer ID from stdin with prompt. Returns 1 on success, 0 on failure.
int readIdFromUser(int *outId) {
    char buf[64];
    printf("Nhập ID cần tìm: ");
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    // trim
    char *p = buf;
    while (*p == ' ' || *p == '\t') p++;
    if (*p == '\n' || *p == '\0') return 0;
    int id;
    if (sscanf(p, "%d", &id) == 1) {
        *outId = id;
        return 1;
    }
    return 0;
}

// Find student by ID. Returns index or -1 if not found.
int findStudentById(struct Student *students, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (students[i].id == id) return i;
    }
    return -1;
}

int main() {
    struct Student students[100];
    int n = loadFromFile("students.txt", students, 100);
    if (n < 0) {
        // try bai3 folder
        n = loadFromFile("..\\bai3\\students.txt", students, 100);
        if (n < 0) {
            printf("Không tìm thấy file students.txt để đọc dữ liệu.\n");
            return 1;
        }
    }

    int id;
    if (!readIdFromUser(&id)) {
        printf("ID không hợp lệ.\n");
        return 1;
    }

    printf("\nKết quả tìm kiếm:\n");
    if (id < 0) {
        printf("Không tìm thấy\n");
        return 0;
    }

    int idx = findStudentById(students, n, id);
    if (idx >= 0) {
        printf("ID: %d, Name: %s, Age: %d, GPA: %.1f\n", students[idx].id, students[idx].name, students[idx].age, students[idx].gpa);
    } else {
        printf("Không tìm thấy\n");
    }

    return 0;
}
