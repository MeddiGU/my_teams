/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** user
*/

#include "../../../include/my.h"

void user(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    remove_quotes(tab);
    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n\r");
        return;
    }
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "550\n\r");
        return;
    }
    if (read_user_info(server, tab[1]) == 1) {
        dprintf(server->current->socket, "550\n\r");
    }
}

int read_user_info(server_s *server, char *uuid)
{
    FILE *file;
    char line[4096];
    char **tab;
    int tempsock = server->current->socket;

    file = fopen("database/user.txt", "r");
    if (file == NULL) {
        dprintf(server->current->socket, "532\n\r");
        return 1;
    }
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, ":");
        if (find_user(server, tab, tempsock, uuid) == 0)
            return 0;
    }
}

int find_user(server_s *server, char **tab, int tmpsock, char *uuid)
{
    client_info* current = server->client_head;

    for (; current != NULL; current = current->next) {
        if (strcmp(uuid, current->uuid) == 0) {
            dprintf(tmpsock, "233 %s %s %d\n\r",
                current->uuid, current->username, 1);
                return 0;
        }
    }
    if (strcmp(uuid, tab[0]) == 0) {
        dprintf(tmpsock, "233 %s %s %d\n\r",
            tab[0], tab[1], 0);
            return 0;
    }
}