/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** create_command
*/

#include "../../../include/my.h"

void create(server_s *server, char *buffer)
{
    char **tab = strtok_tab_spe(buffer, " \t\n\r", 0, 0);

    server->check = 1;
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "500\n\r");
        return;
    }
    if (server->current->is_in_team == false) {
        create_team(server, tab);
    }
    if (server->current->is_in_team == true &&
        server->current->is_in_channel == false) {
        create_channel(server, tab);
    }
    create_thread_reply(server, tab);
}

void create_thread_reply(server_s *server, char **tab)
{
    if (server->current->is_in_team == true &&
        server->current->is_in_channel == true &&
        server->current->is_in_thread == false) {
        create_thread(server, tab);
    }
    if (server->current->is_in_channel == true &&
        server->current->is_in_team == true &&
        server->current->is_in_thread == true) {
            create_reply(server, tab);
        }
}

void check_quote(char *token, int *in_quotes)
{
    for (int j = 0; token[j] != '\0'; j++) {
        if (token[j] == '"')
            *in_quotes = !*in_quotes;
    }
}

char **strtok_tab_spe(char *str, char *tok, int i, int in_quotes)
{
    char **tab = malloc(sizeof(char *) * 4096);
    char *token = strtok(str, tok);
    size_t prev_len;

    while (token != NULL) {
        if (!in_quotes) {
            tab[i] = strdup(token);
            i++;
        } else {
            prev_len = strlen(tab[i - 1]);
            tab[i - 1] = realloc(tab[i - 1], prev_len + strlen(token) + 2);
            strcat(tab[i - 1], " ");
            strcat(tab[i - 1], token);
        }
        check_quote(token, &in_quotes);
        str = NULL;
        token = strtok(str, tok);
    }
    tab[i] = NULL;
    return tab;
}