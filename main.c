#include <stdio.h>

// Định nghĩa struct Student
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

int main() {
    // Khởi tạo mảng sinh viên
    struct Student students[3] = {
                {1, "Nguyen Anh Tu", 20, 3.5},
                {2, "Tran Mai Lan", 21, 3.8},
                {3, "Le Minh Tuan", 22, 3.2}
    };

    // In danh sách sinh viên ra màn hình dưới dạng bảng
    printf("| %-5s | %-20s | %-5s | %-5s |\n", "ID", "Name", "Age", "GPA");
    printf("|-------|----------------------|-------|-------|\n");
    
    for (int i = 0; i < 3; i++) {
        printf("| %-5d | %-20s | %-5d | %-5.2f |\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
    
    return 0;
}
