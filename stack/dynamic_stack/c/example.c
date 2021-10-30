/**
 * gcc data_types.c stack.c example.c -o program
 */
#include "stack.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

void show_students(struct object);

int main(int argc, char *argv[])
{
        stack *student_stack = new_stack(STUDENT_TYPE);

        if (student_stack == NULL)
                return EXIT_FAILURE;

        push(student_stack, (struct object) { ._student = students[0] });
        push(student_stack, (struct object) { ._student = students[1] });
        push(student_stack, (struct object) { ._student = students[2] });

        struct student *result = peek(student_stack);

        if (result != NULL)
                printf("%d - %s\n", result->id, result->name);

        show_stack(student_stack, show_students, IN_ORDER);

        pop(student_stack);

        show_stack(student_stack, show_students, IN_ORDER);

        result = peek(student_stack);

        if (result != NULL)
                printf("%d - %s\n", result->id, result->name);

        destroy_stack(student_stack);

        return EXIT_SUCCESS;
}

void show_students(struct object obj)
{
        struct student result = obj._student;

        printf("\t%d - %s\n", result.id, result.name);
}
