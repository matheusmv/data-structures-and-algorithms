/**
 * gcc data_types.c priority_queue.c example.c -o program
 */
#include "priority_queue.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2F, .n2 = 8.0F, .n3 = 7.2F},
        {.id = 2, .name = "student 2", .n1 = 6.2F, .n2 = 4.0F, .n3 = 6.2F},
        {.id = 3, .name = "student 3", .n1 = 9.2F, .n2 = 10.0F, .n3 = 8.2F},
        {.id = 4, .name = "student 4", .n1 = 2.2F, .n2 = 6.0F, .n3 = 7.9F},
        {.id = 5, .name = "student 5", .n1 = 8.2F, .n2 = 7.9F, .n3 = 7.7F},
};

void show_student(object obj);
int by_lowest_grade(object a, object b);

int main(int argc, char *argv[])
{
        priority_queue *pq_students = new_priority_queue(5, STUDENT_TYPE, by_lowest_grade);

        if (pq_students == NULL)
                return EXIT_FAILURE;

        const size_t arr_len = sizeof(students) / sizeof(students[0]);

        for (int i = 0; i < arr_len; i++)
                enqueue(pq_students, (object) { ._student = students[i] });

        for (int i = 0; i < arr_len; i++) {
                result result = dequeue(pq_students);
                if (result.is_present)
                        show_student(result.object);
        }

        destroy_priority_queue(pq_students);

        return EXIT_SUCCESS;
}

static float grade_average(float n1, float n2, float n3)
{
        return (n1 + n2 + n3) / 3.0F;
}

void show_student(object obj)
{
        struct student student = obj._student;

        float gav = grade_average(student.n1, student.n2, student.n3);

        printf("\t%d - \t%s - \t%.2f\n", student.id, student.name, gav);
}

int by_lowest_grade(object a, object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        float gavA = grade_average(studentA.n1, studentA.n2, studentA.n3);
        float gavB = grade_average(studentB.n1, studentB.n2, studentB.n3);

        return gavA - gavB;
}
