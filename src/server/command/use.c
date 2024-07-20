/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** use
*/

#include "../../../include/my.h"

void use(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    remove_quotes(tab);
    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n\r");
        return;
    }
    if (tab[1] == NULL) {
        return;
    }
    if (tab[1] != NULL && tab[2] == NULL) {
        server->current->current_team = strdup(tab[1]);
        server->current->is_in_team = true;
        return;
    }
    use_reply(server, tab);
}

void use_reply(server_s *server, char **tab)
{
    if (tab[1] != NULL && tab[2] != NULL && tab[3] == NULL) {
        server->current->current_channel = strdup(tab[2]);
        server->current->is_in_channel = true;
        server->current->is_in_team = true;
        return;
    }
    if (tab[1] != NULL && tab[2] != NULL && tab[3] != NULL) {
        server->current->current_thread = strdup(tab[3]);
        server->current->current_channel = strdup(tab[2]);
        server->current->is_in_thread = true;
        server->current->is_in_channel = true;
        server->current->is_in_team = true;
        return;
    }
}