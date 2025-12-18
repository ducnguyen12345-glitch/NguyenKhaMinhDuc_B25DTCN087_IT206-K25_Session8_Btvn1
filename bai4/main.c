#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Đọc danh sách sinh viên từ file, trả về số sinh viên đã đọc, hoặc -1 nếu lỗi
int loadFromFile(const char *filename, struct Student *students, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;

    char line[256];
    int count = 0;

    // Skip possible header line if present
    if (fgets(line, sizeof(line), f)) {
        // detect header by checking if line contains non-digit at start (e.g. "ID")
        char tmp[8];
        if (sscanf(line, "%7s", tmp) == 1) {
            int isHeader = 0;
            if (strcmp(tmp, "ID") == 0 || strcmp(tmp, "Id") == 0) isHeader = 1;
            if (!isHeader) {
                // parse first line as data
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
        // trim leading spaces
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

int main() {
    struct Student students[100];
    int max = 100;
    int n;

    // Try current folder first, then bai3 folder
    n = loadFromFile("students.txt", students, max);
    if (n < 0) {
        n = loadFromFile("..\\bai3\\students.txt", students, max);
        if (n < 0) {
            printf("Khong the mo file students.txt\n");
            return 1;
        }
    }

    printf("Danh sách đọc từ file:\n");
    for (int i = 0; i < n; i++) {
        // print in the requested compact format
        printf("%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    return 0;
}
