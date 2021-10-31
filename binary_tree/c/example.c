/**
 * gcc data_types.c binary_tree.c example.c -o program
 */
#include "binary_tree.h"

struct student students[] = {
        {.id = 1, .name = "student 1", .n1 = 5.2f, .n2 = 8.0f, .n3 = 7.2f},
        {.id = 2, .name = "student 2", .n1 = 6.2f, .n2 = 4.0f, .n3 = 6.2f},
        {.id = 3, .name = "student 3", .n1 = 9.2f, .n2 = 10.0f, .n3 = 8.2f},
        {.id = 4, .name = "student 4", .n1 = 2.2f, .n2 = 6.0f, .n3 = 7.9f},
        {.id = 5, .name = "student 5", .n1 = 8.2f, .n2 = 7.9f, .n3 = 7.7f},
};

bool is_bigger_than(struct object, struct object);
bool equals(struct object, struct object);
void show_students(struct object);

int main(int argc, char *argv[])
{
        binary_tree *student_tree = new_binary_tree(STUDENT_TYPE);

        if (student_tree == NULL)
                return EXIT_FAILURE;

        const int student_arr_len = sizeof(students) / sizeof(struct student);

        for (int i = 0; i < student_arr_len; i++)
                insert_obj(student_tree, (struct object) { ._student = students[i] }, is_bigger_than);

        printf("Pre Order:\n");
        show_binary_tree(student_tree, show_students, PRE_ORDER);

        printf("In Order:\n");
        show_binary_tree(student_tree, show_students, IN_ORDER);

        printf("Post Order:\n");
        show_binary_tree(student_tree, show_students, POST_ORDER);

        struct object to_find = (struct object) {
                ._student = students[0],
        };

        struct result result = search_obj(student_tree, to_find, equals, is_bigger_than);

        if (result.is_present) {
                printf("*** \tfound: ");
                show_students(result.object);
        }

        result = find_and_remove_obj(student_tree, to_find, equals, is_bigger_than);

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

        result = search_obj(student_tree, to_find, equals, is_bigger_than);

        if (result.is_present) {
                printf("*** \tfound: ");
                show_students(result.object);
        }

        printf("Pre Order:\n");
        show_binary_tree(student_tree, show_students, PRE_ORDER);

        printf("In Order:\n");
        show_binary_tree(student_tree, show_students, IN_ORDER);

        printf("Post Order:\n");
        show_binary_tree(student_tree, show_students, POST_ORDER);

        destroy_binary_tree(student_tree);

        return EXIT_SUCCESS;
}

static float grade_average(float n1, float n2, float n3)
{
        return (n1 + n2 + n3) / 3.0f;
}

bool is_bigger_than(struct object a, struct object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        float gA = grade_average(studentA.n1, studentA.n2, studentA.n3);
        float gB = grade_average(studentB.n1, studentB.n2, studentB.n3);

        return gA > gB;
}

bool equals(struct object a, struct object b)
{
        struct student studentA = a._student;
        struct student studentB = b._student;

        return studentA.id == studentB.id;
}

void show_students(struct object obj)
{
        struct student result = obj._student;

        printf("\t%d - %s\n", result.id, result.name);
}
