/**
 * gcc data_types.c array_list.c example.c -o program
 */
#include "array_list.h"

struct state states[] = {
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

struct user users[] = {
        {.username = "username 1", .password = "password 1"},
        {.username = "username 2", .password = "password 2"},
        {.username = "username 3", .password = "password 3"},
        {.username = "username 4", .password = "password 4"},
        {.username = "username 5", .password = "password 5"},
};

void show_states(array_list *);
void show_users(array_list *);

int main(int argc, char *argv[])
{
        array_list *state_list = new_array_list(10, STATE_TYPE);

        if (state_list == NULL)
                return EXIT_FAILURE;

        show_states(state_list);

        const int state_arr_s = sizeof(states) / sizeof(struct state);

        for (int i = 0; i < state_arr_s; i++)
                append_obj(state_list, (struct object) { ._state = states[i] });

        show_states(state_list);

        remove_obj(state_list);
        remove_obj(state_list);
        remove_obj(state_list);
        remove_obj(state_list);
        remove_obj(state_list);

        show_states(state_list);

        add_obj_at(state_list, (struct object) { ._state = states[10] }, 0);
        add_obj_at(state_list, (struct object) { ._state = states[10] }, 2);
        add_obj_at(state_list, (struct object) { ._state = states[10] }, 4);
        add_obj_at(state_list, (struct object) { ._state = states[10] }, 8);

        show_states(state_list);

        struct state result = *(struct state *) get_obj_at(state_list, 4);

        printf("%s - %s\n", result.state, result.abbreviation);

        remove_obj_at(state_list, 5);

        show_states(state_list);

        destroy_array_list(state_list);

        /********************************************************************/

        array_list *users_list = new_array_list(1, USER_TYPE);

        if (users_list == NULL)
                return EXIT_FAILURE;

        show_users(users_list);

        const int user_arr_s = sizeof(users) / sizeof(struct user);

        for (int i = 0; i < user_arr_s; i++)
                append_obj(users_list, (struct object) { ._user = users[i] });

        show_users(users_list);

        remove_obj(users_list);
        remove_obj(users_list);

        show_users(users_list);

        add_obj_at(users_list, (struct object) { ._user = users[2] }, 0);
        add_obj_at(users_list, (struct object) { ._user = users[2] }, 4);

        show_users(users_list);

        struct user usr = *(struct user *) get_obj_at(users_list, 4);

        printf("%s - %s\n", usr.username, usr.password);

        remove_obj_at(users_list, 0);

        show_users(users_list);

        destroy_array_list(users_list);

        return EXIT_SUCCESS;
}

void show_states(array_list *arr)
{
        const size_t arr_size = get_size(arr);
        const size_t arr_length = get_length(arr);

        printf("array size: %ld | array length: %ld\n", arr_size, arr_length);

        if (arr_length == 0) {
                printf("***empty***\n");
        } else {
                for (int i = 0; i < arr_length; i++) {
                        struct state state = *(struct state *) get_obj_at(arr, i);

                        printf("\t%d - %s - %s\n",
                               state.number, state.state, state.abbreviation);
                }
                printf("\n");
        }
}

void show_users(array_list *arr)
{
        const size_t arr_size = get_size(arr);
        const size_t arr_length = get_length(arr);

        printf("array size: %ld | array length: %ld\n", arr_size, arr_length);

        if (arr_length == 0) {
                printf("***empty***\n");
        } else {
                for (int i = 0; i < arr_length; i++) {
                        struct user user = *(struct user *) get_obj_at(arr, i);

                        printf("\t%s - %s\n", user.username, user.password);
                }
                printf("\n");
        }
}
