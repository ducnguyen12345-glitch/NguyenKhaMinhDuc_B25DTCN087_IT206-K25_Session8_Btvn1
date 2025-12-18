#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
};

/* Helpers */
void printStudents(const struct Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

int loadFromFile(const char *filename, struct Student *students, int max) {
    FILE *f = fopen(filename, "r");
    if (!f) return -1;
    char line[256];
    int count = 0;
    // skip optional header
    if (fgets(line, sizeof(line), f)) {
        char first[8];
        if (sscanf(line, "%7s", first) == 1) {
            if (strcmp(first, "ID") == 0 || strcmp(first, "Id") == 0) {
                // header -> ignore
            } else {
                int id, age; double gpa; char name[50];
                if (sscanf(line, "%d %49s %d %lf", &id, name, &age, &gpa) == 4) {
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
        int id, age; double gpa; char name[50];
        if (sscanf(p, "%d %49s %d %lf", &id, name, &age, &gpa) == 4) {
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

int saveToFile(const char *filename, struct Student *students, int count) {
    FILE *f = fopen(filename, "w");
    if (!f) return -1;
    fprintf(f, "ID Name Age GPA\n");
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    fclose(f);
    return 0;
}

int findStudentById(const struct Student *students, int count, int id) {
    for (int i = 0; i < count; i++) if (students[i].id == id) return i;
    return -1;
}

int addStudent(struct Student *students, int *count, int max, struct Student s) {
    if (*count >= max) return 2;
    if (findStudentById(students, *count, s.id) != -1) return 1;
    students[*count] = s; (*count)++; return 0;
}

int deleteStudentById(struct Student *students, int *count, int id) {
    int idx = findStudentById(students, *count, id);
    if (idx == -1) return -1;
    for (int j = idx; j < *count - 1; j++) students[j] = students[j+1];
    (*count)--; return 0;
}

void sortByGpaDesc(struct Student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i+1; j < count; j++) if (students[j].gpa > students[maxIdx].gpa) maxIdx = j;
        if (maxIdx != i) {
            struct Student tmp = students[i]; students[i] = students[maxIdx]; students[maxIdx] = tmp;
        }
    }
}

double averageGPA(const struct Student *students, int count) {
    if (count <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; i++) sum += students[i].gpa;
    return sum / count;
}

void generateTestData(struct Student *students, int *count) {
    // create 10 fake students
    const char *names[10] = {"An","Bình","Chi","Dũng","Em","Hà","Hương","Khanh","Lam","Minh"};
    double gpas[10] = {7.5,8.0,9.0,6.5,8.0,8.25,8.75,9.0,7.5,8.0};
    *count = 10;
    for (int i = 0; i < 10; i++) {
        students[i].id = i+1;
        strncpy(students[i].name, names[i], sizeof(students[i].name)-1);
        students[i].name[sizeof(students[i].name)-1] = '\0';
        students[i].age = 18 + (i%6) + 1;
        students[i].gpa = gpas[i];
    }
}

int readIntWithPrompt(const char *prompt) {
    char buf[64];
    printf("%s", prompt);
    if (!fgets(buf, sizeof(buf), stdin)) return 0;
    int v; if (sscanf(buf, "%d", &v) == 1) return v; return 0;
}

void readStudentFromStdin(struct Student *s) {
    char buf[200];
    printf("Nhập (ID Name Age GPA): ");
    if (!fgets(buf, sizeof(buf), stdin)) return;
    int id, age; double gpa; char name[50];
    if (sscanf(buf, "%d %49s %d %lf", &id, name, &age, &gpa) == 4) {
        s->id = id; strncpy(s->name, name, sizeof(s->name)-1); s->name[sizeof(s->name)-1] = '\0'; s->age = age; s->gpa = gpa;
    }
}

int main() {
    struct Student students[200]; int count = 0;
    // start with test data
    generateTestData(students, &count);

    while (1) {
        printf("\n===== Student Manager =====\n\n");
        printf("1. Nhập sinh viên\n\n");
        printf("2. In danh sách\n\n");
        printf("3. Ghi file\n\n");
        printf("4. Đọc file\n\n");
        printf("5. Tìm kiếm\n\n");
        printf("6. Sắp xếp\n\n");
        printf("7. Thêm sinh viên\n\n");
        printf("8. Xóa sinh viên\n\n");
        printf("0. Thoát\n\n");
        printf("===========================\n\n");
        int choice = readIntWithPrompt("Chọn chức năng: ");

        if (choice == 0) break;
        if (choice == 1) {
            // Input multiple students from stdin (append)
            printf("Nhập số sinh viên cần thêm: ");
            int m = readIntWithPrompt("");
            for (int i = 0; i < m; i++) {
                struct Student s = {0};
                readStudentFromStdin(&s);
                if (s.id != 0) { addStudent(students, &count, 200, s); }
            }
        } else if (choice == 2) {
            printf("\nDanh sách hiện tại:\n"); printStudents(students, count);
        } else if (choice == 3) {
            char fname[256]; printf("Nhập tên file để lưu: "); if (!fgets(fname, sizeof(fname), stdin)) continue; size_t L=strlen(fname); if (L && (fname[L-1]=='\n'||fname[L-1]=='\r')) fname[L-1]='\0';
            if (saveToFile(fname, students, count) == 0) printf("Đã lưu vào %s\n", fname); else printf("Lưu thất bại\n");
        } else if (choice == 4) {
            char fname[256]; printf("Nhập tên file để đọc: "); if (!fgets(fname, sizeof(fname), stdin)) continue; size_t L=strlen(fname); if (L && (fname[L-1]=='\n'||fname[L-1]=='\r')) fname[L-1]='\0';
            int n = loadFromFile(fname, students, 200);
            if (n < 0) printf("Không thể mở file %s\n", fname); else { count = n; printf("Đã đọc %d sinh viên từ %s\n", count, fname); }
        } else if (choice == 5) {
            int id = readIntWithPrompt("Nhập ID cần tìm: ");
            int idx = findStudentById(students, count, id);
            printf("\nKết quả tìm kiếm:\n");
            if (idx >= 0) printf("ID: %d, Name: %s, Age: %d, GPA: %.1f\n", students[idx].id, students[idx].name, students[idx].age, students[idx].gpa);
            else printf("Không tìm thấy\n");
        } else if (choice == 6) {
            sortByGpaDesc(students, count); printf("Đã sắp xếp theo GPA giảm dần.\n");
        } else if (choice == 7) {
            struct Student s={0}; readStudentFromStdin(&s); if (s.id==0) { printf("Dữ liệu không hợp lệ\n"); } else { int r=addStudent(students,&count,200,s); if (r==0) printf("Đã thêm ID %d\n", s.id); else if (r==1) printf("ID trùng\n"); else printf("Danh sách đầy\n"); }
        } else if (choice == 8) {
            int id = readIntWithPrompt("Nhập ID cần xóa: ");
            if (deleteStudentById(students, &count, id) == 0) printf("Đã xóa ID %d\n", id); else printf("Không tìm thấy ID %d\n", id);
        } else {
            printf("Lựa chọn không hợp lệ\n");
        }
    }

    printf("Thoát chương trình.\n");
    return 0;
}
