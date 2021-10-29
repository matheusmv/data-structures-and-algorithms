/**
 * gcc data_types.c linked_list.c example.c -o program
 */
#include "linked_list.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

void show_students(struct object);
void show_students_with_grades(struct object);

int main(int argc, char *argv[])
{
        linked_list *student_list = new_linked_list(STUDENT_TYPE);

        if (student_list == NULL)
                return EXIT_FAILURE;

        insert_last(student_list, (struct object) { ._student = students[4] });
        insert_last(student_list, (struct object) { ._student = students[3] });
        insert_last(student_list, (struct object) { ._student = students[2] });

        show_list(student_list, show_students, IN_ORDER);
        show_list(student_list, show_students_with_grades, REVERSE);

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_first(student_list, (struct object) { ._student = students[i] });

        show_list(student_list, show_students, IN_ORDER);

        remove_first(student_list);
        remove_first(student_list);

        show_list(student_list, show_students, IN_ORDER);

        struct student *result = get_obj_at(student_list, 2);

        if (result != NULL)
                printf("%d - %s\n", result->id, result->name);

        insert_obj_at(student_list, (struct object) { ._student = students[4] }, 1);

        remove_obj_at(student_list, 2);

        show_list(student_list, show_students, IN_ORDER);

        remove_last(student_list);
        remove_last(student_list);

        show_list(student_list, show_students, IN_ORDER);
        show_list(student_list, show_students_with_grades, IN_ORDER);

        destroy_linked_list(student_list);

        return EXIT_SUCCESS;
}

void show_students(struct object obj)
{
        struct student result = obj._student;

        printf("\t%d - %s\n", result.id, result.name);
}

void show_students_with_grades(struct object obj)
{
        struct student result = obj._student;

        printf("\t%d - %s - %.2f - %.2f - %.2f\n",
               result.id, result.name,
               result.n1, result.n2, result.n3);
}
