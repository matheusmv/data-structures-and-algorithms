#include "array_list.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

typedef struct array_list array_list;
struct array_list {
        void   *array;
        size_t element_size;
        size_t size;
        size_t length;
};

static void
increase_array_length(array_list *arr_list)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_size = arr_list->size;

        if (arr_length < arr_size)
                arr_list->length += 1;
}

static void
decrease_array_length(array_list *arr_list)
{
        const size_t arr_length = arr_list->length;

        if (arr_length > 0)
                arr_list->length -= 1;
}

static void *
get_index(void *array, size_t size, size_t index)
{
        return (((char *) array) + index * size);
}

static int
array_has_storage_available(array_list *arr_list, size_t size)
{
        const size_t available_storage = arr_list->size - arr_list->length;

        return size <= available_storage;
}

static int
increase_array_size(array_list *arr_list)
{
        const size_t arr_size = arr_list->size;
        const size_t obj_size = arr_list->element_size;
        const size_t new_size = (arr_size * 2);

        void *new_array = realloc(arr_list->array, new_size * obj_size);
        if (new_array == NULL) {
                return -1;
        }

        *arr_list = (array_list) {
                .array = new_array,
                .element_size = arr_list->element_size,
                .size = new_size,
                .length = arr_list->length,
        };

        return 0;
}

array_list *
array_list_create(size_t arr_size, size_t element_size)
{
        array_list *arr_list = malloc(sizeof(array_list));
        if (arr_list == NULL)
                return NULL;

        void *new_array = calloc(1, (arr_size * element_size));
        if (new_array == NULL) {
                free(arr_list);
                return NULL;
        }

        *arr_list = (array_list) {
                .array = new_array,
                .element_size = element_size,
                .size = arr_size,
                .length = 0,
        };

        return arr_list;
}

size_t
array_list_size(array_list *arr_list)
{
        return arr_list->size;
}

size_t
array_list_length(array_list *arr_list)
{
        return arr_list->length;
}

void
array_list_append(array_list *arr_list, void *object)
{
        const size_t arr_length = arr_list->length;
        const size_t obj_size = arr_list->element_size;

        if (!array_has_storage_available(arr_list, obj_size)) {
                increase_array_size(arr_list);
        }

        void *end_index = get_index(arr_list->array, obj_size, arr_length);
        memmove(end_index, object, obj_size);

        increase_array_length(arr_list);
}

void
array_list_append_at(array_list *arr_list, void *object, size_t index)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = arr_list->element_size;

        if (index > arr_length) {
                fprintf(stderr, "***index [%ld] out of bounds***\n", index);
                array_list_free(&arr_list);
                exit(EXIT_FAILURE);
        }

        if (!array_has_storage_available(arr_list, obj_size)) {
                increase_array_size(arr_list);
        }

        for (size_t i = arr_end; i > index; --i) {
                void *next = get_index(arr_list->array, obj_size, (i + 1));
                void *prev = get_index(arr_list->array, obj_size, i);
                memmove(next, prev, obj_size);
        }

        void *pos = get_index(arr_list->array, obj_size, index);
        memmove(pos, object, obj_size);

        increase_array_length(arr_list);
}

int
array_list_remove(array_list *arr_list, void *buffer)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = arr_list->element_size;

        if (arr_length > 0) {
                void *obj = get_index(arr_list->array, obj_size, arr_end);

                if (buffer != NULL)
                        memmove(buffer, obj, obj_size);

                memset(obj, 0, obj_size);
                decrease_array_length(arr_list);

                return 0;
        }

        return -1;
}

int
array_list_find_at(array_list *arr_list, size_t index, void *buffer)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = arr_list->element_size;

        if (index > arr_end) {
                fprintf(stderr, "***index [%ld] out of bounds***\n", index);
                array_list_free(&arr_list);
                exit(EXIT_FAILURE);
        }

        if (arr_length > 0) {
                void *obj = get_index(arr_list->array, obj_size, index);

                if (buffer != NULL)
                        memmove(buffer, obj, obj_size);

                return 0;
        }

        return -1;
}

int
array_list_remove_at(array_list *arr_list, size_t index, void *buffer)
{
        const size_t arr_length = arr_list->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = arr_list->element_size;

        if (index > arr_end) {
                fprintf(stderr, "***index [%ld] out of bounds***\n", index);
                array_list_free(&arr_list);
                exit(EXIT_FAILURE);
        }

        if (arr_length > 0) {
                if (index == arr_end)
                        return array_list_remove(arr_list, buffer);

                void *obj = get_index(arr_list->array, obj_size, index);

                if (buffer != NULL)
                        memmove(buffer, obj, obj_size);

                for (size_t i = index; i < arr_length; ++i) {
                        void *prev = get_index(arr_list->array, obj_size, i);
                        void *next = get_index(arr_list->array, obj_size, (i + 1));
                        memmove(prev, next, obj_size);
                }

                void *end_index = get_index(arr_list->array, obj_size, arr_end);
                memset(end_index, 0, obj_size);

                decrease_array_length(arr_list);

                return 0;
        }

        return -1;
}

void
array_list_show(array_list *arr_list, to_string_fn to_string, bool reverse)
{
        const size_t arr_length = arr_list->length;
        const size_t obj_size = arr_list->element_size;

        if (arr_length > 0) {
                size_t start = reverse ? arr_length : 0;
                size_t end = reverse ? 0 : arr_length;

                if (reverse) {
                        for (size_t i = start - 1; i > end; --i)
                                to_string(get_index(arr_list->array, obj_size, i));
                } else {
                        for (size_t i = start; i < end; ++i)
                                to_string(get_index(arr_list->array, obj_size, i));
                }
        }
}

void
array_list_free(array_list **arr_list)
{
        if (arr_list != NULL && *arr_list != NULL) {
                if ((*arr_list)->array != NULL) {
                        free((*arr_list)->array);
                        (*arr_list)->array = NULL;
                }

                (*arr_list)->element_size = 0;
                (*arr_list)->length = 0;
                (*arr_list)->size = 0;

                free(*arr_list);
                *arr_list = NULL;
        }
}
