#include <stdio.h>
#include <string.h>

// Student struct
struct Student {
    int id;
    char name[50];
    int age;
    double gpa;
};

// Swap two students
void swapStudent(struct Student *a, struct Student *b) {
    struct Student tmp = *a;
    *a = *b;
    *b = tmp;
}

// Selection sort: sort by GPA descending
void sortByGpaDesc(struct Student *students, int count) {
    for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].gpa > students[maxIdx].gpa) maxIdx = j;
        }
        if (maxIdx != i) swapStudent(&students[i], &students[maxIdx]);
    }
}

void printStudents(const struct Student *students, int count) {
    for (int i = 0; i < count; i++) {
        // print in compact format: ID Name Age GPA
        printf("%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

int main() {
    // Test case 1: GPA bằng nhau
    struct Student sameGpa[] = {
        {1, "A", 20, 8.0},
        {2, "B", 21, 8.0},
        {3, "C", 22, 8.0}
    };
    int n1 = sizeof(sameGpa)/sizeof(sameGpa[0]);
    sortByGpaDesc(sameGpa, n1);
    printf("Test 1 - GPA bằng nhau:\n");
    printStudents(sameGpa, n1);
    printf("\n");

    // Test case 2: GPA tăng dần (already ascending)
    struct Student ascGpa[] = {
        {1, "An", 20, 7.5},
        {2, "Bình", 21, 8.0},
        {3, "Chi", 19, 9.0}
    };
    int n2 = sizeof(ascGpa)/sizeof(ascGpa[0]);
    sortByGpaDesc(ascGpa, n2);
    printf("Test 2 - GPA tăng dần ban đầu, sau khi sắp xếp:\n");
    printStudents(ascGpa, n2);
    printf("\n");

    // Test case 3: GPA ngẫu nhiên
    struct Student randGpa[] = {
        {1, "X", 20, 8.0},
        {2, "Y", 21, 7.5},
        {3, "Z", 19, 9.0}
    };
    int n3 = sizeof(randGpa)/sizeof(randGpa[0]);
    sortByGpaDesc(randGpa, n3);
    printf("Test 3 - GPA ngẫu nhiên, sau khi sắp xếp:\n");
    printStudents(randGpa, n3);
    printf("\n");

    // Output matching user's sample (explicit demonstration)
    struct Student sample[] = {
        {1, "An", 20, 8.0},
        {2, "Bình", 21, 7.5},
        {3, "Chi", 19, 9.0}
    };
    int ns = sizeof(sample)/sizeof(sample[0]);
    sortByGpaDesc(sample, ns);
    printf("Danh sách sau khi sắp xếp:\n");
    printStudents(sample, ns);

    return 0;
}
