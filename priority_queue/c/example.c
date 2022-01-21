#include <stdio.h>
#include <stdlib.h>

#include "priority_queue.h"

#define ARR_LEN(ARR) (sizeof (ARR) / sizeof (ARR)[0])

struct student {
        int id;
        char *name;
        float n1, n2, n3;
};

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2F, .n2 = 8.0F, .n3 = 7.2F},
        {.id = 2, .name = "student 2", .n1 = 6.2F, .n2 = 4.0F, .n3 = 6.2F},
        {.id = 3, .name = "student 3", .n1 = 9.2F, .n2 = 10.0F, .n3 = 8.2F},
        {.id = 4, .name = "student 4", .n1 = 2.2F, .n2 = 6.0F, .n3 = 7.9F},
        {.id = 5, .name = "student 5", .n1 = 8.2F, .n2 = 7.9F, .n3 = 7.7F},
};

void show_student(void *obj);
int by_lowest_grade(void *a, void *b);

int main(int argc, char *argv[])
{
        priority_queue *pq_students = priority_queue_create(5, sizeof(struct student), by_lowest_grade);

        if (pq_students == NULL)
                return EXIT_FAILURE;

        for (int i = 0; i < ARR_LEN(students); i++)
                priority_queue_enqueue(pq_students, &students[i]);

        struct student result;
        for (int i = 0; i < ARR_LEN(students); i++) {
                if (priority_queue_dequeue(pq_students, &result) == 0)
                        show_student(&result);
        }

        priority_queue_free(pq_students);

        return EXIT_SUCCESS;
}

static float
grade_average(float n1, float n2, float n3)
{
        return (n1 + n2 + n3) / 3;
}

void
show_student(void *obj)
{
        struct student *student = obj;

        float gav = grade_average(student->n1, student->n2, student->n3);

        printf("\t%d - \t%s - \t%.2f\n", student->id, student->name, gav);
}

int
by_lowest_grade(void *a, void *b)
{
        struct student *studentA = a;
        struct student *studentB = b;

        float gavA = grade_average(studentA->n1, studentA->n2, studentA->n3);
        float gavB = grade_average(studentB->n1, studentB->n2, studentB->n3);

        return gavA < gavB ? -1 : 1;
}
