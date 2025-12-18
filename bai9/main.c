#include <stdio.h>
#include <string.h>

// Student struct
struct Student {
    int id;
    char name[50];
    int age;
    float gpa;
};

/*
 * addStudent
 * Add a new student to the array if there's space and the ID is not duplicate.
 * Parameters:
 *   students - array of Student with capacity 'max'
 *   count    - pointer to current number of students (will be incremented on success)
 *   max      - capacity of the students array
 *   s        - Student to add
 * Returns: 0 on success, 1 if duplicate ID, 2 if array full
 */
int addStudent(struct Student *students, int *count, int max, struct Student s) {
    if (*count >= max) return 2; // full
    for (int i = 0; i < *count; i++) {
        if (students[i].id == s.id) return 1; // duplicate
    }
    students[*count] = s;
    (*count)++;
    return 0;
}

/*
 * deleteStudentById
 * Remove the student with the given ID from the array (in-place).
 * Parameters:
 *   students - array of Student
 *   count    - pointer to current number of students (will be decremented on success)
 *   id       - ID to remove
 * Returns: 0 on success (found and removed), -1 if not found
 */
int deleteStudentById(struct Student *students, int *count, int id) {
    for (int i = 0; i < *count; i++) {
        if (students[i].id == id) {
            // shift left
            for (int j = i; j < *count - 1; j++) students[j] = students[j+1];
            (*count)--;
            return 0;
        }
    }
    return -1; // not found
}

void printStudents(const struct Student *students, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d %s %d %.1f\n", students[i].id, students[i].name, students[i].age, students[i].gpa);
    }
}

int main() {
    // initial sample data (matches previous examples)
    struct Student students[100];
    int count = 0;
    students[count++] = (struct Student){1, "An", 20, 8.0f};
    students[count++] = (struct Student){2, "Bình", 21, 7.5f};
    students[count++] = (struct Student){3, "Chi", 19, 9.0f};

    printf("Ban dau:\n");
    printStudents(students, count);
    printf("\n");

    // Test: add new student (4 Dũng 22 6.5)
    struct Student newS = {4, "Dũng", 22, 6.5f};
    int r = addStudent(students, &count, 100, newS);
    if (r == 0) printf("Added student ID %d\n", newS.id);
    else if (r == 1) printf("Cannot add: duplicate ID %d\n", newS.id);
    else printf("Cannot add: array full\n");

    // Test: attempt to add duplicate ID
    struct Student dup = {4, "Dupe", 23, 7.0f};
    r = addStudent(students, &count, 100, dup);
    if (r == 1) printf("Test case - add duplicate ID: correctly rejected\n");

    // Test: delete ID 2
    int dres = deleteStudentById(students, &count, 2);
    if (dres == 0) printf("Deleted ID 2\n");
    else printf("Delete failed: ID 2 not found\n");

    // Test: delete non-existent ID
    dres = deleteStudentById(students, &count, 999);
    if (dres == -1) printf("Test case - delete non-existent ID: correctly reported not found\n");

    printf("\nDanh sách sau khi chỉnh sửa:\n");
    printStudents(students, count);

    return 0;
}
