/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** messages
*/

#include "../../../include/my.h"

void messages(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, " \t\n\r");
    char *uuid_user = NULL;

    remove_quotes(tab);
    server->check = 1;
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "500\n");
        return;
    }
    uuid_user = strdup(tab[1]);
    if (check_existing_id(server, uuid_user) == true) {
        find_message(server, uuid_user);
        return;
    } else {
        dprintf(server->current->socket, "550\n");
    }
}

bool check_existing_id(server_s *server, char *uuid_user)
{
    FILE *file;
    char line[4096];
    char **tab = NULL;

    file = fopen("database/user.txt", "r");
    if (file == NULL) {
        printf("Error with open file.\n");
        return false;
    }
    while (fgets(line, 4096, file) != NULL) {
        tab = strtok_tab(line, ":");
        if (strstr(tab[0], uuid_user) != NULL) {
            fclose(file);
            return true;
        }
    }
    fclose(file);
    return false;
}

void find_message(server_s *server, char *uuid_user)
{
    FILE *file;
    char line[4096];
    char **tab = NULL;

    file = fopen("database/messages.txt", "r");
    if (file == NULL) {
        dprintf(server->current->socket, "532\n\r");
        return;
    }
    while (fgets(line, sizeof(line), file)) {
        tab = strtok_tab_spe(line, "::", 0, 0);
        send_find_message(server, uuid_user, tab);
    }
    fclose(file);
}

void send_find_message(server_s *server, char *uuid_user, char **tab)
{
    if (strstr(tab[1], uuid_user) != NULL) {
        if (strstr(tab[0], server->current->uuid) != NULL) {
            dprintf(server->current->socket, "250 %s %s %s\n\r",
                uuid_user, tab[2], tab[3]);
        }
    }
    if (strstr(tab[0], uuid_user) != NULL) {
        if (strstr(tab[1], server->current->uuid) != NULL) {
            dprintf(server->current->socket, "250 %s %s %s\n\r", uuid_user,
                tab[2], tab[3]);
        }
    }
}
