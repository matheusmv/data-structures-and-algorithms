/**
 * gcc data_types.c linked_list.c example.c -o program
 */
#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

void show_students(struct object);
int in_order(object a, object b);
int reverse(object a, object b);

int main(int argc, char *argv[])
{
        linked_list *student_list = new_linked_list(STUDENT_TYPE);

        if (student_list == NULL)
                return EXIT_FAILURE;

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_first(student_list, (struct object) { ._student = students[i] });

        printf("unsorted list\n");
        show_list(student_list, show_students, IN_ORDER);

        m_sort_list(student_list, in_order);

        printf("sorted list - in_order\n");
        show_list(student_list, show_students, IN_ORDER);

        m_sort_list(student_list, reverse);

        printf("sorted list - reverse\n");
        show_list(student_list, show_students, IN_ORDER);

        destroy_linked_list(student_list);

        return EXIT_SUCCESS;
}

static float grade_average(float n1, float n2, float n3)
{
        return (n1 + n2 + n3) / 3.0F;
}

void show_students(struct object obj)
{
        struct student result = obj._student;

        float gav = grade_average(result.n1, result.n2, result.n3);

        printf("\t%d - %s - %.2f\n", result.id, result.name, gav);
}

int in_order(object a, object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        float gavA = grade_average(studentA.n1, studentA.n2, studentA.n3);
        float gavB = grade_average(studentB.n1, studentB.n2, studentB.n3);

        return gavA - gavB;
}

int reverse(object a, object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        float gavA = grade_average(studentA.n1, studentA.n2, studentA.n3);
        float gavB = grade_average(studentB.n1, studentB.n2, studentB.n3);

        return gavB - gavA;
}
