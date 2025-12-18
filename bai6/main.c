#include <stdio.h>
#include <string.h>

// Student struct
struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
};

// Tính GPA trung bình của lớp. Trả về 0.0 nếu count == 0.
// Param: students - mảng sinh viên, count - số phần tử trong mảng.
// Return: average GPA as double.
double averageGPA(const struct Student *students, int count) {
    if (count <= 0) return 0.0;
    double sum = 0.0;
    for (int i = 0; i < count; i++) sum += students[i].gpa;
    return sum / count;
}

int main() {
    // Tạo 10 sinh viên giả lập để test
    struct Student students[10] = {
        {1, "An", 20, 7.5},
        {2, "Bình", 21, 8.0},
        {3, "Cường", 22, 8.5},
        {4, "Dũng", 20, 9.0},
        {5, "Em", 21, 8.0},
        {6, "Hà", 22, 8.25},
        {7, "Hương", 20, 8.75},
        {8, "Khanh", 23, 9.0},
        {9, "Lam", 21, 7.5},
        {10, "Minh", 22, 8.0}
    };

    double avg = averageGPA(students, 10);
    printf("GPA trung bình của lớp là: %.2f\n", avg);

    // Test case: danh sách rỗng
    double avg_empty = averageGPA(students, 0);
    if (avg_empty == 0.0) {
        printf("Test (empty): danh sách rỗng, không thể tính GPA trung bình (returned %.2f)\n", avg_empty);
    }

    return 0;
}
