#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

#define ARR_LEN(ARR) (sizeof (ARR) / sizeof (ARR)[0])

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

void show_students(void *object);
void show_students_with_grades(void *object);

int main(int argc, char *argv[])
{
        linked_list *student_list = linked_list_create(sizeof(struct student));

        if (student_list == NULL)
                return EXIT_FAILURE;

        linked_list_insert_last(student_list, &students[4]);
        linked_list_insert_last(student_list, &students[3]);
        linked_list_insert_last(student_list, &students[2]);

        linked_list_show(student_list, show_students, IN_ORDER);
        linked_list_show(student_list, show_students_with_grades, REVERSE);

        for (int i = 0; i < ARR_LEN(students); i++)
                linked_list_insert_first(student_list, &students[i]);

        linked_list_show(student_list, show_students, IN_ORDER);

        linked_list_remove_first(student_list, NULL);
        linked_list_remove_first(student_list, NULL);

        linked_list_show(student_list, show_students, IN_ORDER);

        void *result = linked_list_get_obj_at(student_list, 2);
        if (result != NULL) {
                printf("\tfound:\n");
                show_students(result);
                printf("\n");
        }

        linked_list_insert_obj_at(student_list, &students[4], 1);

        linked_list_remove_obj_at(student_list, 2, NULL);

        linked_list_show(student_list, show_students, IN_ORDER);

        linked_list_remove_last(student_list, NULL);
        linked_list_remove_last(student_list, NULL);

        linked_list_show(student_list, show_students, IN_ORDER);
        linked_list_show(student_list, show_students_with_grades, IN_ORDER);

        linked_list_free(student_list);

        return EXIT_SUCCESS;
}

void show_students(void *obj)
{
        struct student *result = obj;

        printf("\t%d - %s\n", result->id, result->name);
}

void show_students_with_grades(void *obj)
{
        struct student *result = obj;

        printf("\t%d - %s - %.2f - %.2f - %.2f\n",
               result->id, result->name,
               result->n1, result->n2, result->n3);
}
