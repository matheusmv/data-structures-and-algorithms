#include "array_list.h"

static void increase_array_length(struct array_list *arr_list)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_size = arr_list->size;

        if (arr_length < arr_size)
                arr_list->length += 1;
}

static void decrease_array_length(struct array_list *arr_list)
{
        const size_t arr_length = arr_list->length;

        if (arr_length > 0)
                arr_list->length -= 1;
}

static void increase_array_size(struct array_list *arr_list)
{
        const size_t obj_size = sizeof(struct object);
        const size_t arr_length = arr_list->length;
        const size_t arr_size = arr_list->size;
        const size_t SCALING_FACTOR = 2;

        const size_t new_size = obj_size * arr_size * SCALING_FACTOR;

        arr_list->array = realloc(arr_list->array, new_size);

        if (arr_list->array == NULL) {
                fprintf(stderr, "realloc() failed. (%s)\n", GETSTDERROR());
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        for (int i = arr_length; i < arr_size; i++)
                memset(&arr_list->array[i], 0, obj_size);

        arr_list->size *= SCALING_FACTOR;
}

struct array_list new_array_list(size_t arr_size)
{
        const size_t obj_size = sizeof(struct object);

        struct object *new_array = malloc(arr_size * obj_size);

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
        const size_t arr_length = arr_list->length;
        const size_t arr_size = arr_list->size - 1;
        const size_t obj_size = sizeof(struct object);

        if (arr_length == arr_size)
                increase_array_size(arr_list);

        memmove(&arr_list->array[arr_length], &object, obj_size);
        increase_array_length(arr_list);
}

void remove_obj(struct array_list *arr_list)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = sizeof(struct object);

        if (arr_length > 0) {
                memset(&arr_list->array[arr_end], 0, obj_size);
                decrease_array_length(arr_list);
        }
}

void add_obj_at(struct array_list *arr_list, struct object object, int index)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t arr_size = arr_list->size - 1;
        const size_t obj_size = sizeof(struct object);

        if (index > arr_length || index < 0) {
                fprintf(stderr, "***index [%d] out of bounds***\n", index);
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        if (arr_length == arr_size)
                increase_array_size(arr_list);

        for (int i = arr_end; i >= index; i--)
                arr_list->array[i + 1] = arr_list->array[i];

        memmove(&arr_list->array[index], &object, obj_size);

        increase_array_length(arr_list);
}

struct object get_obj_at(struct array_list *arr_list, int index)
{
        const size_t arr_end = arr_list->length - 1;

        if (index > arr_end || index < 0) {
                fprintf(stderr, "***index [%d] out of bounds***\n", index);
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        return arr_list->array[index];
}

void remove_obj_at(struct array_list *arr_list, int index)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = sizeof(struct object);

        if (index > arr_end || index < 0) {
                fprintf(stderr, "***index [%d] out of bounds***\n", index);
                destroy_array_list(arr_list);
                exit(EXIT_FAILURE);
        }

        if (arr_length > 0) {
                if (index == arr_end) {
                        memset(&arr_list->array[arr_end], 0, obj_size);
                        decrease_array_length(arr_list);
                        return;
                }

                for (int i = index; i < arr_length; i++)
                        arr_list->array[i] = arr_list->array[i + 1];

                memset(&arr_list->array[arr_end], 0, obj_size);
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
