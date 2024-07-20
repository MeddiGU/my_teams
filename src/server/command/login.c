/*
** EPITECH PROJECT, 2024
** B-NWP-400-MAR-4-1-myteams-meddi.gueran
** File description:
** login
*/

#include "../../../include/my.h"

void login(server_s *server, char *buffer)
{
    char **tab = strtok_tab(buffer, "  \t\n\r");
    char *uuid = NULL;
    char *username = NULL;

    server->check = 1;
    if (tab[1] == NULL) {
        dprintf(server->current->socket, "500\n");
        return;
    }
    uuid = strdup(tab[1]);
    if (check_existing_user(server, uuid) == 0) {
        send_to_all_user(server);
        dprintf(server->current->socket, "230 %s %s\n",
            server->current->uuid, server->current->username);
        server->current->is_logged = true;
        server_event_user_logged_in(server->current->uuid);
        return;
    }
    create_user(server, tab);
}

void bring_id(server_s *server, char *line)
{
    char **tab = strtok_tab(line, ":");

    server->current->uuid = strdup(tab[0]);
    server->current->username = strdup(tab[1]);
}

int check_existing_user(server_s *server, char *uuid)
{
    FILE *file;
    char line[4096];

    file = fopen("database/user.txt", "r");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }
    while (fgets(line, 4096, file) != NULL) {
        if (strstr(line, uuid) != NULL) {
            bring_id(server, line);
            fclose(file);
            return 0;
        }
    }
    fclose(file);
    return 1;
}

void create_user(server_s *server, char **tab)
{
    FILE *file;

    server->current->uuid = strdup(tab[1]);
    file = fopen("database/user.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }
    fprintf(file, "%s:%s\n", server->current->uuid, tab[2]);
    server->current->username = strdup(tab[2]);
    send_to_all_user(server);
    server->current->is_logged = true;
    dprintf(server->current->socket, "230 %s %s\n",
        server->current->uuid, server->current->username);
    fclose(file);
    server_event_user_created(server->current->uuid,
        server->current->username);
    server_event_user_logged_in(server->current->uuid);
}

void send_to_all_user(server_s *server)
{
    client_info *current = server->client_head;

    for (; current != NULL; current = current->next) {
        if (current->socket != server->current->socket
            && current->is_logged == true) {
            dprintf(current->socket, "230 %s %s\n\r",
                server->current->uuid, server->current->username);
        }
    }
}