#include <stdio.h>

#include "array_list.h"

#define ARR_LEN(ARR) (sizeof (ARR) / sizeof (ARR)[0])

struct state {
        int number;
        char *state;
        char *abbreviation;
};

struct user {
        char *username;
        char *password;
};

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

void show_states(void *obj);
void show_users(void *obj);

int main(int argc, char *argv[])
{
        array_list *state_list = array_list_create(10, sizeof(struct state));

        if (state_list == NULL)
                return EXIT_FAILURE;

        for (int i = 0; i < ARR_LEN(states); i++)
                array_list_append(state_list, &states[i]);

        array_list_remove(state_list, NULL);
        array_list_remove(state_list, NULL);
        array_list_remove(state_list, NULL);
        array_list_remove(state_list, NULL);
        array_list_remove(state_list, NULL);

        array_list_append_at(state_list, &states[10], 0);
        array_list_append_at(state_list, &states[10], 2);
        array_list_append_at(state_list, &states[10], 4);
        array_list_append_at(state_list, &states[10], 8);

        struct state result;
        if (array_list_find_at(state_list, 4, &result) == 0) {
                printf("\t***found: ");
                show_states(&result);
        }

        array_list_remove_at(state_list, 5, NULL);

        array_list_show(state_list, show_states, IN_ORDER);

        array_list_free(state_list);

        /********************************************************************/

        array_list *users_list = array_list_create(1, sizeof(struct user));

        if (users_list == NULL)
                return EXIT_FAILURE;

        array_list_show(users_list, show_users, IN_ORDER);

        for (int i = 0; i < ARR_LEN(users); i++)
                array_list_append(users_list, &users[i]);

        array_list_remove(users_list, NULL);
        array_list_remove(users_list, NULL);

        array_list_append_at(users_list, &users[2], 0);
        array_list_append_at(users_list, &users[2], 4);

        struct user usr_result;
        if (array_list_find_at(users_list, 4, &usr_result) == 0) {
                printf("\t***found: ");
                show_users(&usr_result);
        }

        array_list_remove_at(users_list, 0, NULL);

        array_list_show(users_list, show_users, IN_ORDER);

        array_list_free(users_list);

        return EXIT_SUCCESS;
}

void
show_states(void *obj)
{
        struct state *state = obj;

        printf("\t%d - %s - %s\n", state->number, state->state, state->abbreviation);
}

void
show_users(void *obj)
{
        struct user *user = obj;

        printf("\t%s - %s\n", user->username, user->password);
}
