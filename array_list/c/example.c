/**
 * gcc array_list.c example.c -o program
*/
#include "array_list.h"

void show(struct array_list *);

struct object states[] = {
        {.number = 1, .state = "Acre", .abbreviation = "AC"},
        {.number = 2, .state = "Alagoas", .abbreviation = "AL"},
        {.number = 3, .state = "Amapá", .abbreviation = "AP"},
        {.number = 4, .state = "Amazonas", .abbreviation = "AM"},
        {.number = 5, .state = "Bahia", .abbreviation = "BA"},
        {.number = 6, .state = "Ceará", .abbreviation = "CE"},
        {.number = 7, .state = "Distrito Federal", .abbreviation = "DF"},
        {.number = 8, .state = "Espírito Santo", .abbreviation = "ES"},
        {.number = 9, .state = "Goiás", .abbreviation = "GO"},
        {.number = 10, .state = "Maranhão", .abbreviation = "MA"},
        {.number = 11, .state = "Mato Grosso", .abbreviation = "MT"},
        {.number = 12, .state = "Mato Grosso do Sul", .abbreviation = "MS"},
        {.number = 13, .state = "Minas Gerais", .abbreviation = "MG"},
        {.number = 14, .state = "Pará", .abbreviation = "PA"},
        {.number = 15, .state = "Paraíba", .abbreviation = "PB"},
        {.number = 16, .state = "Paraná", .abbreviation = "PR"},
        {.number = 17, .state = "Pernambuco", .abbreviation = "PE"},
        {.number = 18, .state = "Piauí", .abbreviation = "PI"},
        {.number = 19, .state = "Rio de Janeiro", .abbreviation = "RJ"},
        {.number = 20, .state = "Rio Grande do Norte", .abbreviation = "RN"},
        {.number = 21, .state = "Rio Grande do Sul", .abbreviation = "RS"},
        {.number = 22, .state = "Rondônia", .abbreviation = "RO"},
        {.number = 23, .state = "Roraima", .abbreviation = "RR"},
        {.number = 24, .state = "Santa Catarina", .abbreviation = "SC"},
        {.number = 25, .state = "São Paulo", .abbreviation = "SP"},
        {.number = 26, .state = "Sergipe", .abbreviation = "SE"},
        {.number = 27, .state = "Tocantins", .abbreviation = "TO"},
};

int main(int argc, char *argv[])
{
        struct array_list state_list = new_array_list(10);

        show(&state_list);

        const int arr_s = sizeof(states) / sizeof(struct object);

        for (int i = 0; i < arr_s; i++)
                append_obj(&state_list, states[i]);

        show(&state_list);

        remove_obj(&state_list);
        remove_obj(&state_list);
        remove_obj(&state_list);
        remove_obj(&state_list);
        remove_obj(&state_list);

        show(&state_list);

        add_obj_at(&state_list, states[10], 0);
        add_obj_at(&state_list, states[10], 2);
        add_obj_at(&state_list, states[10], 4);
        add_obj_at(&state_list, states[10], 8);

        show(&state_list);

        struct object result = get_obj_at(&state_list, 4);

        printf("%s - %s\n", result.state, result.abbreviation);

        remove_obj_at(&state_list, 5);

        show(&state_list);

        destroy_array_list(&state_list);

        return EXIT_SUCCESS;
}

void show(struct array_list *arr)
{
        printf("array size: %ld | array length: %ld\n",
               get_size(arr), get_length(arr));

        if (arr->length == 0) {
                printf("***empty***\n");
        } else {
                for (int i = 0; i < arr->length; i++) {
                        printf("\t%d - %s - %s\n",
                               arr->array[i].number,
                               arr->array[i].state,
                               arr->array[i].abbreviation);
                }
                printf("\n");
        }
}
