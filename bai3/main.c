#include <stdio.h>
#include <string.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

// Lưu danh sách sinh viên vào file text
int saveToFile(const char *filename, struct Student *students, int count) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;

    // Header
    fprintf(f, "ID Name Age GPA\n");

    for (int i = 0; i < count; i++) {
        // Lưu theo định dạng giống output: ID Name Age GPA (space-separated)
        fprintf(f, "%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    fclose(f);
    return 0;
}

int main() {
    struct Student students[3] = {
        {1, "Nguyen Anh Tu", 20, 3.5},
        {2, "Tran Mai Lan", 21, 3.8},
        {3, "Le Minh Tuan", 22, 3.2}
    };

    const char *outfile = "students.txt"; // will be created in bai3 folder
    int res = saveToFile(outfile, students, 3);
    if (res == 0) {
        printf("Da luu danh sach vao file: %s\n", outfile);
    } else {
        printf("Loi khi mo file de luu.\n");
        return 1;
    }

    // Optional: in ra màn hình để xác nhận
    printf("\nID   Name                 Age   GPA\n");
    for (int i = 0; i < 3; i++) {
        printf("%-4d %-20s %-5d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }

    return 0;
}
