#include "array_list.h"

static void increase_array_length(struct array_list *arr_list)
{
        if (arr_list->length < arr_list->size) {
                arr_list->length += 1;
        }
}

static void decrease_array_length(struct array_list *arr_list)
{
        if (arr_list->length > 0) {
                arr_list->length -= 1;
        }
}

void increase_array_size(struct array_list *arr_list)
{
        size_t new_size = (sizeof(arr_list->array[0]) * arr_list->size) * 2;

        arr_list->array = realloc(arr_list->array, new_size);

        if (arr_list->array == NULL) {
                fprintf(stderr, "realloc() failed. (%s)\n", GETSTDERROR());
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        arr_list->size *= 2;
}

struct array_list new_array_list(size_t arr_size)
{
        struct object *new_array = malloc(arr_size * sizeof(struct object));

        if (new_array == NULL) {
                fprintf(stderr, "malloc() failed. (%s)\n", GETSTDERROR());
                exit(EXIT_FAILURE);
        }

        memset(new_array, 0, sizeof(*new_array));

        struct array_list arr_list = {
                .array = new_array,
                .size = arr_size,
                .length = 0,
        };

        return arr_list;
}

size_t get_size(struct array_list *arr_list)
{
        return arr_list->size;
}

size_t get_length(struct array_list *arr_list)
{
        return arr_list->length;
}

void append_obj(struct array_list *arr_list, struct object object)
{
        if (arr_list->length == arr_list->size - 1)
                increase_array_size(arr_list);

        memcpy(&arr_list->array[arr_list->length], &object,
               sizeof(struct object));

        increase_array_length(arr_list);
}

void remove_obj(struct array_list *arr_list)
{
        if (arr_list->length > 0) {
                memset(&arr_list->array[arr_list->length - 1], 0,
                       sizeof(struct object));
                decrease_array_length(arr_list);
        }
}

void add_obj_at(struct array_list *arr_list, struct object object, int index)
{
        if (index > arr_list->length || index < 0) {
                fprintf(stderr, "***index [%d] out of bounds***\n", index);
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        if (arr_list->length == arr_list->size - 1)
                increase_array_size(arr_list);

        for (int i = arr_list->length - 1; i >= index; i--)
                arr_list->array[i + 1] = arr_list->array[i];

        memcpy(&arr_list->array[index], &object, sizeof(struct object));

        increase_array_length(arr_list);
}

struct object get_obj_at(struct array_list *arr_list, int index)
{
        if (index > arr_list->length - 1 || index < 0) {
                fprintf(stderr, "***index [%d] out of bounds***\n", index);
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        return arr_list->array[index];
}

void remove_obj_at(struct array_list *arr_list, int index)
{
        if (arr_list->length > 0) {
                if (index > arr_list->length - 1 || index < 0) {
                        fprintf(stderr, "***index [%d] out of bounds***\n", index);
                        destroy_array_list(arr_list);
                        exit(EXIT_FAILURE);
                }

                const int start = 0;
                const int end = arr_list->length - 1;

                if (index == start) {
                        for (int index = start; index < arr_list->length; index++) {
                                arr_list->array[index] = arr_list->array[index + 1];
                        }
                        memset(&arr_list->array[end], 0, sizeof(struct object));
                        decrease_array_length(arr_list);
                        return;
                }

                if (index == end) {
                        memset(&arr_list->array[end], 0, sizeof(struct object));
                        decrease_array_length(arr_list);
                        return;
                }

                const int middle = index;

                for (int index = middle; index < arr_list->length; index++) {
                        arr_list->array[index] = arr_list->array[index + 1];
                }
                memset(&arr_list->array[end], 0, sizeof(struct object));
                decrease_array_length(arr_list);
        }
}

void destroy_array_list(struct array_list *arr_list)
{
        if (arr_list->array != NULL) {
                free(arr_list->array);
                arr_list->array = NULL;
                arr_list->size = 0;
                arr_list->length = 0;
        }
}
