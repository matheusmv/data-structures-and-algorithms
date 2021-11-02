#include "linear_search.h"

bool is_empty(object *array)
{
        return array == NULL;
}

result get_result(object *obj)
{
        if (obj != NULL)
                return (struct result) { .is_present = true, .object = *obj };

        return (struct result) { .is_present = false };
}

result linear_search(object *array, size_t arr_length, object key, compare_obj_fn comparator)
{
        if (!is_empty(array)) {
                for (int i = 0; i < arr_length; i++) {
                        if (comparator(key, array[i]) == 0) {
                                return get_result(&array[i]);
                        }
                }
        }

        return (struct result) { .is_present = false };
}
