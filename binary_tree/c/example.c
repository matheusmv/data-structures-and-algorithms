/**
 * gcc data_types.c binary_tree.c example.c -o program
 */
#include "binary_tree.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2F, .n2 = 8.0F, .n3 = 7.2F},
        {.id = 2, .name = "student 2", .n1 = 6.2F, .n2 = 4.0F, .n3 = 6.2F},
        {.id = 3, .name = "student 3", .n1 = 9.2F, .n2 = 10.0F, .n3 = 8.2F},
        {.id = 4, .name = "student 4", .n1 = 2.2F, .n2 = 6.0F, .n3 = 7.9F},
        {.id = 5, .name = "student 5", .n1 = 8.2F, .n2 = 7.9F, .n3 = 7.7F},
};

bool greater_than(object, object);
bool equals(object, object);
void show_students(object);

int main(int argc, char *argv[])
{
        binary_tree *student_tree = new_binary_tree(STUDENT_TYPE);

        if (student_tree == NULL)
                return EXIT_FAILURE;

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_obj(student_tree, (object) { ._student = students[i] }, equals, greater_than);

        printf("Pre Order:\n");
        show_binary_tree(student_tree, PRE_ORDER, show_students);

        printf("In Order:\n");
        show_binary_tree(student_tree, IN_ORDER, show_students);

        printf("Post Order:\n");
        show_binary_tree(student_tree, POST_ORDER, show_students);

        object to_find = (struct object) {
                ._student = students[0],
        };

        result result = search_obj(student_tree, to_find, equals, greater_than);

        if (result.is_present) {
                printf("*** \tfound: ");
                show_students(result.object);
        }

        result = find_and_remove_obj(student_tree, to_find, equals, greater_than);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = remove_obj(student_tree);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = remove_obj(student_tree);

        if (result.is_present) {
                printf("*** \tremoved: ");
                show_students(result.object);
        }

        result = search_obj(student_tree, to_find, equals, greater_than);

        if (result.is_present) {
                printf("*** \tfound: ");
                show_students(result.object);
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

bool greater_than(object a, object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        float gavA = grade_average(studentA.n1, studentA.n2, studentA.n3);
        float gavB = grade_average(studentB.n1, studentB.n2, studentB.n3);

        return gavA > gavB;
}

bool equals(object a, object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        return studentA.id == studentB.id;
}

void show_students(object obj)
{
        struct student result = obj._student;

        float gav = grade_average(result.n1, result.n2, result.n3);

        printf("\t%d - %s - %.2f\n", result.id, result.name, gav);
}
