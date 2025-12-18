#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

int main() {
    struct Student students[5];
    int count = 0;
    char line[200];

    printf("Nhập tối đa 5 sinh viên. Mỗi dòng: ID Name Age GPA\n");
    printf("Ví dụ: 1 An 20 8.0\n");

    for (int i = 0; i < 5; ) {
        printf("Nhập sinh viên %d (hoặc nhấn Enter để kết thúc): ", i+1);
        if (!fgets(line, sizeof(line), stdin)) break;
        // trim leading spaces
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '\n' || *p == '\0') break; // blank line -> finish

        int id, age; float gpa; char name[50];
        int n = sscanf(p, "%d %49s %d %f", &id, name, &age, &gpa);
        if (n != 4) {
            printf("Dữ liệu không hợp lệ. Hãy nhập theo định dạng: ID Name Age GPA\n");
            continue; // retry same index
        }

        students[count].id = id;
        strncpy(students[count].name, name, sizeof(students[count].name)-1);
        students[count].name[sizeof(students[count].name)-1] = '\0';
        students[count].age = age;
        students[count].gpa = gpa;
        count++;
        i++;
    }

    // In danh sách
    printf("\nID   Name     Age   GPA\n");
    for (int i = 0; i < count; i++) {
        // print similar format as sample
        printf("%-4d %-7s %-5d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    return 0;
}
