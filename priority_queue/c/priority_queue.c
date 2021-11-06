#include "priority_queue.h"

typedef struct __priority_queue {
        struct object *array;
        compare_obj_fn comparator;
        obj_type type;
        size_t size;
        size_t length;
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

static void increase_array_size(priority_queue *queue)
{
        const size_t SCALING_FACTOR = 2;
        const size_t obj_size = sizeof(struct object);
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

        for (int i = arr_length; i < new_arr_size; i++)
                memset(&queue->array[i], 0, obj_size);

        queue->size = new_arr_size;
}

priority_queue *new_priority_queue(size_t size, obj_type type, compare_obj_fn comparator)
{
        priority_queue *queue = malloc(sizeof(priority_queue));

        if (queue == NULL)
                return NULL;

        const size_t obj_size = sizeof(struct object);

        object *new_array = malloc(size * obj_size);

        if (new_array == NULL) {
                free(queue);
                return NULL;
        }

        memset(new_array, 0, sizeof(*new_array));

        const obj_type queue_type = get_object_type(type);

        *queue = (priority_queue) {
                .array = new_array,
                .comparator = comparator,
                .type = queue_type,
                .size = size,
                .length = 0,
        };

        return queue;
}

size_t get_length(priority_queue *queue)
{
        return queue->length;
}

static void swap(object *a, object *b)
{
        object aux = *a;
        *a = *b;
        *b = aux;
}

static void heapify(object *array, size_t arr_size, int64_t index, compare_obj_fn comparator)
{
        if (arr_size <= 1)
                return;

        int64_t smaller = index;
        int64_t left_element = 2 * index + 1;
        int64_t rigth_element = 2 * index + 2;

        if (left_element < arr_size && comparator(array[left_element], array[smaller]) < 0)
                smaller = left_element;
        if (rigth_element < arr_size && comparator(array[rigth_element], array[smaller]) < 0)
                smaller = rigth_element;
        if (smaller != index) {
                swap(&array[index], &array[smaller]);
                heapify(array, arr_size, smaller, comparator);
        }
}

void enqueue(priority_queue *queue, object object)
{
        const size_t arr_length = queue->length;
        const size_t arr_end = arr_length - 1;
        const size_t arr_size = queue->size;
        const size_t obj_size = sizeof(struct object);

        if (arr_length == arr_size)
                increase_array_size(queue);

        memmove(&queue->array[arr_length], &object, obj_size);
        increase_array_length(queue);

        for (int i = arr_end / 2 - 1; i >= 0; i--)
                heapify(queue->array, arr_end, i, queue->comparator);
}

result dequeue(priority_queue *queue)
{
        const size_t arr_length = queue->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = sizeof(struct object);
        const obj_type type = queue->type;

        if (arr_length > 0) {
                result obj = get_object(&queue->array[0], type);

                swap(&queue->array[0], &queue->array[arr_length - 1]);

                for (int i = arr_end / 2 - 1; i >= 0; i--)
                        heapify(queue->array, arr_end, i, queue->comparator);

                memset(&queue->array[arr_end], 0, obj_size);
                decrease_array_length(queue);

                return obj;
        }

        return (struct result) { .is_present = false };
}

result peek(priority_queue *queue)
{
        const size_t arr_length = queue->length;
        const obj_type type = queue->type;

        if (arr_length > 0)
                return get_object(&queue->array[0], type);

        return (struct result) { .is_present = false };
}

void show_priority_queue(priority_queue *queue, to_string_fn to_string, bool reverse)
{
        const size_t arr_length = queue->length;

        if (arr_length > 0) {
                int start = reverse ? arr_length : 0;
                int end = reverse ? 0 : arr_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(queue->array[i]);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(queue->array[i]);
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

                queue->type = -1;
                queue->size = -1;
                queue->length = -1;

                free(queue);
                queue = NULL;
        }
}
