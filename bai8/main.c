#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Read students from a file with lines: ID Name Age GPA
// Returns number read, or -1 on error.
int loadFromFile(const char *filename, struct Student *students, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char line[256];
    int count = 0;

    // Optionally skip header if present
    if (fgets(line, sizeof(line), f)) {
        char first[8];
        if (sscanf(line, "%7s", first) == 1) {
            if (strcmp(first, "ID") == 0 || strcmp(first, "Id") == 0) {
                // skip header
            } else {
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

int main() {
    char filename[256];
    printf("Nhập tên file: ");
    if (!fgets(filename, sizeof(filename), stdin)) return 1;
    // trim newline
    size_t L = strlen(filename);
    if (L > 0 && (filename[L-1] == '\n' || filename[L-1] == '\r')) filename[L-1] = '\0';
    // determine class name from filename (e.g., classA.txt -> lớp A)
    char classname[64] = "";
    if (sscanf(filename, "class%1[a-zA-Z]", classname) == 1) {
        // classname holds letter like A, B, C
    }

    struct Student students[200];
    int n = loadFromFile(filename, students, 200);
    if (n < 0) {
        printf("Không thể mở file: %s\n", filename);
        return 1;
    }

    if (classname[0] != '\0')
        printf("Danh sách sinh viên lớp %s:\n", classname);
    else
        printf("Danh sách sinh viên (file: %s):\n", filename);

    for (int i = 0; i < n; i++) {
        printf("%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    return 0;
}
