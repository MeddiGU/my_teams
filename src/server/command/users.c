/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** users
*/

#include "../../../include/my.h"

void users(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");

    server->check = 1;
    if (server->current->is_logged == false) {
        dprintf(server->current->socket, "530\n\r");
        return;
    }
    if (tab[1] != NULL) {
        dprintf(server->current->socket, "531\n\r");
        return;
    }
    list_user(server);
}

void list_user(server_s *server)
{
    FILE *file;
    char line[4096];
    char **tab;
    int tempsock = server->current->socket;

    file = fopen("database/user.txt", "r");
    if (file == NULL) {
        dprintf(server->current->socket, "532\n\r");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab(line, ":");
        user_exist(server, tab, tempsock);
    }
    fclose(file);
}

void user_exist(server_s *server, char **tab, int tmpsock)
{
    client_info* current = server->client_head;

    for (; current != NULL; current = current->next) {
        if (strcmp(tab[0], current->uuid) == 0) {
            dprintf(tmpsock, "232 %s %s %d\n\r",
                tab[0], tab[1], 1);
            return;
        }
    }
    dprintf(tmpsock, "232 %s %s %d\n\r",
        tab[0], tab[1], 0);
}