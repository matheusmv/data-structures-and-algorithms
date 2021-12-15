#include "priority_queue.h"

typedef struct __priority_queue {
        void *array;
        size_t esize;
        size_t size;
        size_t length;
        compare_obj_fn comparator;
} priority_queue;

static void increase_array_length(priority_queue *queue)
{
        const size_t arr_length = queue->length;
        const size_t arr_size = queue->size;

        if (arr_length < arr_size)
                queue->length += 1;
}

static void decrease_array_length(priority_queue *queue)
{
        const size_t arr_length = queue->length;

        if (arr_length > 0)
                queue->length -= 1;
}

static void *get_index(void *array, size_t size, int index)
{
        return (void *) (((char *) array) + index * size);
}

static void increase_array_size(priority_queue *queue)
{
        const size_t SCALING_FACTOR = 2;
        const size_t obj_size = queue->esize;
        const size_t arr_length = queue->length;
        const size_t arr_size = queue->size;
        const size_t new_arr_size = arr_size * SCALING_FACTOR;

        const size_t new_size = obj_size * new_arr_size;

        queue->array = realloc(queue->array, new_size);

        if (queue->array == NULL) {
                fprintf(stderr, "realloc() failed. (%s)\n", GETSTDERROR());
                destroy_priority_queue(queue);
                exit(EXIT_FAILURE);
        }

        for (int i = arr_length; i < new_arr_size; i++) {
                void *index = get_index(queue->array, obj_size, i);
                memset(index, 0, obj_size);
        }

        queue->size = new_arr_size;
}

priority_queue *new_priority_queue(size_t size, size_t element_size, compare_obj_fn comparator)
{
        priority_queue *queue = malloc(sizeof(priority_queue));

        if (queue == NULL)
                return NULL;

        void *new_array = malloc(size * element_size);

        if (new_array == NULL) {
                free(queue);
                return NULL;
        }

        memset(new_array, 0, sizeof(size * element_size));

        *queue = (priority_queue) {
                .array = new_array,
                .esize = element_size,
                .size = size,
                .length = 0,
                .comparator = comparator,
        };

        return queue;
}

size_t get_length(priority_queue *queue)
{
        return queue->length;
}

static void swap(void *a, void *b, size_t size)
{
        unsigned char aux, *aux_a, *aux_b;

        aux_a = a;
        aux_b = b;

        for (size_t i = 0; i != size; i++) {
                aux = aux_a[i];
                aux_a[i] = aux_b[i];
                aux_b[i] = aux;
        }
}

static void heapify(void *array, size_t size, size_t arr_size, int index, compare_obj_fn comparator)
{
        if (arr_size <= 1)
                return;

        int smaller = index;
        void *smaller_obj = get_index(array, size, smaller);

        int left_element = 2 * index + 1;
        void *left_obj = get_index(array, size, left_element);

        int rigth_element = 2 * index + 2;
        void *right_obj = get_index(array, size, rigth_element);

        if (left_element < arr_size && comparator(left_obj, smaller_obj) < 0)
                smaller = left_element;
        if (rigth_element < arr_size && comparator(right_obj, smaller_obj) < 0)
                smaller = rigth_element;
        if (smaller != index) {
                void *new_smaller = get_index(array, size, smaller);
                swap(smaller_obj, new_smaller, size);
                heapify(array, size, arr_size, smaller, comparator);
        }
}

void enqueue(priority_queue *queue, void *object)
{
        const size_t arr_length = queue->length;
        const size_t arr_end = arr_length - 1;
        const size_t arr_size = queue->size;
        const size_t obj_size = queue->esize;

        if (arr_length == arr_size)
                increase_array_size(queue);

        void *end_index = get_index(queue->array, obj_size, arr_length);
        memmove(end_index, object, obj_size);

        increase_array_length(queue);

        for (int i = arr_end / 2 - 1; i >= 0; i--)
                heapify(queue->array, obj_size, arr_end, i, queue->comparator);
}

int dequeue(priority_queue *queue, void *buffer)
{
        const size_t arr_length = queue->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = queue->esize;

        if (arr_length > 0) {
                void *start = get_index(queue->array, obj_size, 0);
                void *end = get_index(queue->array, obj_size, arr_end);

                if (buffer != NULL)
                        memmove(buffer, start, obj_size);

                swap(start, end, obj_size);

                for (int i = arr_end / 2 - 1; i >= 0; i--)
                        heapify(queue->array, obj_size, arr_end, i, queue->comparator);

                memset(end, 0, obj_size);
                decrease_array_length(queue);

                return 0;
        }

        return -1;
}

void *peek(priority_queue *queue)
{
        const size_t arr_length = queue->length;
        const size_t obj_size = queue->esize;

        if (arr_length > 0)
                return get_index(queue->array, obj_size, 0);

        return NULL;
}

void show_priority_queue(priority_queue *queue, to_string_fn to_string, bool reverse)
{
        const size_t arr_length = queue->length;
        const size_t obj_size = queue->esize;

        if (arr_length > 0) {
                int start = reverse ? arr_length : 0;
                int end = reverse ? 0 : arr_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(get_index(queue->array, obj_size, i));
                } else {
                        for (int i = start; i < end; i++)
                                to_string(get_index(queue->array, obj_size, i));
                }
        }
}

void destroy_priority_queue(priority_queue *queue)
{
        if (queue != NULL) {
                if (queue->array != NULL) {
                        free(queue->array);
                        queue->array = NULL;
                }

                queue->esize = 0;
                queue->size = 0;
                queue->length = 0;

                free(queue);
                queue = NULL;
        }
}
