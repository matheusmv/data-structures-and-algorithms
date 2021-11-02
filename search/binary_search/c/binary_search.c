#include "binary_search.h"

static bool is_empty(object *array)
{
        return array == NULL;
}

static result get_result(object *obj)
{
        if (obj != NULL)
                return (struct result) { .is_present = true, .object = *obj };

        return (struct result) { .is_present = false };
}

result binary_search(object *array, size_t arr_length, object key, compare_obj_fn comparator)
{
        if (!is_empty(array)) {
                size_t start = 0;
                size_t mid = 0;
                size_t end = arr_length - 1;

                while (start <= end) {
                        mid = (start + end) / 2;

                        int cmp_result = comparator(key, array[mid]);

                        if (cmp_result < 0) {
                                end = mid - 1;
                        } else if (cmp_result > 0) {
                                start = mid + 1;
                        } else {
                                return get_result(&array[mid]);
                        }
                }
        }

        return (struct result) { .is_present = false };
}
