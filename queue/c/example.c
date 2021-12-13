/**
 * gcc queue.c example.c -o program
 */
#include "queue.h"

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

void show_student(void *object);

int main(int argc, char *argv[])
{
        queue *student_queue = new_queue(sizeof(struct student));

        if (student_queue == NULL)
                return EXIT_FAILURE;

        enqueue(student_queue, &students[0]);
        enqueue(student_queue, &students[1]);
        enqueue(student_queue, &students[2]);

        void *result = peek(student_queue);

        if (result != NULL) {
                printf("\tfound:\n");
                show_student(result);
                printf("\n");
        }

        show_queue(student_queue, show_student, IN_ORDER);
        printf("\n");

        dequeue(student_queue);

        show_queue(student_queue, show_student, IN_ORDER);
        printf("\n");

        result = peek(student_queue);

        if (result != NULL) {
                printf("\tfound:\n");
                show_student(result);
                printf("\n");
        }

        destroy_queue(student_queue);

        return EXIT_SUCCESS;
}

void show_student(void *object)
{
        struct student *result = object;

        printf("\t%d - %s\n", result->id, result->name);
}
