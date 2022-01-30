#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

struct student {
        int id;
        char *name;
        float n1, n2, n3;
};

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

void show_student(void *obj);

int main(void)
{
        stack *student_stack = stack_new(sizeof(struct student));
        if (student_stack == NULL) {
                return EXIT_FAILURE;
        }

        stack_push(student_stack, &students[0]);
        stack_push(student_stack, &students[1]);
        stack_push(student_stack, &students[2]);

        void *result = stack_peek(student_stack);

        if (result != NULL) {
                printf("\tfound:\n");
                show_student(result);
                printf("\n");
        }

        printf("in order\n");
        stack_show(student_stack, show_student, IN_ORDER);
        printf("\n");

        stack_pop(student_stack);

        printf("reverse\n");
        stack_show(student_stack, show_student, REVERSE);
        printf("\n");

        result = stack_peek(student_stack);

        if (result != NULL) {
                printf("\tfound:\n");
                show_student(result);
                printf("\n");
        }

        stack_free(&student_stack);

        return EXIT_SUCCESS;
}

void
show_student(void *obj)
{
        struct student *result = obj;

        printf("\t%d - %s\n", result->id, result->name);
}
