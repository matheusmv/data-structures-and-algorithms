#include "deque.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

void show_students(struct object);
bool is_palindrome(char *);

int main(int argc, char *argv[])
{
        deque *student_deque = new_deque(STUDENT_TYPE);

        if (student_deque == NULL)
                return EXIT_FAILURE;

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_first(student_deque, (struct object) { ._student = students[i] });

        show_deque(student_deque, show_students, IN_ORDER);
        show_deque(student_deque, show_students, REVERSE);

        struct result result = remove_first(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = remove_first(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        show_deque(student_deque, show_students, IN_ORDER);

        result = peek_first(student_deque);

        if (result.is_present) {
                printf("*** \tfound: ");
                show_students(result.object);
        }

        insert_last(student_deque, (struct object) { ._student = students[4] });
        insert_last(student_deque, (struct object) { ._student = students[4] });

        show_deque(student_deque, show_students, IN_ORDER);

        result = remove_last(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = remove_last(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        show_deque(student_deque, show_students, IN_ORDER);

        result = remove_last(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = remove_last(student_deque);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        show_deque(student_deque, show_students, IN_ORDER);

        insert_first(student_deque, (struct object) { ._student = students[0] });
        insert_last(student_deque, (struct object) { ._student = students[0] });

        show_deque(student_deque, show_students, IN_ORDER);

        destroy_deque(student_deque);

        return EXIT_SUCCESS;
}

void show_students(struct object obj)
{
        struct student result = obj._student;

        printf("\t%d - %s\n", result.id, result.name);
}
