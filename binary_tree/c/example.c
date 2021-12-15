/**
 * gcc binary_tree.c example.c -o program
 */
#include "binary_tree.h"

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

int compare_by_id(void *a, void *b);
void show_students(void *);

int main(int argc, char *argv[])
{
        binary_tree *student_tree = new_binary_tree(sizeof(struct student));

        if (student_tree == NULL)
                return EXIT_FAILURE;

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_obj(student_tree, &students[i], compare_by_id);

        printf("Pre Order:\n");
        show_binary_tree(student_tree, PRE_ORDER, show_students);

        printf("In Order:\n");
        show_binary_tree(student_tree, IN_ORDER, show_students);

        printf("Post Order:\n");
        show_binary_tree(student_tree, POST_ORDER, show_students);

        void *result;
        result = search_obj(student_tree, &students[0], compare_by_id);
        if (result != NULL) {
                printf("*** \tfound: ");
                show_students(result);
        }

        struct student sresult;
        if (find_and_remove_obj(student_tree, &students[0], compare_by_id, &sresult) == 0) {
                printf("*** \tremoved: ");
                show_students(&sresult);
        }

        if (remove_obj(student_tree, &sresult) == 0) {
                printf("*** \tremoved: ");
                show_students(&sresult);
        }

        if (remove_obj(student_tree, &sresult) == 0) {
                printf("*** \tremoved: ");
                show_students(&sresult);
        }

        result = search_obj(student_tree, &students[0], compare_by_id);
        if (result != NULL) {
                printf("*** \tfound: ");
                show_students(result);
        }

        printf("Pre Order:\n");
        show_binary_tree(student_tree, PRE_ORDER, show_students);

        printf("In Order:\n");
        show_binary_tree(student_tree, IN_ORDER, show_students);

        printf("Post Order:\n");
        show_binary_tree(student_tree, POST_ORDER, show_students);

        destroy_binary_tree(student_tree);

        return EXIT_SUCCESS;
}

static float grade_average(float n1, float n2, float n3)
{
        return (n1 + n2 + n3) / 3.0F;
}

int compare_by_id(void *a, void *b)
{
        struct student *studentA = a;
        struct student *studentB = b;

        return studentA->id - studentB->id;
}

void show_students(void *obj)
{
        struct student *student = obj;

        float gav = grade_average(student->n1, student->n2, student->n3);

        printf("\t%d - %s - %.2f\n", student->id, student->name, gav);
}
