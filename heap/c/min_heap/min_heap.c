#include "min_heap.h"

typedef struct __min_heap {
        struct object *array;
        compare_obj_fn comparator;
        obj_type type;
        size_t size;
        size_t length;
} min_heap;

static void increase_array_length(min_heap *heap)
{
        const size_t arr_length = heap->length;
        const size_t arr_size = heap->size;

        if (arr_length < arr_size)
                heap->length += 1;
}

static void decrease_array_length(min_heap *heap)
{
        const size_t arr_length = heap->length;

        if (arr_length > 0)
                heap->length -= 1;
}

static void increase_array_size(min_heap *heap)
{
        const size_t SCALING_FACTOR = 2;
        const size_t obj_size = sizeof(struct object);
        const size_t arr_length = heap->length;
        const size_t arr_size = heap->size;
        const size_t new_arr_size = arr_size * SCALING_FACTOR;

        const size_t new_size = obj_size * new_arr_size;

        heap->array = realloc(heap->array, new_size);

        if (heap->array == NULL) {
                fprintf(stderr, "realloc() failed. (%s)\n", GETSTDERROR());
                destroy_min_heap(heap);
                exit(EXIT_FAILURE);
        }

        for (int i = arr_length; i < new_arr_size; i++)
                memset(&heap->array[i], 0, obj_size);

        heap->size = new_arr_size;
}

min_heap *new_min_heap(size_t heap_size, obj_type type, compare_obj_fn comparator)
{
        min_heap *heap = malloc(sizeof(min_heap));

        if (heap == NULL)
                return NULL;

        const size_t obj_size = sizeof(struct object);

        object *new_array = malloc(heap_size * obj_size);

        if (new_array == NULL) {
                free(heap);
                return NULL;
        }

        memset(new_array, 0, sizeof(*new_array));

        const obj_type heap_type = get_object_type(type);

        *heap = (min_heap) {
                .array = new_array,
                .comparator = comparator,
                .type = heap_type,
                .size = heap_size,
                .length = 0,
        };

        return heap;
}

size_t get_length(min_heap *heap)
{
        return heap->length;
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

        int64_t largest = index;
        int64_t left_element = 2 * index + 1;
        int64_t rigth_element = 2 * index + 2;

        if (left_element < arr_size && comparator(array[left_element], array[largest]) < 0)
                largest = left_element;
        if (rigth_element < arr_size && comparator(array[rigth_element], array[largest]) < 0)
                largest = rigth_element;
        if (largest != index) {
                swap(&array[index], &array[largest]);
                heapify(array, arr_size, largest, comparator);
        }
}

void insert_obj(min_heap *heap, object object)
{
        const size_t arr_length = heap->length;
        const size_t arr_end = arr_length - 1;
        const size_t arr_size = heap->size;
        const size_t obj_size = sizeof(struct object);

        if (arr_length == arr_size)
                increase_array_size(heap);

        memmove(&heap->array[arr_length], &object, obj_size);
        increase_array_length(heap);

        for (int i = arr_end / 2 - 1; i >= 0; i--)
                heapify(heap->array, arr_end, i, heap->comparator);
}

result remove_obj(min_heap *heap)
{
        const size_t arr_length = heap->length;
        const size_t arr_end = arr_length - 1;
        const size_t obj_size = sizeof(struct object);
        const obj_type type = heap->type;

        if (arr_length > 0) {
                result obj = get_object(&heap->array[0], type);

                swap(&heap->array[0], &heap->array[arr_length - 1]);

                for (int i = arr_end / 2 - 1; i >= 0; i--)
                        heapify(heap->array, arr_end, i, heap->comparator);

                memset(&heap->array[arr_end], 0, obj_size);
                decrease_array_length(heap);

                return obj;
        }

        return (struct result) { .is_present = false };
}

void show_heap(min_heap *heap, to_string_fn to_string, bool reverse)
{
        const size_t arr_length = heap->length;

        if (arr_length > 0) {
                int start = reverse ? arr_length : 0;
                int end = reverse ? 0 : arr_length;

                if (reverse) {
                        for (int i = start - 1; i >= end; i--)
                                to_string(heap->array[i]);
                } else {
                        for (int i = start; i < end; i++)
                                to_string(heap->array[i]);
                }
        }
}

void destroy_min_heap(min_heap *heap)
{
        if (heap != NULL) {
                if (heap->array != NULL) {
                        free(heap->array);
                        heap->array = NULL;
                }

                heap->type = -1;
                heap->size = -1;
                heap->length = -1;

                free(heap);
                heap = NULL;
        }
}
